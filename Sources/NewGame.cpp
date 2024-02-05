#include "../Headers/NewGame.h"

NewGame::NewGame(QWidget* parent) : QDialog(parent)
{
    /* �޸Ĵ��ڲ��� */
    this->setWindowTitle(QStringLiteral("����Ϸ"));
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);

    /* ������� */
    gamemodeLabel = new QLabel(QStringLiteral("��ѡ����Ϸģʽ��"));
    timeLabel = new QLabel(QStringLiteral("˼��ʱ�䣨3-99����"));
    cellNumLabel = new QLabel(QStringLiteral("���̸�����5-26����"));
    PVPButton = new QRadioButton(QStringLiteral("PVP"));
    PVCButton = new QRadioButton(QStringLiteral("PVC"));
    thinkTimeBox = new QSpinBox;
    cellNumBox = new QSpinBox;
    commitButton = new QPushButton(QStringLiteral("ȷ��"));
    cancelButton = new QPushButton(QStringLiteral("ȡ��"));
    modeButtonGroup = new QButtonGroup;

    modeLayout = new QVBoxLayout;
    timeLayout = new QHBoxLayout;
    cellLayout = new QHBoxLayout;
    buttonLayout = new QHBoxLayout;
    widgetLayout = new QVBoxLayout;

    /* �޸ı�ǩ���� */
    PVCButton->setChecked(true);
    thinkTimeBox->setValue(DEFAULT_PLAY_TIME);
    thinkTimeBox->setSuffix(QStringLiteral("��"));
    thinkTimeBox->setRange(3, 99);
    cellNumBox->setValue(15);
    cellNumBox->setSuffix(QStringLiteral("��"));
    cellNumBox->setRange(5, 26);

    /* ��ť��༭ */
    modeButtonGroup->addButton(PVCButton, 0);
    modeButtonGroup->addButton(PVPButton, 1);

    /* ���� */
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

    /* �����ź���� */
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