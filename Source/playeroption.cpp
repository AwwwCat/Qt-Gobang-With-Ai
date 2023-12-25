#include "playeroption.h"
#include "ui_playeroption.h"

PlayerOption::PlayerOption(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlayerOption)
{
    ui->setupUi(this);
    setWindowTitle("玩家设置");

    ui->nameALineEdit->setText(nameA);
    ui->nameBLineEdit->setText(nameB);
}

PlayerOption::~PlayerOption()
{
    delete ui;
}

void PlayerOption::on_OKButton_clicked()
{
    emit playerOptionSgn(ui->nameALineEdit->text(), ui->pathALineEdit->text(), ui->nameBLineEdit->text(), ui->photoBButton->text());
    this->close();
}

void PlayerOption::on_photoAButton_clicked()
{
    pathA = QFileDialog::getOpenFileName(this, "", QCoreApplication::applicationFilePath(), QStringList("*.jpg;*.png").join(";"));
    ui->pathALineEdit->setText(pathA);
}

void PlayerOption::on_photoBButton_clicked()
{
    pathB = QFileDialog::getOpenFileName(this, "", QCoreApplication::applicationFilePath(), QStringList("*.jpg;*.png").join(";"));
    ui->pathBLineEdit->setText(pathB);
}
