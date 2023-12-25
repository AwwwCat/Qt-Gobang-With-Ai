#include "option.h"
#include "ui_option.h"

Option::Option(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::Option)
{
    ui->setupUi(this);
    ui->showPieceCheckBox->setChecked(true);
    ui->pieceAComboBox->setCurrentIndex(0);
    ui->pieceBComboBox->setCurrentIndex(1);
    setWindowTitle("设置");
}

Option::~Option()
{
    delete ui;
}

void Option::on_pushButton_clicked()
{
    QColor colors[8] = {QColor(0, 0, 0, 255),
                        QColor(255, 255, 255, 255),
                        QColor(255, 0, 0, 255),
                        QColor(255, 255, 0, 255),
                        QColor(0, 255, 0, 255),
                        QColor(0, 255, 255, 255),
                        QColor(0, 0, 255, 255),
                        QColor(255, 0, 255, 255)
                       };
    emit options(colors[ui->pieceAComboBox->currentIndex()], colors[ui->pieceBComboBox->currentIndex()],
            ui->showPieceCheckBox->isChecked(), ui->orderCheckBox->isChecked(), ui->scoreCheckBox->isChecked());
    this->close();
}
