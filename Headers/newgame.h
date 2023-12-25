#ifndef NEWGAME_H
#define NEWGAME_H

#include <QDialog>
#include <QButtonGroup>

namespace Ui {
class NewGame;
}

class NewGame : public QDialog
{
    Q_OBJECT

public:
    explicit NewGame(QDialog *parent = nullptr);
    ~NewGame();
    Ui::NewGame *ui;

public slots:


signals:
    void pressOK(int gameMode, int thinkTime);


private slots:
    void on_OKButton_clicked();


    void on_pushButton_clicked();

private:
    QButtonGroup *buttonGroup;

};

#endif // NEWGAME_H
