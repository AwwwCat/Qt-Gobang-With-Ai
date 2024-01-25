#include "../Headers/ImportDialog.h"

ImportDialog::ImportDialog(QWidget* parent) : QDialog(parent)
{
	/* 修改窗口参数 */
	this->setWindowTitle(QStringLiteral("导入对局"));
	this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);

	/* 定义对象 */
    chessBoard = new ChessBoard;

    chooseLabel = new QLabel(QStringLiteral("请选择要导入的对局："));
    chooseBox = new QComboBox;
    refreshButton = new QPushButton(QStringLiteral("刷新"));
    commitButton = new QPushButton(QStringLiteral("确定"));
    cancelButton = new QPushButton(QStringLiteral("取消"));

    chooseLayout = new QHBoxLayout;
    buttonLayout = new QHBoxLayout;
    widgetLayout = new QVBoxLayout;

    /* 修改标签属性 */
    chooseLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    chessBoard->setMinimumSize(chessBoard->startX * 2 + chessBoard->cellNum * chessBoard->cellSize + 1, chessBoard->startY * 2 + chessBoard->cellNum * chessBoard->cellSize + 1);

    /* 布局 */
    chooseLayout->addWidget(chooseLabel);
    chooseLayout->addWidget(chooseBox);

    buttonLayout->addStretch(1);
    buttonLayout->addWidget(refreshButton);
    buttonLayout->addWidget(commitButton);
    buttonLayout->addWidget(cancelButton);

    widgetLayout->addLayout(chooseLayout);
    widgetLayout->addWidget(chessBoard);
    widgetLayout->addLayout(buttonLayout);

    this->setLayout(widgetLayout);

    /* 链接信号与槽 */
    connect(chooseBox, &QComboBox::currentTextChanged, this, &ImportDialog::readChessMap);
    connect(refreshButton, &QPushButton::clicked, this, &ImportDialog::refreshButtonClicked);
    connect(commitButton, &QPushButton::clicked, this, &ImportDialog::commitButtonClicked);
    connect(cancelButton, &QPushButton::clicked, this, &ImportDialog::cancelButtonClicked);

    loadChessMaps();
}

ImportDialog::~ImportDialog()
{
    delete chessBoard;

    delete chooseLabel;
    delete chooseBox;
    delete refreshButton;
    delete commitButton;
    delete cancelButton;

    delete chooseLayout;
    delete buttonLayout;
    delete widgetLayout;
}

void ImportDialog::loadChessMaps()
{
    QString path = QCoreApplication::applicationDirPath() + "/maps";
    QDir dir(path);
    if (!dir.exists())
    {
        dir.mkpath(path);
    }

    chooseBox->addItems(dir.entryList(QDir::Files | QDir::NoDot));
}

void ImportDialog::readChessMap()
{
    qDebug() << chooseBox->currentText();
    QString path = QCoreApplication::applicationDirPath() + "/maps/" + chooseBox->currentText();
    QFile file(path);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QDataStream in(&file);

    quint32 magic;
    in >> magic;
    if (magic != 0xA4B3C2D1)
        return; // 要改

    gameMode = 0;
    cellNum = 0;
    order = 0;
    in >> gameMode >> cellNum >> order;
    chessBoard->cellNum = cellNum;

    chessOrder.clear();
    chessOrder.fill(QVector<int>(2, -1), pow(cellNum + 1, 2));

    for (int i = 0; !in.atEnd(); i++)
    {
        int x, y;
        in >> x >> y;
        
        QVector<int> addr;
        addr.append(x);
        addr.append(y);
        chessOrder.replace(i, addr);
    }

    chessBoard->loadChessMap(order, chessOrder);

    file.close();
}

void ImportDialog::wrongChessMap()
{

}

void ImportDialog::refreshButtonClicked()
{
    chooseBox->clear();
    loadChessMaps();
}

void ImportDialog::commitButtonClicked()
{
    emit commitImportSgn(gameMode, cellNum, order, chessOrder);
    this->close();
}

void ImportDialog::cancelButtonClicked()
{
    this->close();
}