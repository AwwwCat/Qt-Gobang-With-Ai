#ifndef PLAYEROPTION_H
#define PLAYEROPTION_H

#include <QDialog>
#include <QString>
#include <QFileDialog>

namespace Ui {
class PlayerOption;
}

class PlayerOption : public QDialog
{
    Q_OBJECT

public:
    explicit PlayerOption(QWidget *parent = nullptr);
    ~PlayerOption();
    Ui::PlayerOption *ui;

    QString nameA = QString("Baka");
    QString pathA;
    QString nameB = QString("Baka");
    QString pathB;

private slots:
    void on_OKButton_clicked();

    void on_photoAButton_clicked();

    void on_photoBButton_clicked();

signals:
    void playerOptionSgn(QString nma, QString pha, QString nmb, QString phb);

private:

};

#endif // PLAYEROPTION_H
