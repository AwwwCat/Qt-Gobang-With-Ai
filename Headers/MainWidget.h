#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "../Headers/define.h"
#include "../Headers/Chess.h"
#include <QCoreApplication>
#include <QDataStream>
#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QLabel>
#include <QLayout>
#include <QMessageBox>
#include <QPainter>
#include <QPainterPath>
#include <QPaintEvent>
#include <QPen>
#include <QPixmap>
#include <QString>
#include <QTimer>
#include <QWidget>

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    int playTime = DEFAULT_PLAY_TIME;
    int leftTime = DEFAULT_PLAY_TIME;

    explicit MainWidget(QWidget* parent = nullptr);
    ~MainWidget();

    Chess* chess;
    QLabel* playerAPhoto;
    QLabel* playerBPhoto;
    QLabel* playerAName;
    QLabel* playerBName;
    QLabel* pieceLabel;
    QLabel* pieceShow;
    QLabel* leftTimeLabel;
    QLabel* leftTimeShow;

    QTimer* timer;
    QTimer* stimer;

    QPushButton* backButton;
    QPushButton* againButton;
    QMessageBox* winnerBox;

private:
    QVBoxLayout* pieceLayout;
    QVBoxLayout* leftTimeLayout;
    QHBoxLayout* dataShowLayout;
    QVBoxLayout* playerALayout;
    QVBoxLayout* playerBLayout;
    QVBoxLayout* sidebarLayout;
    QHBoxLayout* widgetLayout;

    bool eventFilter(QObject* obj, QEvent* event);
    void pieceModeShow(int pm);
    void pieceModeChange();
    void timerRestart();
    void timeOut();
    void secondCutDown();
    void winGame(int winner);

public slots:
    void receiveNewGameSgn(int gm, int tm, int cn);
    void receiveSaveChessMapSgn();
    void receiveMainOptionsSgn(QColor ca, QColor cb, QColor cbc, QColor clc, bool nextPieceShow, bool orderShow);
    void receivePlayerOptionsSgn(QString nma, QString pha, QString nmb, QString phb);
    void receiveDebugOptionsSgn(bool weightshow);
    void receiveImportSgn(int gameMode, int cellNum, int order, QVector<QVector<int>>chessOrder);
};

#endif // !MAINWIDGET_H