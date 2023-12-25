#include "chess.h"

Chess::Chess(QWidget *parent) : QWidget(parent)
{
    setMouseTracking(true);
    setGeometry(0, TopDistance, START_X*2+CELL_NUM*CELL_SIZE+1, START_Y*2+CELL_NUM*CELL_SIZE+1);
    gameMode = Noplay;
    pieceAColor = QColor(0, 0, 0, 255);
    pieceBColor = QColor(255, 255,255, 255);

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    cleanChessboard();
}

// 画图事件
void Chess::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(QColor(0, 0, 0), 1));

    // 画棋盘
    for(int i = 0; i < CELL_NUM+1; i++)
    {
        painter.drawLine(START_X, i*CELL_SIZE+START_Y, CELL_NUM*CELL_SIZE+START_X, i*CELL_SIZE+START_Y);
        painter.drawLine(i*CELL_SIZE+START_X, START_Y, i*CELL_SIZE+START_X, CELL_NUM*CELL_SIZE+START_Y);
    }

    // 画棋盘上五个黑点
    painter.setBrush(QColor(0, 0, 0, 255));
    painter.drawEllipse(7*CELL_SIZE+START_X-10, 7*CELL_SIZE+START_Y-10, 20, 20);
    painter.drawEllipse(3*CELL_SIZE+START_X-10, 3*CELL_SIZE+START_Y-10, 20, 20);
    painter.drawEllipse(11*CELL_SIZE+START_X-10, 3*CELL_SIZE+START_Y-10, 20, 20);
    painter.drawEllipse(11*CELL_SIZE+START_X-10, 11*CELL_SIZE+START_Y-10, 20, 20);
    painter.drawEllipse(3*CELL_SIZE+START_X-10, 11*CELL_SIZE+START_Y-10, 20, 20);

    // 画将要下的棋子
    if (pieceX != -1 && pieceY != -1 && gameMode != Noplay && showPiece)
    {
        if (pieceMode == Black)
            painter.setBrush(pieceAColor);
        else if (pieceMode == White)
            painter.setBrush(pieceBColor);
        painter.drawEllipse(pieceX*CELL_SIZE+START_X-PIECE_R, pieceY*CELL_SIZE+START_Y-PIECE_R, PIECE_R*2, PIECE_R*2);
    }



    // 画棋盘上已有的棋子
    painter.setPen(QPen(QColor(0, 0, 0), 1));
    for (int i = 0; i < CELL_NUM+1; i++)
        for (int j = 0; j < CELL_NUM+1; j++)
        {
            if (chessMap[i][j] == Black)
            {
                painter.setBrush(pieceAColor);
                painter.drawEllipse(i*CELL_SIZE+START_X-PIECE_R, j*CELL_SIZE+START_Y-PIECE_R, PIECE_R*2, PIECE_R*2);
            }
            else if (chessMap[i][j] == White)
            {
                painter.setBrush(pieceBColor);
                painter.drawEllipse(i*CELL_SIZE+START_X-PIECE_R, j*CELL_SIZE+START_Y-PIECE_R, PIECE_R*2, PIECE_R*2);
            }
        }

    // Debug模式：权重
    if (showScore)
    {
        painter.setPen(QPen(QColor(255, 0, 255), 2));
        for (int i = 0; i < CELL_NUM+1; i++)
                for (int j = 0; j < CELL_NUM+1; j++)
                {
                    painter.drawText(i*CELL_SIZE+START_X-4, j*CELL_SIZE+START_Y+12, QString::number(scoreMap[i][j]));
                }
    }

    // 下棋顺序
    if (showOrder)
    {
        painter.setPen(QPen(QColor(255, 0, 0), 2));
        for (int i = 0; i < pow(CELL_NUM+1, 2) && chessOrder[i][0] != -1; i++)
        {
            painter.setBrush(QColor(255, 0, 0));
            painter.drawText(chessOrder[i][0]*CELL_SIZE+START_X-4, chessOrder[i][1]*CELL_SIZE+START_Y, QString::number(i+1));
        }
    }
}

// 鼠标移动事件
void Chess::mouseMoveEvent(QMouseEvent *e)
{
    int cx = e->x() - START_X;
    int cy = e->y() - START_Y;

    int pieceDX = ((cx % CELL_SIZE) > (CELL_SIZE / 2) ? CELL_SIZE : 0) - cx % CELL_SIZE;
    int pieceDY = ((cy % CELL_SIZE) > (CELL_SIZE / 2) ? CELL_SIZE : 0) - cy % CELL_SIZE;

    pieceX = cx/CELL_SIZE + ((cx % CELL_SIZE) > (CELL_SIZE / 2));
    pieceY = cy/CELL_SIZE + ((cy % CELL_SIZE) > (CELL_SIZE / 2));

    int pieceDistance = std::sqrt(std::pow(pieceDX, 2) + std::pow(pieceDY, 2));

    pieceX = (pieceX >= 0 && pieceX <= CELL_NUM && pieceDistance <= PIECE_R) ? pieceX : -1;
    pieceY = (pieceY >= 0 && pieceY <= CELL_NUM && pieceDistance <= PIECE_R) ? pieceY : -1;

    update();
}

// 鼠标点击事件
void Chess::mousePressEvent(QMouseEvent *e)
{
    // 玩家对战
    if (pieceX != -1 && pieceY != -1 && chessMap[pieceX][pieceY] == None && gameMode == PvP)
    {
        chessMap[pieceX][pieceY] = pieceMode;
        chessOrder[order][0] = pieceX;
        chessOrder[order][1] = pieceY;
        order++;

        int directLine[4] = {0};
        bool changePiece = true;

        for (int i = 0; i < 8; i++)
            for (int j = 1; j < LIANZHU_NUM; j++)
            {
                int px = pieceX+j*direction[i][0];
                int py = pieceY+j*direction[i][1];

                if (px <= CELL_NUM && px >= 0 && py <= CELL_NUM && py >= 0)
                {
                    if (chessMap[px][py] == pieceMode)
                    {
                        directLine[i%4] += 1;
                        if (directLine[i%4] == LIANZHU_NUM-1)
                        {
                            emit winnerSgn(pieceMode);
                            changePiece = false;
                        }
                    }
                    else
                    {
                        break;
                    }
                }

            }
        if (changePiece == true)
        {
            pieceMode = (pieceMode == Black) ? White : Black;
            emit pieceSgn(pieceMode);
        }
    }
    // ai下棋
    else if (pieceX != -1 && pieceY != -1 && chessMap[pieceX][pieceY] == None && gameMode == PvC)
    {
         chessMap[pieceX][pieceY] = pieceMode;
         chessOrder[order][0] = pieceX;
         chessOrder[order][1] = pieceY;
         order++;
         int directLine[4] = {0};
         bool changePiece = true;

         for (int i = 0; i < 8; i++)
             for (int j = 1; j < LIANZHU_NUM; j++)
             {
                 int px = pieceX+j*direction[i][0];
                 int py = pieceY+j*direction[i][1];

                 if (px <= CELL_NUM && px >= 0 && py <= CELL_NUM && py >= 0)
                 {
                     if (chessMap[px][py] == pieceMode)
                     {
                         directLine[i%4] += 1;
                         if (directLine[i%4] == LIANZHU_NUM-1)
                         {
                             emit winnerSgn(pieceMode);
                             changePiece = false;
                         }
                     }
                     else
                     {
                         break;
                     }
                 }

             }
         if (changePiece == true)
         {
             AIPlay();
             pieceMode = (pieceMode == Black) ? White : Black;
             emit pieceSgn(pieceMode);
         }
         update();

    }

    update();
}

// 清空棋盘
void Chess::cleanChessboard()
{
    pieceMode = Black;
    for (int i = 0; i < CELL_NUM+1; i++)
        for (int j = 0; j < CELL_NUM+1; j++)
        {
            chessMap[i][j] = 0;
        }
    for (int i = 0; i < pow(CELL_NUM+1, 2); i++)
    {
        chessOrder[i][0] = chessOrder[i][1] = -1;
    }
    order = 0;
    for (int i = 0; i <= CELL_NUM; i++)
    {
        for (int j = 0; j <= CELL_NUM; j++)
        {
            scoreMap[i][j] = 0;
        }
    }
    emit pieceSgn(pieceMode);
    update();
}

// ai算法
void Chess::AIPlay()
{
    bool changePiece = true;
    int maxScore = 0;

    int maxScoreMap[8][2];
    int mx = -1, my = -1;

    for (int i = 0; i < 8; i++)
    {
        maxScoreMap[i][0] = maxScoreMap[i][1] = -1;
    }

    // 清空权重表
    for (int i = 0; i <= CELL_NUM; i++)
    {
        for (int j = 0; j <= CELL_NUM; j++)
        {
            scoreMap[i][j] = 0;
        }
    }

    // 遍历所有空位判断周围八个方向类型
    for (int i = 0; i <= CELL_NUM; i++)
    {
        for (int j = 0; j <= CELL_NUM; j++)
        {
            if (chessMap[i][j] == None && gameMode != Noplay)
            {
                int roundType[8] = {0};
                // 遍历黑子
                for (int m = 0; m < 8; m++)
                {
                    if (roundType[m] == 0)
                        for (int n = 1; n <= LIANZHU_NUM; n++)
                        {
                            int px = i+n*direction[m][0];
                            int py = j+n*direction[m][1];

                            if (px <= CELL_NUM && px >= 0 && py <= CELL_NUM && py >= 0)
                            {
                                if (chessMap[px][py] == Black)
                                    roundType[m] += 1;
                                else if (chessMap[px][py] == None && roundType[m] != 0)
                                {
                                    roundType[m] = roundType[m]*2-1;
                                    break;
                                } else if (chessMap[px][py] == White && roundType[m] != 0)
                                {
                                    roundType[m] = roundType[m]*2;
                                    break;
                                } else
                                    break;
                            }
                        }
                }

                // 遍历白子
                for (int m = 0; m < 8; m++)
                {
                    if (roundType[m] == 0)
                        for (int n = 1; n <= LIANZHU_NUM; n++)
                        {
                            int px = i+n*direction[m][0];
                            int py = j+n*direction[m][1];

                            if (px <= CELL_NUM && px >= 0 && py <= CELL_NUM && py >= 0)
                            {
                                if (chessMap[px][py] == White)
                                    roundType[m] += 1;
                                else if (chessMap[px][py] == None && roundType[m] != 0)
                                {
                                    roundType[m] = roundType[m]*2-1+WXXXXP;
                                    break;
                                } else if (chessMap[px][py] == Black && roundType[m] != 0)
                                {
                                    roundType[m] = roundType[m]*2+WXXXXP;
                                    break;
                                } else
                                    break;
                            }
                        }
                }
                scoreMap[i][j] += WeightedCalculation(roundType, Black);
            }
        }
    }

    // 查找最大权重
    for (int i = 0; i <= CELL_NUM; i++)
    {
        for (int j = 0; j <= CELL_NUM; j++)
        {
            if (scoreMap[i][j] > maxScore)
            {
                maxScore = scoreMap[i][j];
            }
        }
    }

    // 寻找所有最大权重坐标
    int k = 0;
    int maxnum = 0;
    for (int i = 0; i <= CELL_NUM && maxnum < 8; i++)
    {
        for (int j = 0; j <= CELL_NUM && maxnum < 8; j++)
        {
            if (scoreMap[i][j] == maxScore)
            {
                maxScoreMap[k][0] = i;
                maxScoreMap[k][1] = j;
                k++;
                maxnum++;
            }
        }
    }

    // 获取随机坐标
    QRandomGenerator rg(QDateTime::currentMSecsSinceEpoch());
    int r = rg.bounded(maxnum);
    mx = maxScoreMap[r][0];
    my = maxScoreMap[r][1];


    // 放置棋子
    if (mx != -1 && my != -1)
    {
        chessMap[mx][my] = White;
        chessOrder[order][0] = mx;
        chessOrder[order][1] = my;
        order++;
    }

    // 判断胜负
    if (mx != -1 && mx != -1 && gameMode != Noplay)
    {
        int directLine[4] = {0};
        bool changePiece = true;

        for (int i = 0; i < 8; i++)
        {
            for (int j = 1; j < LIANZHU_NUM; j++)
            {
                int px = mx+j*direction[i][0];
                int py = my+j*direction[i][1];

                if (px <= CELL_NUM && px >= 0 && py <= CELL_NUM && py >= 0)
                {
                    if (chessMap[px][py] == White)
                    {
                        directLine[i%4] += 1;
                        if (directLine[i%4] == LIANZHU_NUM-1)
                        {
                            emit winnerSgn(White);
                            changePiece = false;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
            }
        }
    }

    if (changePiece == true)
    {
        pieceMode = (pieceMode == Black) ? White : Black;
        emit pieceSgn(pieceMode);
    }

    update();
}

// 加权运算
int Chess::WeightedCalculation(int types[8], int pm)
{
    int weight = 0;
    enum Categorys {
        Kill, DeadFive, LiveFour, DeadFour, LiveThree, DeadThree, LiveTwo, DeadTwo, LiveOne, DeadOne, TwoLiveTwo, AllCategorys
    };
    int categorysB[AllCategorys] = {0};
    int categorysW[AllCategorys] = {0};


    // 棋形分析
    /* Black */
    // 杀棋：OXXXXP
    for (int i = 0; i < 8; i++)
    {
        // OXXXXP
        if (types[i] == OXXXXP)
            categorysB[LiveFour] += 1;
    }

    // 死五：WXXPXXXO WXXPXXXW OXXPXXXW WXXXXPXO WXXXXPXW
    for (int i = 0; i < 4; i++)
    {
        // WXXPXXXO
        if ((types[i] == OXXXP && types[i+4] == WXXP) || (types[i] == WXXP && types[i+4] == OXXXP))
            categorysB[LiveFour] += 1;
        // WXXPXXXW
        else if ((types[i] == WXXP && types[i+4] == WXXXP) || (types[i] == WXXXP && types[i+4] == WXXP))
            categorysB[LiveFour] += 1;
        // OXXPXXXW
        else if ((types[i] == OXXP && types[i+4] == WXXXP) || (types[i] == WXXXP && types[i+4] == OXXP))
            categorysB[LiveFour] += 1;
        // WXXXXPXO
        else if ((types[i] == WXXXXP && types[i+4] == OXP) || (types[i] == OXP && types[i+4] == WXXXXP))
            categorysB[LiveFour] += 1;
        // WXXXXPXW
        else if ((types[i] == WXXXXP && types[i+4] == WXP) || (types[i] == WXP && types[i+4] == WXXXXP))
            categorysB[LiveFour] += 1;
    }

    // 活四：OXXXPXO OXXPXXO
    for (int i = 0; i < 4; i++)
    {
        // OXXPXXO
        if (types[i] == OXXP && types[i+4] == OXXP)
            categorysB[LiveFour] += 1;
        // OXXXPXO
        else if ((types[i] == OXP && types[i+4] == OXXXP) || (types[i] == OXXXP && types[i+4] == OXP))
            categorysB[LiveFour] += 1;
    }

    // 死四：WXXXXP WXXXPXO WXXPXXO WXXXPXW
    for (int i = 0; i < 4; i++)
    {
        // WXXPXXO
        if ((types[i] == WXXP && types[i+4] == OXXP) || (types[i] == OXXP && types[i+4] == WXXP))
            categorysB[DeadFour] += 1;
        // WXXXPXO
        else if ((types[i] == WXXXP && types[i+4] == OXP) || (types[i] == OXP && types[i+4] == WXXXP))
            categorysB[DeadFour] += 1;
        // OXXXPXW
        else if ((types[i] == WXP && types[i+4] == OXXXP) || (types[i] == OXXXP && types[i+4] == WXP))
            categorysB[DeadFour] += 1;
        // WXXXPXW
        else if ((types[i] == WXP && types[i+4] == WXXXP) || (types[i] == WXXXP && types[i+4] == WXP))
            categorysB[DeadFour] += 1;
    }
    for (int i = 0; i < 8; i++)
    {
        // WXXXXP
        if (types[i] == WXXXXP)
            categorysB[DeadFour] += 1;
    }

    // 活三：OXXXPO OXXPXO
    for (int i = 0; i < 4; i++)
    {
        // OXXPXO
        if ((types[i] == OXXP && types[i+4] == OXP) || (types[i] == OXP && types[i+4] == OXXP))
            categorysB[LiveThree] += 1;
        // OXXXPO
        else if ((types[i] == OXXXP && types[i+4] == OP) || (types[i] == OP && types[i+4] == OXXXP))
            categorysB[LiveThree] += 1;
    }

    // 死三：WXXXPO WXXPXO WXPXXO
    for (int i = 0; i < 4; i++)
    {
        // WXXPXO
        if ((types[i] == WXXP && types[i+4] == OXP) || (types[i] == OXP && types[i+4] == WXXP))
            categorysB[DeadThree] += 1;
        // WXPXXO
        else if ((types[i] == WXP && types[i+4] == OXXP) || (types[i] == OXXP && types[i+4] == WXP))
            categorysB[DeadThree] += 1;
        // WXXXPO
        else if ((types[i] == WXXXP && types[i+4] == OP) || (types[i] == OP && types[i+4] == WXXXP))
            categorysB[DeadThree] += 1;
    }

    // 活二：OXXPO OXPXO
    for (int i = 0; i < 4; i++)
    {
        // OXPXO
        if (types[i] == OXP && types[i+4] == OXP)
            categorysB[LiveTwo] += 1;
        else if ((types[i] == OXXP && types[i+4] == OP) || (types[i] == OP && types[i+4] == OXXP))
            categorysB[DeadThree] += 1;
    }

    // 死二：WXXPO WXPXO WXPXW
    for (int i = 0; i < 4; i++)
    {
        // WXPXO
        if ((types[i] == WXP && types[i+4] == OXP) || (types[i] == OXP && types[i+4] == WXP))
            categorysB[DeadTwo] += 1;
        // WXPXW
        else if (types[i] == WXP && types[i+4] == WXP)
            categorysB[DeadTwo] += 1;
        // WXXPO
        else if ((types[i] == WXXP && types[i+4] == OP) || (types[i] == OP && types[i+4] == WXXP))
            categorysB[DeadTwo] += 1;
    }

    // 活一：OXPO
    for (int i = 0; i < 4; i++)
    {
        // OXPO
        if ((types[i] == OXP && types[i+4] == OP) || (types[i] == OP && types[i+4] == OXP))
            categorysB[LiveOne] += 1;
    }

    // 死一：WXPO
    for (int i = 0; i < 4; i++)
    {
        // WXPO
        if ((types[i] == WXP && types[i+4] == OP) || (types[i] == OP && types[i+4] == WXP))
            categorysB[DeadOne] += 1;
    }

    /* White */
    // 杀棋：OXXXXP
    for (int i = 0; i < 8; i++)
    {
        // OXXXXP
        if (types[i]-8 == OXXXXP)
            categorysW[LiveFour] += 1;
    }

    // 死五：WXXPXXXO WXXPXXXW OXXPXXXW WXXXXPXO WXXXXPXW
    for (int i = 0; i < 4; i++)
    {
        // WXXPXXXO
        if ((types[i]-8 == OXXXP && types[i+4]-8 == WXXP) || (types[i]-8 == WXXP && types[i+4]-8 == OXXXP))
            categorysW[LiveFour] += 1;
        // WXXPXXXW
        else if ((types[i]-8 == WXXP && types[i+4]-8 == WXXXP) || (types[i]-8 == WXXXP && types[i+4]-8 == WXXP))
            categorysW[LiveFour] += 1;
        // OXXPXXXW
        else if ((types[i]-8 == OXXP && types[i+4]-8 == WXXXP) || (types[i]-8 == WXXXP && types[i+4]-8 == OXXP))
            categorysW[LiveFour] += 1;
        // WXXXXPXO
        else if ((types[i]-8 == WXXXXP && types[i+4]-8 == OXP) || (types[i]-8 == OXP && types[i+4]-8 == WXXXXP))
            categorysW[LiveFour] += 1;
        // WXXXXPXW
        else if ((types[i]-8 == WXXXXP && types[i+4]-8 == WXP) || (types[i]-8 == WXP && types[i+4]-8 == WXXXXP))
            categorysW[LiveFour] += 1;
    }

    // 活四：OXXXPXO OXXPXXO
    for (int i = 0; i < 4; i++)
    {
        // OXXPXXO
        if (types[i]-8 == OXXP && types[i+4]-8 == OXXP)
            categorysW[LiveFour] += 1;
        // OXXXPXO
        else if ((types[i]-8 == OXP && types[i+4]-8 == OXXXP) || (types[i]-8 == OXXXP && types[i+4]-8 == OXP))
            categorysW[LiveFour] += 1;
    }

    // 死四：WXXXXP WXXXPXO WXXPXXO WXXXPXW
    for (int i = 0; i < 4; i++)
    {
        // WXXPXXO
        if ((types[i]-8 == WXXP && types[i+4]-8 == OXXP) || (types[i]-8 == OXXP && types[i+4]-8 == WXXP))
            categorysW[DeadFour] += 1;
        // WXXXPXO
        else if ((types[i]-8 == WXXXP && types[i+4]-8 == OXP) || (types[i]-8 == OXP && types[i+4]-8 == WXXXP))
            categorysW[DeadFour] += 1;
        // OXXXPXW
        else if ((types[i]-8 == WXP && types[i+4]-8 == OXXXP) || (types[i]-8 == OXXXP && types[i+4]-8 == WXP))
            categorysW[DeadFour] += 1;
        // WXXXPXW
        else if ((types[i]-8 == WXP && types[i+4]-8 == WXXXP) || (types[i]-8 == WXXXP && types[i+4]-8 == WXP))
            categorysW[DeadFour] += 1;
    }
    for (int i = 0; i < 8; i++)
    {
        // WXXXXP
        if (types[i]-8 == WXXXXP)
            categorysW[DeadFour] += 1;
    }

    // 活三：OXXXPO OXXPXO
    for (int i = 0; i < 4; i++)
    {
        // OXXPXO
        if ((types[i]-8 == OXXP && types[i+4]-8 == OXP) || (types[i]-8 == OXP && types[i+4]-8 == OXXP))
            categorysW[LiveThree] += 1;
        // OXXXPO
        else if ((types[i]-8 == OXXXP && types[i+4] == OP) || (types[i] == OP && types[i+4]-8 == OXXXP))
            categorysW[LiveThree] += 1;
    }

    // 死三：WXXXPO WXXPXO WXPXXO
    for (int i = 0; i < 4; i++)
    {
        // WXXPXO
        if ((types[i]-8 == WXXP && types[i+4]-8 == OXP) || (types[i]-8 == OXP && types[i+4]-8 == WXXP))
            categorysW[DeadThree] += 1;
        // WXPXXO
        else if ((types[i]-8 == WXP && types[i+4]-8 == OXXP) || (types[i]-8 == OXXP && types[i+4]-8 == WXP))
            categorysW[DeadThree] += 1;
        // WXXXPO
        else if ((types[i]-8 == WXXXP && types[i+4] == OP) || (types[i] == OP && types[i+4]-8 == WXXXP))
            categorysW[DeadThree] += 1;
    }

    // 活二：OXXPO OXPXO
    for (int i = 0; i < 4; i++)
    {
        // OXPXO
        if (types[i]-8 == OXP && types[i+4]-8 == OXP)
            categorysW[LiveTwo] += 1;
        else if ((types[i]-8 == OXXP && types[i+4] == OP) || (types[i] == OP && types[i+4]-8 == OXXP))
            categorysW[DeadThree] += 1;
    }

    // 死二：WXXPO WXPXO WXPXW
    for (int i = 0; i < 4; i++)
    {
        // WXPXO
        if ((types[i]-8 == WXP && types[i+4]-8 == OXP) || (types[i]-8 == OXP && types[i+4]-8 == WXP))
            categorysW[DeadTwo] += 1;
        // WXPXW
        else if (types[i]-8 == WXP && types[i+4]-8 == WXP)
            categorysW[DeadTwo] += 1;
        // WXXPO
        else if ((types[i]-8 == WXXP && types[i+4] == OP) || (types[i] == OP && types[i+4]-8 == WXXP))
            categorysW[DeadTwo] += 1;
    }

    // 活一：OXPO
    for (int i = 0; i < 4; i++)
    {
        // OXPO
        if ((types[i]-8 == OXP && types[i+4] == OP) || (types[i] == OP && types[i+4]-8 == OXP))
            categorysW[LiveOne] += 1;
    }

    // 死一：WXPO
    for (int i = 0; i < 4; i++)
    {
        // WXPO
        if ((types[i]-8 == WXP && types[i+4] == OP) || (types[i] == OP && types[i+4]-8 == WXP))
            categorysW[DeadOne] += 1;
    }

    if (categorysB[DeadThree] + categorysB[LiveTwo] >= 2)
        categorysB[TwoLiveTwo] = 1;

    if (categorysW[DeadThree] + categorysW[LiveTwo] >= 2)
        categorysW[TwoLiveTwo] = 1;

//    if (categorysB[DeadThree] >= 2)
//    {
//        categorysB[DeadThree] = 0;
//        categorysB[DeadFour] += 1;
//    }
//    if (categorysB[LiveTwo] >= 2)
//    {
//        categorysB[LiveTwo] = 0;
//        categorysB[LiveThree] += 1;
//    }
//    if (categorysB[DeadTwo] >= 2 || categorysB[DeadTwo] + categorysB[LiveTwo] >= 2)
//    {
//        categorysB[DeadTwo] = 0;
//        categorysB[DeadThree] += 1;
//    }
//    if (categorysB[LiveOne] >= 2)
//    {
//        categorysB[LiveOne] = 0;
//        categorysB[LiveTwo] += 1;
//    }
//    if (categorysB[DeadOne] >= 2 || categorysB[DeadOne] + categorysB[LiveOne] >= 2)
//    {
//        categorysB[DeadOne] = 0;
//        categorysB[DeadTwo] += 1;
//    }

//    if (categorysW[DeadThree] >= 2)
//    {
//        categorysW[DeadThree] = 0;
//        categorysW[DeadFour] += 1;
//    }
//    if (categorysW[LiveTwo] >= 2)
//    {
//        categorysW[LiveTwo] = 0;
//        categorysW[LiveThree] += 1;
//    }
//    if (categorysW[DeadTwo] >= 2 || categorysW[DeadTwo] + categorysW[LiveTwo] >= 2)
//    {
//        categorysW[DeadTwo] = 0;
//        categorysW[DeadThree] += 1;
//    }
//    if (categorysW[LiveOne] >= 2)
//    {
//        categorysW[LiveOne] = 0;
//        categorysW[LiveTwo] += 1;
//    }
//    if (categorysW[DeadOne] >= 2 || categorysW[DeadOne] + categorysW[LiveOne] >= 2)
//    {
//        categorysW[DeadOne] = 0;
//        categorysW[DeadTwo] += 1;
//    }

    weight += categorysB[DeadOne] * 1;
    weight += categorysB[LiveOne] * 2;
    weight += categorysB[DeadTwo] * 5;
    weight += categorysB[LiveTwo] * 10;
    weight += categorysB[DeadThree] * 20;
    weight += categorysB[TwoLiveTwo] * 100;
    weight += categorysB[LiveThree] * 150;
    weight += categorysB[DeadFour] * 500;
    weight += categorysB[LiveFour] * 500;
    weight += categorysB[DeadFive] * 500;
    weight += categorysB[Kill] * 1000;

    weight += categorysW[DeadOne] * 0;
    weight += categorysW[LiveOne] * 1;
    weight += categorysW[DeadTwo] * 2;
    weight += categorysW[LiveTwo] * 5;
    weight += categorysW[DeadThree] * 10;
    weight += categorysW[TwoLiveTwo] * 120;
    weight += categorysW[LiveThree] * 200;
    weight += categorysW[DeadFour] * 1000;
    weight += categorysW[LiveFour] * 1000;
    weight += categorysW[DeadFive] * 1000;
    weight += categorysW[Kill] * 2000;


//    if (pm == Black)
//    {
//        int typesNum[9] = {0};
//        for (int i = 0; i < 8; i++)
//        {
//            for (int j = 0; j < 8; j++)
//            {
//                if (types[j] == i)
//                    typesNum[i]++;
//            }
//        }

//        weight += pow(2, typesNum[OXP]);
//        weight += pow(1, typesNum[WXP]);
//        weight += pow(8, typesNum[OXXP]);
//        weight += pow(2, typesNum[WXXP]);
//        weight += pow(128, typesNum[OXXXP]);
//        weight += pow(8, typesNum[WXXXP]);
//        weight += pow(128, typesNum[OXXXXP]);
//        weight += pow(128, typesNum[WXXXXP]);
//    }
//    else if (pm == White)
//    {
//        int typesNum[9] = {0};
//        for (int i = 0; i < 8; i++)
//        {
//            for (int j = 0; j < 8; j++)
//            {
//                if (types[j] == i)
//                    typesNum[i]++;
//            }
//        }

//        weight += pow(2, typesNum[OXP]);
//        weight += pow(1, typesNum[WXP]);
//        weight += pow(8, typesNum[OXXP]);
//        weight += pow(2, typesNum[WXXP]);
//        weight += pow(64, typesNum[OXXXP]);
//        weight += pow(32, typesNum[WXXXP]);
//        weight += pow(256, typesNum[OXXXXP]);
//        weight += pow(256, typesNum[WXXXXP]);
//    }
    return weight;
}
