#include "../Headers/MainWidget.h"

MainWidget::MainWidget(QWidget* parent) : QWidget(parent)
{
	/* 定义对象 */
	chess = new Chess;
	playerAName = new QLabel(QStringLiteral("[玩家姓名]"));
	playerBName = new QLabel(QStringLiteral("[玩家姓名]"));
	playerAPhoto = new QLabel(QStringLiteral("[玩家头像]"));
	playerBPhoto = new QLabel(QStringLiteral("[玩家头像]"));
	pieceLabel = new QLabel(QStringLiteral("现在是黑方下棋"));
	pieceShow = new QLabel;
	leftTimeLabel = new QLabel(QStringLiteral("剩余思考时间"));
	leftTimeShow = new QLabel;

	timer = new QTimer;
	stimer = new QTimer;

	pieceLayout = new QVBoxLayout;
	leftTimeLayout = new QVBoxLayout;
	dataShowLayout = new QHBoxLayout;
	playerALayout = new QVBoxLayout;
	playerBLayout = new QVBoxLayout;
	sidebarLayout = new QVBoxLayout;
	widgetLayout = new QHBoxLayout;

	/* 修改标签属性 */
	playerAName->setAlignment(Qt::AlignCenter);
	playerBName->setAlignment(Qt::AlignCenter);
	playerAPhoto->setAlignment(Qt::AlignCenter);
	playerBPhoto->setAlignment(Qt::AlignCenter);
	pieceLabel->setAlignment(Qt::AlignCenter);
	pieceShow->setAlignment(Qt::AlignCenter);
	leftTimeLabel->setAlignment(Qt::AlignCenter);
	leftTimeShow->setAlignment(Qt::AlignCenter);

	pieceShow->installEventFilter(this);

	playerAPhoto->setScaledContents(true);
	playerBPhoto->setScaledContents(true);

	winnerBox = new QMessageBox{ QMessageBox::NoIcon, QStringLiteral("恭喜"), QStringLiteral("") };
	winnerBox->setWindowFlags(Qt::Dialog);
	winnerBox->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
	backButton = winnerBox->addButton(QStringLiteral("返回棋盘"), QMessageBox::NoRole);
	againButton = winnerBox->addButton(QStringLiteral("再来一局"), QMessageBox::NoRole);

	/* 控件大小控制 */
	chess->setMinimumSize(chess->startX * 2 + chess->cellNum * chess->cellSize + 1, chess->startY * 2 + chess->cellNum * chess->cellSize + 1);
	pieceLabel->setMaximumWidth(140);
	pieceLabel->setMinimumWidth(140);
	leftTimeLabel->setMaximumWidth(140);
	leftTimeLabel->setMinimumWidth(140);
	playerAName->setMinimumWidth(291);
	playerAName->setMaximumWidth(291);
	pieceShow->setMinimumSize(140, 140);
	leftTimeShow->setMinimumSize(140, 140);
	playerAPhoto->setMinimumHeight(291);
	playerBPhoto->setMinimumHeight(291);

	QFont ft;
	ft.setPointSize(40);
	leftTimeShow->setFont(ft);

	/* 布局 */
	pieceLayout->addWidget(pieceLabel);
	pieceLayout->addWidget(pieceShow);

	leftTimeLayout->addWidget(leftTimeLabel);
	leftTimeLayout->addWidget(leftTimeShow);

	dataShowLayout->addLayout(pieceLayout);
	dataShowLayout->addLayout(leftTimeLayout);

	playerALayout->addWidget(playerAPhoto);
	playerALayout->addWidget(playerAName);

	playerBLayout->addWidget(playerBPhoto);
	playerBLayout->addWidget(playerBName);

	sidebarLayout->addSpacing(50);
	sidebarLayout->addLayout(playerALayout);
	sidebarLayout->addStretch(1);
	sidebarLayout->addLayout(dataShowLayout);
	sidebarLayout->addStretch(1);
	sidebarLayout->addLayout(playerBLayout);
	sidebarLayout->addSpacing(50);

	widgetLayout->addWidget(chess);
	widgetLayout->addLayout(sidebarLayout);
	widgetLayout->addSpacing(50);
	widgetLayout->setStretchFactor(chess, 1);
	widgetLayout->setStretchFactor(sidebarLayout, 0);

	this->setLayout(widgetLayout);

	/* 链接信号与槽 */
	connect(timer, &QTimer::timeout, this, &MainWidget::timeOut);
	connect(stimer, &QTimer::timeout, this, &MainWidget::secondCutDown);
	connect(chess, &Chess::pieceChangedSgn, this, &MainWidget::pieceModeChange);
	connect(chess, &Chess::winnerSgn, this, &MainWidget::winGame);
}

MainWidget::~MainWidget()
{
	delete chess;
	delete playerAPhoto;
	delete playerBPhoto;
	delete playerAName;
	delete playerBName;
	delete pieceLabel; 
	delete pieceShow; 
	delete leftTimeLabel; 
	delete leftTimeShow;

	delete timer;
	delete stimer;

	delete backButton;
	delete againButton;
	delete winnerBox;

	delete pieceLayout;
	delete leftTimeLayout;
	delete dataShowLayout;
	delete playerALayout;
	delete playerBLayout;
	delete sidebarLayout;
	delete widgetLayout;
};

bool MainWidget::eventFilter(QObject* obj, QEvent* event)
{
	if (obj == pieceShow && event->type() == QEvent::Paint)
	{
		QPainter painter(pieceShow);
		painter.setRenderHint(QPainter::Antialiasing, true);

		if (chess->pieceMode == Black)
			painter.setBrush(chess->pieceAColor);
		else if (chess->pieceMode == White)
			painter.setBrush(chess->pieceBColor);
		painter.drawEllipse(75 - 35, 75 - 35, 2 * 35, 2 * 35);
	}
	return QWidget::eventFilter(obj, event);
}

void MainWidget::pieceModeShow(int pm)
{
	QString str = QStringLiteral("现在是");
	str.append(pm == Black ? QStringLiteral("黑") : QStringLiteral("白"));
	str.append(QStringLiteral("方下棋"));
	pieceLabel->setText(str);
}

void MainWidget::pieceModeChange()
{
	pieceModeShow(chess->pieceMode);
	this->timerRestart();
	update();
}

void MainWidget::timerRestart()
{
	leftTime = playTime;
	timer->start(playTime * 1000);
	stimer->start(1000);
	leftTimeShow->setNum(leftTime);
}

void MainWidget::timeOut()
{
	winGame(chess->pieceMode == Black ? White : Black);
	leftTimeShow->setNum(0);
}

void MainWidget::secondCutDown()
{
	leftTime -= 1;
	leftTimeShow->setNum(leftTime);
}

void MainWidget::winGame(int winner)
{
	QString str;
	stimer->stop();
	if (winner == None)
	{
		str = QStringLiteral("平局！");
	}
	else
	{
		str = winner == Black ? QStringLiteral("黑") : QStringLiteral("白");
		str.append(QStringLiteral("方获胜！"));
	}
	winnerBox->setText(str);
	winnerBox->exec();
	if (winnerBox->clickedButton() == againButton)
		chess->createNewChessMap();
	else if (winnerBox->clickedButton() == backButton)
	{
		chess->playing = false;
		timer->stop();
	}
}

void MainWidget::receiveNewGameSgn(int gm, int tm, int cn)
{
	playTime = tm;
	chess->cellNum = cn;
	this->timerRestart();

	chess->playing = true;
	chess->gameMode = gm;
	pieceModeShow(Black);
	chess->createNewChessMap();
}

void MainWidget::receiveSaveChessMapSgn()
{
	QString path = QCoreApplication::applicationDirPath() + "/maps";
	QDir dir(path);
	if (!dir.exists())
	{
		dir.mkpath(path);
	}

	QDateTime currentDateTime = QDateTime::currentDateTime();
	QString currentDate = currentDateTime.toString("yyyy.MM.dd_hh.mm.ss");

	QFile file(path + "/" + currentDate + ".dat");
	file.open(QIODevice::WriteOnly | QIODevice::Text);
	QDataStream out(&file);
	out << (quint32)0xA4B3C2D1;

	QVector<int> map = chess->saveChessMap();
	for (int i = 0; i < map.size(); i++)
		out << (quint32)map[i];

	file.close();
}

void MainWidget::receiveMainOptionsSgn(QColor ca, QColor cb, bool nextPieceShow, bool orderShow)
{
	chess->pieceAColor = ca;
	chess->pieceBColor = cb;
	chess->showPiece = nextPieceShow;
	chess->showOrder = orderShow;
}

void MainWidget::receivePlayerOptionsSgn(QString nma, QString pha, QString nmb, QString phb)
{
	playerAName->setText(nma);
	playerBName->setText(nmb);

	if (!pha.isEmpty())
	{
		QPixmap pix(pha);
		playerAPhoto->setPixmap(pix);
	}

	if (!phb.isEmpty())
	{
		QPixmap pix(phb);
		playerBPhoto->setPixmap(pix);
	}
}

void MainWidget::receiveDebugOptionsSgn(bool weightshow)
{
	chess->showScore = weightshow;
}

void MainWidget::receiveImportSgn(int gameMode, int cellNum, int order, QVector<QVector<int>>chessOrder)
{
	chess->gameMode = gameMode;
	chess->cellNum = cellNum;
	chess->pieceMode = order % 2 + 1;
	chess->loadChessMap(order, chessOrder);
	this->timerRestart();
}