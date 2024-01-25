#include "../Headers/DebugOption.h"

DebugOption::DebugOption(QWidget* parent) : QDialog(parent)
{
	/* �޸Ĵ��ڲ��� */
	this->setWindowTitle(QStringLiteral("Debug����"));
	this->setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);

	/* ������� */
	weightShowBox = new QCheckBox(QStringLiteral("��ʾaiȨ��"));
	commitButton = new QPushButton(QStringLiteral("ȷ��"));
	cancelButton = new QPushButton(QStringLiteral("ȡ��"));

	buttonLayout = new QHBoxLayout;
	widgetLayout = new QVBoxLayout;

	/* ���� */
	buttonLayout->addStretch(1);
	buttonLayout->addWidget(commitButton);
	buttonLayout->addWidget(cancelButton);

	widgetLayout->addWidget(weightShowBox);
	widgetLayout->addStretch(1);
	widgetLayout->addLayout(buttonLayout);

	this->setLayout(widgetLayout);

	/* �����ź���� */
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