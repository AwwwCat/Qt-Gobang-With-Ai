#include "../Headers/MainOption.h"

MainOption::MainOption(QWidget* parent) : QDialog(parent)
{
    /* �޸Ĵ��ڲ��� */
    this->setWindowTitle(QStringLiteral("��Ϸ����"));
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);

    /* ������� */
    colorLabel = new QLabel(QStringLiteral("��ɫ����"));
    colorALabel = new QLabel(QStringLiteral("�ڷ�������ɫ��"));
    colorBLabel = new QLabel(QStringLiteral("�׷�������ɫ��"));
    colorAShow = new QLabel;
    colorBShow = new QLabel;
    otherLabel = new QLabel(QStringLiteral("��������"));
    nextPieceShow = new QCheckBox(QStringLiteral("��ʾ��һ�����λ��"));
    orderShow = new QCheckBox(QStringLiteral("��ʾ����˳��"));
    colorAButton = new QPushButton(QStringLiteral("ѡ��..."));
    colorBButton = new QPushButton(QStringLiteral("ѡ��..."));
    commitButton = new QPushButton(QStringLiteral("ȷ��"));
    cancelButton = new QPushButton(QStringLiteral("ȡ��"));

    colorALayout = new QHBoxLayout;
    colorBLayout = new QHBoxLayout;
    buttonLayout = new QHBoxLayout;
    widgetLayout = new QVBoxLayout;

    /* �޸ı�ǩ���� */
    colorALabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    colorBLabel->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    colorAShow->setMinimumWidth(80);
    colorBShow->setMinimumWidth(80);
    colorAShow->setAutoFillBackground(true);
    colorAShow->setPalette(colorAPalette);
    colorBShow->setAutoFillBackground(true);
    colorBShow->setPalette(colorBPalette);
    nextPieceShow->setChecked(true);

    /* ���� */
    colorALayout->addWidget(colorALabel);
    colorALayout->addWidget(colorAShow);
    colorALayout->addWidget(colorAButton);

    colorBLayout->addWidget(colorBLabel);
    colorBLayout->addWidget(colorBShow);
    colorBLayout->addWidget(colorBButton);

    buttonLayout->addStretch(1);
    buttonLayout->addWidget(commitButton);
    buttonLayout->addWidget(cancelButton);

    widgetLayout->addWidget(colorLabel);
    widgetLayout->addLayout(colorALayout);
    widgetLayout->addLayout(colorBLayout);
    widgetLayout->addWidget(otherLabel);
    widgetLayout->addWidget(nextPieceShow);
    widgetLayout->addWidget(orderShow);
    widgetLayout->addStretch(1);
    widgetLayout->addLayout(buttonLayout);

    this->setLayout(widgetLayout);

    /* �����ź���� */
    connect(colorAButton, &QPushButton::clicked, this, &MainOption::colorAButtonClicked);
    connect(colorBButton, &QPushButton::clicked, this, &MainOption::colorBButtonClicked);
    connect(commitButton, &QPushButton::clicked, this, &MainOption::commitButtonClicked);
    connect(cancelButton, &QPushButton::clicked, this, &MainOption::cancelButtonClicked);
}

MainOption::~MainOption()
{
    delete colorLabel;
    delete colorALabel;
    delete colorBLabel;
    delete colorAShow;
    delete colorBShow;
    delete otherLabel;
    delete nextPieceShow;
    delete orderShow;
    delete colorAButton;
    delete colorBButton;
    delete commitButton;
    delete cancelButton;

    delete colorALayout;
    delete colorBLayout;
    delete buttonLayout;
    delete widgetLayout;
}

void MainOption::colorAButtonClicked()
{
    colorA = QColorDialog::getColor(colorA, this, QStringLiteral("ѡ����ɫ"));
    colorAPalette = QPalette(colorA);
    colorAShow->setPalette(colorAPalette);
}

void MainOption::colorBButtonClicked()
{
    colorB = QColorDialog::getColor(colorB, this, QStringLiteral("ѡ����ɫ"));
    colorBPalette = QPalette(colorB);
    colorBShow->setPalette(colorBPalette);
}

void MainOption::commitButtonClicked()
{
    emit commitOptionsSgn(colorA, colorB, nextPieceShow->isChecked(), orderShow->isChecked());
    this->close();
}

void MainOption::cancelButtonClicked()
{
    this->close();
}