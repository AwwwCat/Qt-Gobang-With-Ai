#include "../Headers/PlayerOption.h"

PlayerOption::PlayerOption(QWidget* parent) : QDialog(parent)
{
    /* 修改窗口参数 */
    this->setWindowTitle(QStringLiteral("玩家设置"));
    this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);

    /* 定义对象 */
    ALabel = new QLabel(QStringLiteral("黑方玩家信息"));
    BLabel = new QLabel(QStringLiteral("白方玩家信息"));
    nameALabel = new QLabel(QStringLiteral("玩家名称"));
    nameBLabel = new QLabel(QStringLiteral("玩家名称"));
    photoALabel = new QLabel(QStringLiteral("图片路径"));
    photoBLabel = new QLabel(QStringLiteral("图片路径"));
    nameAEdit = new QLineEdit(nameA);
    nameBEdit = new QLineEdit(nameB);
    pathAEdit = new QLineEdit;
    pathBEdit = new QLineEdit;
    pathAButton = new QPushButton(QStringLiteral("浏览..."));
    pathBButton = new QPushButton(QStringLiteral("浏览..."));
    commitButton = new QPushButton(QStringLiteral("确定"));
    cancelButton = new QPushButton(QStringLiteral("取消"));

    nameALayout = new QHBoxLayout;
    nameBLayout = new QHBoxLayout;
    photoALayout = new QHBoxLayout;
    photoBLayout = new QHBoxLayout;
    buttonLayout = new QHBoxLayout;
    widgetLayout = new QVBoxLayout;

    /* 布局 */
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

    /* 链接信号与槽 */
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
    pathA = QFileDialog::getOpenFileName(this, QStringLiteral("选择图片"), QCoreApplication::applicationFilePath(), QStringList("*.jpg;*.png").join(";"));
    pathAEdit->setText(pathA);
}

void PlayerOption::pathBButtonClicked()
{
    pathB = QFileDialog::getOpenFileName(this, QStringLiteral("选择图片"), QCoreApplication::applicationFilePath(), QStringList("*.jpg;*.png").join(";"));
    pathBEdit->setText(pathB);
}
