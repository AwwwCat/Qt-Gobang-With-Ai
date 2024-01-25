#include "../Headers/DebugOption.h"

DebugOption::DebugOption(QWidget* parent) : QDialog(parent)
{
	/* 修改窗口参数 */
	this->setWindowTitle(QStringLiteral("Debug设置"));
	this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);

	/* 定义对象 */
	weightShowBox = new QCheckBox(QStringLiteral("显示ai权重"));
	commitButton = new QPushButton(QStringLiteral("确定"));
	cancelButton = new QPushButton(QStringLiteral("取消"));

	buttonLayout = new QHBoxLayout;
	widgetLayout = new QVBoxLayout;

	/* 布局 */
	buttonLayout->addStretch(1);
	buttonLayout->addWidget(commitButton);
	buttonLayout->addWidget(cancelButton);

	widgetLayout->addWidget(weightShowBox);
	widgetLayout->addStretch(1);
	widgetLayout->addLayout(buttonLayout);

	this->setLayout(widgetLayout);

	/* 链接信号与槽 */
	connect(commitButton, &QPushButton::clicked, this, &DebugOption::commitButtonClicked);
	connect(cancelButton, &QPushButton::clicked, this, &DebugOption::cancelButtonClicked);
}

DebugOption::~DebugOption()
{
	delete weightShowBox;
	delete commitButton;
	delete cancelButton;

	delete buttonLayout;
	delete widgetLayout;
}

void DebugOption::commitButtonClicked()
{
	emit commitOptionsSgn(weightShowBox->isChecked());
	this->close();
}

void DebugOption::cancelButtonClicked()
{
	this->close();
}