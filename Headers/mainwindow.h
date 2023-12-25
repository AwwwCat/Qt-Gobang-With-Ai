#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#define SIDEBAR_W 300

#include <QMainWindow>
#include <QTimer>
#include <QPixmap>
#include "chess.h"
#include "newgame.h"
#include "option.h"
#include "playeroption.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int gameMode;
    int pieceMode;
    int playTime;
    int leftTime;
    QString playerAName;
    QString playerBName;

    QTimer *timer;
    QTimer *stimer;

    Chess *chess;
    NewGame *newgame;
    Option *option;
    PlayerOption *playerOption;

    QPushButton *backBut;
    QPushButton *againBut;
    QMessageBox *winnerBox;

    void startNewGame(int gm, int tm);
    void newGameOption(bool sw, int gm);

private:
    Ui::MainWindow *ui;
    bool eventFilter(QObject *obj,QEvent *event);

signals:
    void newGameSgn();

private slots:
    void timeOut();
    void winGame(int winner);
    void pieceModeChange(int p);
    void newGameAction();
    void optionAction();
    void secondCutDown();
    void playingMethod();
    void aboutGames();
    void optionChanged(QColor ca, QColor cb, bool sp, bool so, bool ss);
    void playerOptionAction();
    void playerOptionChanged(QString nma, QString pha, QString nmb, QString phb);


};
#endif // MAINWINDOW_H
