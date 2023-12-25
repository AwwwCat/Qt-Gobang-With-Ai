#include "newgame.h"
#include "ui_newgame.h"

NewGame::NewGame(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::NewGame)
{
    ui->setupUi(this);
    setWindowTitle("新游戏");
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    ui->PVPButton->setChecked(true);

    buttonGroup = new QButtonGroup;
    buttonGroup->addButton(ui->PVPButton, 0);
    buttonGroup->addButton(ui->PVCButton, 1);
}

NewGame::~NewGame()
{
    delete ui;
    delete buttonGroup;
}

void NewGame::on_OKButton_clicked()
{
    emit pressOK(buttonGroup->checkedId() + 1, ui->timeSpinBox->value());
    this->close();
}

void NewGame::on_pushButton_clicked()
{
    this->close();
}
