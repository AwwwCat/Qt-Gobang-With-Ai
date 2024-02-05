#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "../Headers/define.h"
#include <QColor>
#include <QPainter>
#include <QPainterPath>
#include <QPaintEvent>
#include <QResizeEvent>
#include <QWidget>
#include <cmath>

enum PieceMode {
    None, Black, White
};

class ChessBoard : public QWidget
{
    Q_OBJECT

public:
    int cellSize = 80;
    int cellNum = 14;
    int startX = 50;
    int startY = 50;
    int pieceR = 35;
    int lianzhuNum = 5;

    QColor chessBoardColor = DEFAULT_CHESS_BOARD_COLOR;
    QColor chessLineColor = DEFAULT_CHESS_LINE_COLOR;
    QColor pieceAColor = DEFAULT_PIECE_A_COLOR;
    QColor pieceBColor = DEFAULT_PIECE_B_COLOR;

    explicit ChessBoard(QWidget* parent = nullptr);
    virtual ~ChessBoard();

    void loadChessMap(int order, QVector<QVector<int>> chessOrder);

protected:
    int order;
    QVector<QVector<int>> chessMap;
    QVector<QVector<int>> chessOrder;

    void boardDraw(QPainter& painter);
    void pointDraw(QPainter& painter);
    void pieceDraw(QPainter& painter);
    virtual void paintEvent(QPaintEvent* e);

    void createNewChessBoard();

    void boardCalculation(int maxLen, int minLen, int& maxStart, int& minStart);
    void boardCalculation(int sameLen);
    void boardResize();
    void resizeEvent(QResizeEvent* e);
};

#endif // !CHESSBOARD_H