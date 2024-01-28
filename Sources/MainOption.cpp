#include "../Headers/MainOption.h"

MainOption::MainOption(QWidget* parent) : QDialog(parent)
{
    /* 修改窗口参数 */
    this->setWindowTitle(QStringLiteral("游戏设置"));
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);

    /* 定义对象 */
    colorLabel = new QLabel(QStringLiteral("颜色设置"));
    colorALabel = new QLabel(QStringLiteral("黑方棋子颜色："));
    colorBLabel = new QLabel(QStringLiteral("白方棋子颜色："));
    chessBoardColorLabel = new QLabel(QStringLiteral("棋盘背景颜色："));
    colorAShow = new QLabel;
    colorBShow = new QLabel;
    chessBoardColorShow = new QLabel;
    otherLabel = new QLabel(QStringLiteral("其他设置"));
    nextPieceShow = new QCheckBox(QStringLiteral("显示下一步棋的位置"));
    orderShow = new QCheckBox(QStringLiteral("显示下棋顺序"));
    colorAButton = new QPushButton(QStringLiteral("选择..."));
    colorBButton = new QPushButton(QStringLiteral("选择..."));
    chessBoardColorButton = new QPushButton(QStringLiteral("选择..."));
    commitButton = new QPushButton(QStringLiteral("确定"));
    cancelButton = new QPushButton(QStringLiteral("取消"));

    colorALayout = new QHBoxLayout;
    colorBLayout = new QHBoxLayout;
    chessBoardColorLayout = new QHBoxLayout;
    buttonLayout = new QHBoxLayout;
    widgetLayout = new QVBoxLayout;

    /* 修改标签属性 */
    colorALabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    colorBLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    chessBoardColorLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    colorAShow->setMinimumWidth(80);
    colorBShow->setMinimumWidth(80);
    colorAShow->setAutoFillBackground(true);
    colorAShow->setPalette(colorAPalette);
    colorBShow->setAutoFillBackground(true);
    colorBShow->setPalette(colorBPalette);
    chessBoardColorShow->setAutoFillBackground(true);
    chessBoardColorShow->setPalette(chessBoardColorPalette);
    nextPieceShow->setChecked(true);

    /* 布局 */
    colorALayout->addWidget(colorALabel);
    colorALayout->addWidget(colorAShow);
    colorALayout->addWidget(colorAButton);

    colorBLayout->addWidget(colorBLabel);
    colorBLayout->addWidget(colorBShow);
    colorBLayout->addWidget(colorBButton);

    chessBoardColorLayout->addWidget(chessBoardColorLabel);
    chessBoardColorLayout->addWidget(chessBoardColorShow);
    chessBoardColorLayout->addWidget(chessBoardColorButton);

    buttonLayout->addStretch(1);
    buttonLayout->addWidget(commitButton);
    buttonLayout->addWidget(cancelButton);

    widgetLayout->addWidget(colorLabel);
    widgetLayout->addLayout(colorALayout);
    widgetLayout->addLayout(colorBLayout);
    widgetLayout->addLayout(chessBoardColorLayout);
    widgetLayout->addWidget(otherLabel);
    widgetLayout->addWidget(nextPieceShow);
    widgetLayout->addWidget(orderShow);
    widgetLayout->addStretch(1);
    widgetLayout->addLayout(buttonLayout);

    this->setLayout(widgetLayout);

    /* 链接信号与槽 */
    connect(colorAButton, &QPushButton::clicked, this, &MainOption::colorAButtonClicked);
    connect(colorBButton, &QPushButton::clicked, this, &MainOption::colorBButtonClicked);
    connect(chessBoardColorButton, &QPushButton::clicked, this, &MainOption::chessBoardColorButtonClicked);
    connect(commitButton, &QPushButton::clicked, this, &MainOption::commitButtonClicked);
    connect(cancelButton, &QPushButton::clicked, this, &MainOption::cancelButtonClicked);
}

MainOption::~MainOption()
{
    delete colorLabel;
    delete colorALabel;
    delete colorBLabel;
    delete chessBoardColorLabel;
    delete colorAShow;
    delete colorBShow;
    delete chessBoardColorShow;
    delete otherLabel;
    delete nextPieceShow;
    delete orderShow;
    delete colorAButton;
    delete colorBButton;
    delete commitButton;
    delete cancelButton;

    delete colorALayout;
    delete colorBLayout;
    delete chessBoardColorLayout;
    delete buttonLayout;
    delete widgetLayout;
}

void MainOption::colorAButtonClicked()
{
    colorA = QColorDialog::getColor(colorA, this, QStringLiteral("选择颜色"));
    colorAPalette = QPalette(colorA);
    colorAShow->setPalette(colorAPalette);
}

void MainOption::colorBButtonClicked()
{
    colorB = QColorDialog::getColor(colorB, this, QStringLiteral("选择颜色"));
    colorBPalette = QPalette(colorB);
    colorBShow->setPalette(colorBPalette);
}

void MainOption::chessBoardColorButtonClicked()
{
    chessBoardColor = QColorDialog::getColor(chessBoardColor, this, QStringLiteral("选择颜色"));
    chessBoardColorPalette = QPalette(chessBoardColor);
    chessBoardColorShow->setPalette(chessBoardColorPalette);
}

void MainOption::commitButtonClicked()
{
    emit commitOptionsSgn(colorA, colorB, chessBoardColor, nextPieceShow->isChecked(), orderShow->isChecked());
    this->close();
}

void MainOption::cancelButtonClicked()
{
    this->close();
}