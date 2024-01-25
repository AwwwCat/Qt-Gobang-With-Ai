#ifndef CHESS_H
#define CHESS_H

#include "../Headers/ChessBoard.h"
#include <cmath>
#include <QColor>
#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>
#include <QPaintEvent>
#include <QPen>
#include <QPushButton>
#include <QRandomGenerator>
#include <QResizeEvent>
#include <QtGlobal>
#include <QTime>
#include <QTimer>
#include <QVector>
#include <QWidget>

enum Gamemode {
    Noplay, PvC, PvP
};

enum SingleTypes {
    WP, OXP, WXP, OXXP, WXXP, OXXXP, WXXXP, OXXXXP, WXXXXP, WOOP, WOP, OP, WXOP, OXOP, WXXOP, OXXOP, WXXXOP, OXOXP
};

enum Categorys {
    MakeKill, AliveFour, LongFive, RushFour, AliveThree, SleepThree, AliveTwo, JumpTwo, MiddleTwo, SideTwo, SleepTwo, AliveOne, SleepOne, ThreeThree, FourThree, FourFour, AllCategorys
};

class Chess : public ChessBoard
{
    Q_OBJECT

public:
    explicit Chess(QWidget* parent = nullptr);
    virtual ~Chess();

    bool playing = false;
    bool showPiece = true;
    bool showOrder = false;
    bool showScore = false;

    int pieceMode;
    int gameMode = Noplay;

private:
    int direction[8][2] = { {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1} };
    int pieceX, pieceY;
    QVector<QVector<int>> scoreMap;

    void paintEvent(QPaintEvent* e);
    void mouseMoveEvent(QMouseEvent* e);
    void mousePressEvent(QMouseEvent* e);

    void chessPlaying();
    bool lianziJudgment();
    bool winnerJudgment();
    void AIPlay();
    void AIAttack(QVector<int> categorys);
    QVector<int> roundErgodic(int x, int y, int pm);
    QVector<int> typesConvert(QVector<int> types, int pm);
    int WeightedCalculation(QVector<int> types, int pm);
    

public slots:
    void backMove();
    void createNewChessMap();
    QVector<int> saveChessMap();

signals:
    void chessPlayingDone();
    void pieceChangedSgn();
    void winnerSgn(int winner);
};

#endif // !CHESS_H
