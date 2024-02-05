#include "../Headers/ChessBoard.h"

ChessBoard::ChessBoard(QWidget* parent) : QWidget(parent)
{
    createNewChessBoard();
}

ChessBoard::~ChessBoard()
{

}

void ChessBoard::loadChessMap(int order, QVector<QVector<int>> chessOrder)
{
    createNewChessBoard();

    this->order = order;
    this->chessOrder = chessOrder;

    for (int i = 0; i < pow(cellNum + 1, 2) && chessOrder[i][0] != -1; i++)
    {
        chessMap[chessOrder[i][0]][chessOrder[i][1]] = i % 2 + 1;
    }

    update();
}

void ChessBoard::boardDraw(QPainter& painter)
{
    painter.setPen(chessBoardColor);
    painter.setBrush(chessBoardColor);
    int minLen = fmin(startX, startY);
    painter.drawRect(startX - minLen, startY - minLen, cellNum * cellSize + 2 * minLen, cellNum * cellSize + 2 * minLen);

    painter.setPen(chessLineColor);
    QFont font;
    font.setFamily("Microsoft Yahei");
    font.setPixelSize(cellSize / 3);

    painter.setFont(font);
    for (int i = 0; i < cellNum + 1; i++)
    {
        painter.drawText(startX - minLen, i * cellSize + startY - cellSize / 2, minLen - 10, cellSize, Qt::AlignCenter, QString::number(i + 1));
        painter.drawText(i * cellSize + startX - cellSize / 2, startY + cellNum * cellSize + 10, cellSize, minLen - 10, Qt::AlignCenter, QString(char(i + 65)));
    }

    painter.setBrush(chessLineColor);
    painter.setPen(chessLineColor);
    for (int i = 0; i < cellNum + 1; i++)
    {
        painter.drawLine(startX, i * cellSize + startY, cellNum * cellSize + startX, i * cellSize + startY);
        painter.drawLine(i * cellSize + startX, startY, i * cellSize + startX, cellNum * cellSize + startY);
    }
    
    painter.drawRect(startX - 10, startY - 11, cellNum * cellSize + 20, 5);
    painter.drawRect(startX - 10, startY + cellNum * cellSize + 5, cellNum * cellSize + 20, 5);

    painter.drawRect(startX - 10, startY - 11, 5, cellNum * cellSize + 20);
    painter.drawRect(startX + cellNum * cellSize + 5, startY - 10, 5, cellNum * cellSize + 20);
}

void ChessBoard::pointDraw(QPainter& painter)
{
    painter.setBrush(chessLineColor);
    painter.setPen(chessLineColor);
    int pointR = cellSize / 10;
    if (cellNum == 4)
    {
        int midPoint = cellNum / 2;
        painter.drawEllipse(midPoint * cellSize + startX - pointR, midPoint * cellSize + startY - pointR, pointR * 2, pointR * 2);
    }
    else
    {
        int midPoint = cellNum / 2;
        int aroundPoint = (midPoint - 1) / 2;
        if (cellNum % 2 == 0)
            painter.drawEllipse(midPoint * cellSize + startX - pointR, midPoint * cellSize + startY - pointR, pointR * 2, pointR * 2);
        else
            aroundPoint += 1;
        painter.drawEllipse(aroundPoint * cellSize + startX - pointR, aroundPoint * cellSize + startY - pointR, pointR * 2, pointR * 2);
        painter.drawEllipse((cellNum - aroundPoint) * cellSize + startX - pointR, aroundPoint * cellSize + startY - pointR, pointR * 2, pointR * 2);
        painter.drawEllipse((cellNum - aroundPoint) * cellSize + startX - pointR, (cellNum - aroundPoint) * cellSize + startY - pointR, pointR * 2, pointR * 2);
        painter.drawEllipse(aroundPoint * cellSize + startX - pointR, (cellNum - aroundPoint) * cellSize + startY - pointR, pointR * 2, pointR * 2);
    }
}

void ChessBoard::pieceDraw(QPainter& painter)
{
    for (int i = 0; i < cellNum + 1; i++)
        for (int j = 0; j < cellNum + 1; j++)
        {
            if (order > 0 && chessOrder[order - 1][0] == i && chessOrder[order - 1][1] == j)
            {
                painter.setPen(QPen(QColor(255, 0, 0), 3));
                if (chessMap[chessOrder[order - 1][0]][chessOrder[order - 1][1]] == Black)
                {
                    painter.setBrush(pieceAColor);
                }
                else if (chessMap[chessOrder[order - 1][0]][chessOrder[order - 1][1]] == White)
                {
                    painter.setBrush(pieceBColor);
                }
                painter.drawEllipse(chessOrder[order - 1][0] * cellSize + startX - pieceR, chessOrder[order - 1][1] * cellSize + startY - pieceR, pieceR * 2, pieceR * 2);
                continue;
            }
            painter.setPen(QPen(QColor(0, 0, 0), 1));
            if (chessMap[i][j] == Black)
            {
                painter.setBrush(pieceAColor);
                painter.drawEllipse(i * cellSize + startX - pieceR, j * cellSize + startY - pieceR, pieceR * 2, pieceR * 2);
            }
            else if (chessMap[i][j] == White)
            {
                painter.setBrush(pieceBColor);
                painter.drawEllipse(i * cellSize + startX - pieceR, j * cellSize + startY - pieceR, pieceR * 2, pieceR * 2);
            }
            
        }
    
    
}

void ChessBoard::paintEvent(QPaintEvent* e)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(QColor(0, 0, 0), 1));

    boardDraw(painter);
    pointDraw(painter);
    pieceDraw(painter);
}

void ChessBoard::createNewChessBoard()
{
    boardResize();

    chessMap.clear();
    chessOrder.clear();

    chessMap.fill(QVector<int>(cellNum + 1, 0), cellNum + 1);
    chessOrder.fill(QVector<int>(2, -1), pow(cellNum + 1, 2));

    order = 0;

    update();
}

void ChessBoard::boardCalculation(int maxLen, int minLen, int& maxStart, int& minStart)
{
    int boardLength = minLen - 21;
    int exLength = boardLength % (cellNum + 1);
    cellSize = boardLength / (cellNum + 1);
    pieceR = cellSize / 2 - cellSize / 15;
    maxStart = (maxLen - boardLength + exLength) / 2 + pieceR + 15 + cellSize / 15;
    minStart = exLength / 2 + pieceR + 10 + cellSize / 15;
}

void ChessBoard::boardCalculation(int sameLen)
{
    int boardLength = sameLen - 21;
    int exLength = boardLength % (cellNum + 1);
    cellSize = boardLength / (cellNum + 1);
    pieceR = cellSize / 2 - cellSize / 15;
    startX = startY = exLength / 2 + pieceR + 10 + cellSize / 15;
}

void ChessBoard::boardResize()
{
    if (this->width() > this->height())
        boardCalculation(this->width(), this->height(), startX, startY);
    else if (this->width() < this->height())
        boardCalculation(this->height(), this->width(), startY, startX);
    else
        boardCalculation(this->width());
}

void ChessBoard::resizeEvent(QResizeEvent* e)
{
    boardResize();
}