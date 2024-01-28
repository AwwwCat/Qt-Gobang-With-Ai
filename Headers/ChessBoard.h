#ifndef CHESSBOARD_H
#define CHESSBOARD_H

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

    QColor chessBoardColor = QColor(247, 230, 182, 255);
    QColor pieceAColor = QColor(0, 0, 0, 255);
    QColor pieceBColor = QColor(255, 255, 255, 255);

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