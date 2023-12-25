#ifndef CHESS_H
#define CHESS_H

#define CELL_SIZE 80
#define CELL_NUM 14
#define START_X 50
#define START_Y 50
#define TopDistance 25
#define PIECE_R 35
#define LIANZHU_NUM 5

#include <QWidget>
#include <QPen>
#include <QPainter>
#include <QPainterPath>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QColor>
#include <QTimer>
#include <QTime>
#include <QtGlobal>
#include <QRandomGenerator>
#include <QStack>
#include <QMessageBox>
#include <QPushButton>
#include <string>
#include <cmath>

enum PieceMode {
    None, Black, White
};

enum Gamemode {
    Noplay, PvP, PvC
};

enum SingleTypes {
    OP, OXP, WXP, OXXP, WXXP, OXXXP, WXXXP, OXXXXP, WXXXXP
};

class Chess : public QWidget
{
    Q_OBJECT
public:
    explicit Chess(QWidget *parent = nullptr);
    virtual ~Chess() {};

    int pieceMode;
    int gameMode = Noplay;
    bool showPiece = true;
    bool showOrder = false;
    bool showScore = false;
    QStack<int> chessStack;
    QColor pieceAColor;
    QColor pieceBColor;

public slots:
    void cleanChessboard();

signals:
    void pieceSgn(int piecemode);
    void winnerSgn(int winner);

private:
    int direction[8][2] = {{0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};
    int pieceX, pieceY;
    int order;
    int chessMap[CELL_NUM+1][CELL_NUM+1];
    int chessOrder[(CELL_NUM+1)*(CELL_NUM+1)][2];
    int scoreMap[CELL_NUM+1][CELL_NUM+1];

    void AIPlay();
    int WeightedCalculation(int types[8], int pm);

    void paintEvent(QPaintEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
};

#endif // CHESS_H
