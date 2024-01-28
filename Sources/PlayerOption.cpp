#include "../Headers/PlayerOption.h"

PlayerOption::PlayerOption(QWidget* parent) : QDialog(parent)
{
    /* �޸Ĵ��ڲ��� */
    this->setWindowTitle(QStringLiteral("�������"));
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);

    /* ������� */
    ALabel = new QLabel(QStringLiteral("�ڷ������Ϣ"));
    BLabel = new QLabel(QStringLiteral("�׷������Ϣ"));
    nameALabel = new QLabel(QStringLiteral("�������"));
    nameBLabel = new QLabel(QStringLiteral("�������"));
    photoALabel = new QLabel(QStringLiteral("ͼƬ·��"));
    photoBLabel = new QLabel(QStringLiteral("ͼƬ·��"));
    nameAEdit = new QLineEdit(nameA);
    nameBEdit = new QLineEdit(nameB);
    pathAEdit = new QLineEdit;
    pathBEdit = new QLineEdit;
    pathAButton = new QPushButton(QStringLiteral("���..."));
    pathBButton = new QPushButton(QStringLiteral("���..."));
    commitButton = new QPushButton(QStringLiteral("ȷ��"));
    cancelButton = new QPushButton(QStringLiteral("ȡ��"));

    nameALayout = new QHBoxLayout;
    nameBLayout = new QHBoxLayout;
    photoALayout = new QHBoxLayout;
    photoBLayout = new QHBoxLayout;
    buttonLayout = new QHBoxLayout;
    widgetLayout = new QVBoxLayout;

    /* ���� */
    nameALayout->addWidget(nameALabel);
    nameALayout->addWidget(nameAEdit);

    photoALayout->addWidget(photoALabel);
    photoALayout->addWidget(pathAEdit);
    photoALayout->addWidget(pathAButton);

    nameBLayout->addWidget(nameBLabel);
    nameBLayout->addWidget(nameBEdit);

    
    photoBLayout->addWidget(photoBLabel);
    photoBLayout->addWidget(pathBEdit);
    photoBLayout->addWidget(pathBButton);

    buttonLayout->addStretch(1);
    buttonLayout->addWidget(commitButton);
    buttonLayout->addWidget(cancelButton);

    widgetLayout->addWidget(ALabel);
    widgetLayout->addLayout(nameALayout);
    widgetLayout->addLayout(photoALayout);
    widgetLayout->addWidget(BLabel);
    widgetLayout->addLayout(nameBLayout);
    widgetLayout->addLayout(photoBLayout);
    widgetLayout->addStretch(1);
    widgetLayout->addLayout(buttonLayout);

    this->setLayout(widgetLayout);

    /* �����ź���� */
    connect(pathAButton, &QPushButton::clicked, this, &PlayerOption::pathAButtonClicked);
    connect(pathBButton, &QPushButton::clicked, this, &PlayerOption::pathBButtonClicked);
    connect(commitButton, &QPushButton::clicked, this, &PlayerOption::commitButtonClicked);
    connect(cancelButton, &QPushButton::clicked, this, &PlayerOption::cancelButtonClicked);
}

PlayerOption::~PlayerOption()
{
    delete ALabel;
    delete BLabel;
    delete nameALabel;
    delete nameBLabel;
    delete photoALabel;
    delete photoBLabel;
    delete nameAEdit;
    delete nameBEdit;
    delete pathAEdit;
    delete pathBEdit;
    delete pathAButton;
    delete pathBButton;
    delete commitButton;
    delete cancelButton;

    delete nameALayout;
    delete nameBLayout;
    delete photoALayout;
    delete photoBLayout;
    delete buttonLayout;
    delete widgetLayout;
}

void PlayerOption::commitButtonClicked()
{
    emit commitOptionsSgn(nameAEdit->text(), pathAEdit->text(), nameBEdit->text(), pathBEdit->text());
    this->close();
}

void PlayerOption::cancelButtonClicked()
{
    this->close();
}

void PlayerOption::pathAButtonClicked()
{
    pathA = QFileDialog::getOpenFileName(this, QStringLiteral("ѡ��ͼƬ"), QCoreApplication::applicationFilePath(), QStringList("*.jpg;*.png").join(";"));
    pathAEdit->setText(pathA);
}

void PlayerOption::pathBButtonClicked()
{
    pathB = QFileDialog::getOpenFileName(this, QStringLiteral("ѡ��ͼƬ"), QCoreApplication::applicationFilePath(), QStringList("*.jpg;*.png").join(";"));
    pathBEdit->setText(pathB);
}
