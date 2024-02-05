#include "../Headers/NewGame.h"

NewGame::NewGame(QWidget* parent) : QDialog(parent)
{
    /* 修改窗口参数 */
    this->setWindowTitle(QStringLiteral("新游戏"));
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);

    /* 定义对象 */
    gamemodeLabel = new QLabel(QStringLiteral("请选择游戏模式："));
    timeLabel = new QLabel(QStringLiteral("思考时间（3-99）："));
    cellNumLabel = new QLabel(QStringLiteral("棋盘格数（5-26）："));
    PVPButton = new QRadioButton(QStringLiteral("PVP"));
    PVCButton = new QRadioButton(QStringLiteral("PVC"));
    thinkTimeBox = new QSpinBox;
    cellNumBox = new QSpinBox;
    commitButton = new QPushButton(QStringLiteral("确定"));
    cancelButton = new QPushButton(QStringLiteral("取消"));
    modeButtonGroup = new QButtonGroup;

    modeLayout = new QVBoxLayout;
    timeLayout = new QHBoxLayout;
    cellLayout = new QHBoxLayout;
    buttonLayout = new QHBoxLayout;
    widgetLayout = new QVBoxLayout;

    /* 修改标签属性 */
    PVCButton->setChecked(true);
    thinkTimeBox->setValue(DEFAULT_PLAY_TIME);
    thinkTimeBox->setSuffix(QStringLiteral("秒"));
    thinkTimeBox->setRange(3, 99);
    cellNumBox->setValue(15);
    cellNumBox->setSuffix(QStringLiteral("格"));
    cellNumBox->setRange(5, 26);

    /* 按钮组编辑 */
    modeButtonGroup->addButton(PVCButton, 0);
    modeButtonGroup->addButton(PVPButton, 1);

    /* 布局 */
    modeLayout->addWidget(gamemodeLabel);
    modeLayout->addWidget(PVCButton);
    modeLayout->addWidget(PVPButton);

    timeLayout->addWidget(timeLabel);
    timeLayout->addWidget(thinkTimeBox);

    cellLayout->addWidget(cellNumLabel);
    cellLayout->addWidget(cellNumBox);

    buttonLayout->addStretch(1);
    buttonLayout->addWidget(commitButton);
    buttonLayout->addWidget(cancelButton);

    widgetLayout->addLayout(modeLayout);
    widgetLayout->addLayout(timeLayout);
    widgetLayout->addLayout(cellLayout);
    widgetLayout->addStretch(1);
    widgetLayout->addLayout(buttonLayout);

    this->setLayout(widgetLayout);

    /* 链接信号与槽 */
    connect(commitButton, &QPushButton::clicked, this, &NewGame::commitButtonClicked);
    connect(cancelButton, &QPushButton::clicked, this, &NewGame::cancelButtonClicked);
}

NewGame::~NewGame()
{
    delete gamemodeLabel;
    delete timeLabel;
    delete PVPButton;
    delete PVCButton;
    delete thinkTimeBox;
    delete commitButton;
    delete cancelButton;
    delete modeButtonGroup;

    delete modeLayout;
    delete timeLayout;
    delete buttonLayout;
    delete widgetLayout;
}

void NewGame::commitButtonClicked()
{
    emit commitNewGameSgn(modeButtonGroup->checkedId() + 1, thinkTimeBox->value(), cellNumBox->value() - 1);
    this->close();
}

void NewGame::cancelButtonClicked()
{
    this->close();
}