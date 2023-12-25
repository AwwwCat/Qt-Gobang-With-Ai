#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(START_X*2+CELL_NUM*CELL_SIZE+SIDEBAR_W+1, START_Y*2+CELL_NUM*CELL_SIZE+TopDistance+1);
    pieceMode = Black;
    ui->PieceMode->installEventFilter(this);

    connect(ui->NewgameAction, &QAction::triggered, this, &MainWindow::newGameAction);
    connect(ui->playingMethodAction, &QAction::triggered, this, &MainWindow::playingMethod);
    connect(ui->aboutGames, &QAction::triggered, this, &MainWindow::aboutGames);
    connect(ui->optionAction, &QAction::triggered, this, &MainWindow::optionAction);
    connect(ui->playerOptionAction, &QAction::triggered, this, &MainWindow::playerOptionAction);

    chess = new Chess(this);
    connect(chess, &Chess::pieceSgn, this, &MainWindow::pieceModeChange);
    connect(chess, &Chess::winnerSgn, this, &MainWindow::winGame);

    winnerBox = new QMessageBox {QMessageBox::NoIcon, "恭喜", ""};
    winnerBox->setWindowFlags(Qt::Dialog);
    winnerBox->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    backBut = winnerBox->addButton("返回棋盘", QMessageBox::NoRole);
    againBut = winnerBox->addButton("再来一局", QMessageBox::NoRole);

    timer = new QTimer;
    stimer = new QTimer;
    playTime = 30;
    connect(timer, &QTimer::timeout, this, &MainWindow::timeOut);
    connect(stimer, &QTimer::timeout, this, &MainWindow::secondCutDown);

    option = new Option;
    connect(option, &Option::options, this, &MainWindow::optionChanged);

    newgame = new NewGame;
    connect(newgame, &NewGame::pressOK, this, &MainWindow::startNewGame);

    playerOption = new PlayerOption;
    connect(playerOption, &PlayerOption::playerOptionSgn, this, &MainWindow::playerOptionChanged);
    ui->PlayerAName->setText(playerOption->nameA);
    ui->PlayerBName->setText(playerOption->nameB);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
    delete stimer;
    delete chess;
    delete backBut;
    delete againBut;
    delete newgame;
    delete winnerBox;
    delete option;
    delete playerOption;
}

void MainWindow::newGameAction()
{
    newgame->exec();
}

void MainWindow::optionAction()
{
    option->exec();
}

void MainWindow::winGame(int winner)
{
    stimer->stop();
    QString str = winner == Black ? "黑" : "白";
    winnerBox->setText(str.append("方获胜！"));
    winnerBox->exec();
    if (winnerBox->clickedButton() == againBut)
        chess->cleanChessboard();
    else if (winnerBox->clickedButton() == backBut)
    {
        chess->gameMode = Noplay;
        timer->stop();
        stimer->stop();
    }
}

void MainWindow::startNewGame(int gm, int tm)
{
    playTime = tm;
    leftTime = playTime;
    timer->start(playTime * 1000);
    stimer->start(1000);
    ui->LeftTime->setNum(leftTime);

    chess->gameMode = gm;
    chess->cleanChessboard();
    pieceMode = Black;
}

void MainWindow::timeOut()
{
    ui->LeftTime->setNum(0);
    winGame(pieceMode == Black ? White : Black);
}

bool MainWindow::eventFilter(QObject *obj,QEvent *event)
{
   if(obj == ui->PieceMode && event->type() == QEvent::Paint)
   {
       QPainter painter(ui->PieceMode);
       painter.setRenderHint(QPainter::Antialiasing, true);
       if (pieceMode == Black)
           painter.setBrush(chess->pieceAColor);
       else if (pieceMode == White)
           painter.setBrush(chess->pieceBColor);

       painter.drawEllipse(75-PIECE_R, 75-PIECE_R, 2*PIECE_R, 2*PIECE_R);
   }
   return QMainWindow::eventFilter(obj, event);
}

void MainWindow::secondCutDown()
{
    leftTime -= 1;
    ui->LeftTime->setNum(leftTime);
}

void MainWindow::pieceModeChange(int p)
{
    pieceMode = p;
    QString str = "现在是";
    str.append(pieceMode == Black ? "黑" : "白");
    str.append("方下棋");
    ui->PieceLabel->setText(str);
    timer->start(playTime * 1000);
    stimer->start(1000);
    leftTime = playTime;
    ui->LeftTime->setNum(leftTime);
    update();
}

void MainWindow::playingMethod()
{
    QMessageBox messageBox(QMessageBox::Question, "玩法说明", "你是傻逼吗五子棋不会玩？\n自己百度谢谢。", QMessageBox::Ok);
    messageBox.exec();
}

void MainWindow::aboutGames()
{
    QMessageBox messageBox(QMessageBox::Question, "关于软件", "作者：我\n版本：v0.00314152653589793238", QMessageBox::Ok);
    messageBox.exec();
}

void MainWindow::optionChanged(QColor ca, QColor cb, bool sp, bool so, bool ss)
{
    chess->pieceAColor = ca;
    chess->pieceBColor = cb;
    chess->showPiece = sp;
    chess->showOrder = so;
    chess->showScore = ss;
}

void MainWindow::playerOptionAction()
{
    playerOption->exec();
}

void MainWindow::playerOptionChanged(QString nma, QString pha, QString nmb, QString phb)
{
    ui->PlayerAName->setText(nma);
    ui->PlayerBName->setText(nmb);

    if (!pha.isEmpty())
    {
        QPixmap pix(pha);
        ui->PlayerAPhoto->setPixmap(pix);
    }

    if (!phb.isEmpty())
    {
        QPixmap pix(phb);
        ui->PlayerBPhoto->setPixmap(pix);
    }

;}
