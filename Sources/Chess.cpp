#include "../Headers/Chess.h"

Chess::Chess(QWidget* parent) : ChessBoard(parent)
{
    setMouseTracking(true);
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    connect(this, &Chess::chessPlayingDone, this, &Chess::chessPlaying);
    createNewChessMap();
}

Chess::~Chess()
{

}

void Chess::paintEvent(QPaintEvent* e)
{
    Q_UNUSED(e);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(QColor(0, 0, 0), 1));

    // 画棋盘
    boardDraw(painter);

    // 画棋盘上的黑点
    pointDraw(painter);

    // 画将要下的棋子
    if (pieceX != -1 && pieceY != -1 && gameMode != Noplay && playing && showPiece)
    {
        if (pieceMode == Black)
            painter.setBrush(pieceAColor);
        else if (pieceMode == White)
            painter.setBrush(pieceBColor);
        painter.drawEllipse(pieceX * cellSize + startX - pieceR, pieceY * cellSize + startY - pieceR, pieceR * 2, pieceR * 2);
    }

    // 画棋盘上已有的棋子
    pieceDraw(painter);

    // Debug模式：权重
    if (showScore)
    {
        painter.setPen(QPen(QColor(255, 0, 0), 3));
        for (int i = 0; i < cellNum + 1; i++)
            for (int j = 0; j < cellNum + 1; j++)
            {
                if (chessMap[i][j] == None)
                    painter.drawText(i * cellSize + startX - cellSize / 2, j * cellSize + startY - cellSize / 2, cellSize, cellSize, Qt::AlignCenter, QString::number(scoreMap[i][j]));
            }
    }

    // 下棋顺序
    if (showOrder)
    {
        painter.setPen(QPen(QColor(255, 0, 0), 3));
        for (int i = 0; i < pow(cellNum + 1, 2) && chessOrder[i][0] != -1; i++)
        {
            painter.drawText(chessOrder[i][0] * cellSize + startX - cellSize / 2, chessOrder[i][1] * cellSize + startY - cellSize / 2, cellSize, cellSize, Qt::AlignCenter, QString::number(i + 1));
        }
    }
}

void Chess::mouseMoveEvent(QMouseEvent* e)
{
    int cx = e->x() - startX;
    int cy = e->y() - startY;

    int pieceDX = ((cx % cellSize) > (cellSize / 2) ? cellSize : 0) - cx % cellSize;
    int pieceDY = ((cy % cellSize) > (cellSize / 2) ? cellSize : 0) - cy % cellSize;

    pieceX = cx / cellSize + ((cx % cellSize) > (cellSize / 2));
    pieceY = cy / cellSize + ((cy % cellSize) > (cellSize / 2));

    int pieceDistance = std::sqrt(std::pow(pieceDX, 2) + std::pow(pieceDY, 2));

    pieceX = (pieceX >= 0 && pieceX <= cellNum && pieceDistance <= pieceR) ? pieceX : -1;
    pieceY = (pieceY >= 0 && pieceY <= cellNum && pieceDistance <= pieceR) ? pieceY : -1;

    update();
}

void Chess::mousePressEvent(QMouseEvent* e) 
{
    if (e->button() == Qt::LeftButton && pieceX != -1 && pieceY != -1 && chessMap[pieceX][pieceY] == None && playing)
    {
        int directLine[4] = { 0 };
        bool changePiece = true;

        chessMap[pieceX][pieceY] = pieceMode;
        chessOrder[order][0] = pieceX;
        chessOrder[order][1] = pieceY;
        order++;
        
        emit chessPlayingDone();
    }

    if (e->button() == Qt::RightButton)
    {
        QVector<int> roundType = roundErgodic(pieceX, pieceY, Black);
        int wightB = WeightedCalculation(typesConvert(roundType, Black), Black);
        int wightW = WeightedCalculation(typesConvert(roundErgodic(pieceX, pieceY, White), White), White);
        qDebug("Down: %d, RightDown: %d, Right: %d, RightUp: %d, Up: %d, LeftUp: %d, Left: %d, LeftDown: %d, Wight-Black: %d, Wight-White: %d", roundType[0], roundType[1], roundType[2], roundType[3], roundType[4], roundType[5], roundType[6], roundType[7], wightB, wightW);
    }

    update();
}

void Chess::chessPlaying()
{
    if (!winnerJudgment())
    {
        pieceMode = (pieceMode == Black) ? White : Black;
        emit pieceChangedSgn();
    }

    if (gameMode == PvC && pieceMode == White && playing)
    {
        AIPlay();
    }
}

bool Chess::winnerJudgment()
{
    if (order == pow(cellNum + 1, 2))
    {
        emit winnerSgn(None);
        return true;
    }
    else if (lianziJudgment())
    {
        emit winnerSgn(pieceMode);
        return true;
    }
    return false;
}

bool Chess::lianziJudgment()
{
    if (order == 0)
        return false;

    int directLine[4] = { 0 };

    for (int i = 0; i < 8; i++)
    {
        for (int j = 1; j < lianzhuNum; j++)
        {
            int px = chessOrder[order - 1][0] + j * direction[i][0];
            int py = chessOrder[order - 1][1] + j * direction[i][1];

            if (px <= cellNum && px >= 0 && py <= cellNum && py >= 0)
            {
                if (chessMap[px][py] == pieceMode)
                {
                    directLine[i % 4] += 1;
                    if (directLine[i % 4] == lianzhuNum - 1)
                    {
                        return true;
                    }
                }
                else
                {
                    break;
                }
            }
        }
    }

    return false;
}

void Chess::AIPlay()
{
    int maxScore = 0;
    int mx = -1, my = -1;
    QVector<QVector<int>> maxScoreMap;
    scoreMap.fill(QVector<int>(cellNum + 1, 0), cellNum + 1);

    // 遍历所有空位判断周围八个方向类型
    for (int i = 0; i <= cellNum; i++)
    {
        for (int j = 0; j <= cellNum; j++)
        {
            if (chessMap[i][j] == None && gameMode != Noplay && playing)
            {
                scoreMap[i][j] += WeightedCalculation(typesConvert(roundErgodic(i, j, Black), Black), Black);
                scoreMap[i][j] += WeightedCalculation(typesConvert(roundErgodic(i, j, White), White), White);
            }
        }
    }

    // 查找最大权重
    for (int i = 0; i <= cellNum; i++)
    {
        for (int j = 0; j <= cellNum; j++)
        {
            if (scoreMap[i][j] > maxScore)
            {
                maxScore = scoreMap[i][j];
            }
        }
    }

    // 寻找所有最大权重坐标
    for (int i = 0; i <= cellNum; i++)
    {
        for (int j = 0; j <= cellNum; j++)
        {
            if (scoreMap[i][j] == maxScore)
            {
                QVector<int> maxScoreAddr;
                maxScoreAddr.append(i);
                maxScoreAddr.append(j);
                maxScoreMap.append(maxScoreAddr);
            }
        }
    }

    // 获取随机坐标
    QRandomGenerator rg(QDateTime::currentMSecsSinceEpoch());
    int r = rg.bounded(maxScoreMap.count());
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

    emit chessPlayingDone();

    update();
}

void Chess::AIAttack(QVector<int> categorys)
{

}

QVector<int> Chess::roundErgodic(int x, int y, int pm)
{
    QVector<int> roundType(8, 0);
    
    for (int m = 0; m < 8; m++)
    {
        if (roundType[m] == 0)
        {
            for (int n = 1; n <= lianzhuNum; n++)
            {
                int px = x + n * direction[m][0];
                int py = y + n * direction[m][1];

                if (px <= cellNum && px >= 0 && py <= cellNum && py >= 0)
                { 
                    if (roundType[m] == OXOXP)
                    {
                        if (chessMap[px][py] != None)
                            roundType[m] = OXP;
                        break;
                    }
                    
                    if (roundType[m] == OXP)
                    {
                        if (chessMap[px][py] == pm)
                        {
                            roundType[m] = OXOXP;
                            continue;
                        }
                        break;
                    }

                    if (roundType[m] == OP)
                    {
                        if (chessMap[px][py] != pm && chessMap[px][py] != None)
                            roundType[m] = WOOP;
                        break;
                    }

                    if (roundType[m] == WXXXOP && chessMap[px][py] == None)
                    {
                        roundType[m] = OP;
                        break;
                    }
                    else if (chessMap[px][py] == None && n == 1)
                    {
                        roundType[m] = WOP;
                    }
                    else if (chessMap[px][py] == pm)
                    {
                        roundType[m] += 2;
                    }
                    else if (chessMap[px][py] == None && roundType[m] >= WOOP)
                    {
                        roundType[m] += 1;
                        if (roundType[m] == OP)
                            continue;
                        break;
                    }
                    else if (chessMap[px][py] == None && roundType[m] != 0 && roundType[m] < WOOP)
                    {
                        roundType[m] -= 1;
                        if (roundType[m] == OXP)
                            continue;
                        break;
                    }
                    else
                        break;
                }
            }
        }
    }

    return roundType;
}

QVector<int> Chess::typesConvert(QVector<int> types, int pm)
{
    QVector<int> categorys(AllCategorys, 0);

    for (int i = 0; i < 4; i++)
    {
    /* 眠一：WXPM */ 
        // WXPM
        if ((types[i] == WXP && (types[i + 4] >= WOOP && types[i + 4] <= OP)) || ((types[i] >= WOOP && types[i] <= OP) && types[i + 4] == WXP))
            categorys[SleepOne] += 1;
    /* 活一：OXPM */
        // OXPM
        else if ((types[i] == OXP && (types[i + 4] >= WOOP && types[i + 4] <= OP)) || ((types[i] >= WOOP && types[i] <= OP) && types[i + 4] == OXP))
            categorys[AliveOne] += 1;
    /* 眠二：WXPXO WPXXO WXXPO WXXPOOW WXXOPOW*/
        // WPXXO
        else if ((types[i] == WP && types[i + 4] == OXXP) || (types[i] == OXXP && types[i + 4] == WP))
            categorys[SleepTwo] += 1;
        // WXPXO
        else if ((types[i] == WXP && types[i + 4] == OXP) || (types[i] == OXP && types[i + 4] == WXP))
            categorys[SleepTwo] += 1;
        // WXXPO
        else if ((types[i] == WXXP && types[i + 4] == OP) || (types[i] == OP && types[i + 4] == WXXP))
            categorys[SleepTwo] += 1;
        // WXXPOOW
        else if ((types[i] == WXXP && types[i + 4] == WOOP) || (types[i] == WOOP && types[i + 4] == WXXP))
            categorys[SleepTwo] += 1;
        // WXXOPOW
        else if ((types[i] == WXXOP && types[i + 4] == WOP) || (types[i] == WOP && types[i + 4] == WXXOP))
            categorys[SleepTwo] += 1;
    /* 活二：OXXPM OXPXO */
        // OXPXO
        else if (types[i] == OXP && types[i + 4] == OXP)
            categorys[AliveTwo] += 1;
        // OXXPM
        else if ((types[i] == OXXP && (types[i + 4] >= WOOP && types[i + 4] <= OP)) || ((types[i] >= WOOP && types[i] <= OP) && types[i + 4] == OXXP))
            categorys[AliveTwo] += 1;
    /* 跳二: OXOXPM */
        // OXOXPM
        else if ((types[i] == OXOXP && (types[i + 4] >= WOOP && types[i + 4] <= OP)) || ((types[i] >= WOOP && types[i] <= OP) && types[i + 4] == OXOXP))
            categorys[JumpTwo] += 1;
    /* 中二：OXOPXO */
        // OXOPXO
        else if ((types[i] == OXOP && types[i + 4] == OXP) || (types[i] == OXP && types[i + 4] == OXOP))
            categorys[MiddleTwo] += 1;
    /* 边二：OXXOPM */
        // OXXOPO
        else if ((types[i] == OXXOP && (types[i + 4] >= WOOP && types[i + 4] <= OP)) || ((types[i] >= WOOP && types[i] <= OP) && types[i + 4] == OXXOP))
            categorys[SideTwo] += 1;
    /* 眠三：WXXPXO WXPXXO WXXXPM WXXXOPW */
        // WXXPXO
        else if ((types[i] == WXXP && types[i + 4] == OXP) || (types[i] == OXP && types[i + 4] == WXXP))
            categorys[SleepThree] += 1;
        // WXPXXO
        else if ((types[i] == WXP && types[i + 4] == OXXP) || (types[i] == OXXP && types[i + 4] == WXP))
            categorys[SleepThree] += 1;
        // WXXXPM
        else if ((types[i] == WXXXP && (types[i + 4] >= WOOP && types[i + 4] <= OP)) || ((types[i] >= WOOP && types[i] <= OP) && types[i + 4] == WXXXP))
            categorys[SleepThree] += 1;
        // WXXXOPA
        else if (types[i] == WXXXOP || types[i + 4] == WXXXP)
            categorys[SleepThree] += 1;
    /* 活三：OXXXPM OXXPXO */
        // OXXPXO
        else if ((types[i] == OXXP && types[i + 4] == OXP) || (types[i] == OXP && types[i + 4] == OXXP))
            categorys[AliveThree] += 1;
        // OXXXPM
        else if ((types[i] == OXXXP && (types[i + 4] >= WOOP && types[i + 4] <= OP)) || ((types[i] >= WOOP && types[i] <= OP) && types[i + 4] == OXXXP))
            categorys[AliveThree] += 1;
    /* 冲四：WXXXXPA WXXXPXO WXXPXXO WXXXPXW OXXPXXO OXXXPXO */
        // WXXXXPA
        else if (types[i] == WXXXXP || types[i + 4] == WXXXXP)
            categorys[RushFour] += 1;
        // WXXPXXO
        else if ((types[i] == WXXP && types[i + 4] == OXXP) || (types[i] == OXXP && types[i + 4] == WXXP))
            categorys[RushFour] += 1;
        // WXXXPXO
        else if ((types[i] == WXXXP && types[i + 4] == OXP) || (types[i] == OXP && types[i + 4] == WXXXP))
            categorys[RushFour] += 1;
        // OXXXPXW
        else if ((types[i] == WXP && types[i + 4] == OXXXP) || (types[i] == OXXXP && types[i + 4] == WXP))
            categorys[RushFour] += 1;
        // WXXXPXW
        else if ((types[i] == WXP && types[i + 4] == WXXXP) || (types[i] == WXXXP && types[i + 4] == WXP))
            categorys[RushFour] += 1;
        // OXXPXXO
        else if (types[i] == OXXP && types[i + 4] == OXXP)
            categorys[RushFour] += 1;
        // OXXXPXO
        else if ((types[i] == OXP && types[i + 4] == OXXXP) || (types[i] == OXXXP && types[i + 4] == OXP))
            categorys[RushFour] += 1;
    /* 长五：WXXPXXXO WXXPXXXW OXXPXXXW WXXXXPXO WXXXXPXW */
        // WXXPXXXO
        else if ((types[i] == OXXXP && types[i + 4] == WXXP) || (types[i] == WXXP && types[i + 4] == OXXXP))
            categorys[LongFive] += 1;
        // WXXPXXXW
        else if ((types[i] == WXXP && types[i + 4] == WXXXP) || (types[i] == WXXXP && types[i + 4] == WXXP))
            categorys[LongFive] += 1;
        // OXXPXXXW
        else if ((types[i] == OXXP && types[i + 4] == WXXXP) || (types[i] == WXXXP && types[i + 4] == OXXP))
            categorys[LongFive] += 1;
        // WXXXXPXO
        else if ((types[i] == WXXXXP && types[i + 4] == OXP) || (types[i] == OXP && types[i + 4] == WXXXXP))
            categorys[LongFive] += 1;
        // WXXXXPXW
        else if ((types[i] == WXXXXP && types[i + 4] == WXP) || (types[i] == WXP && types[i + 4] == WXXXXP))
            categorys[LongFive] += 1;
    /* 活四：OXXXXPA */
        else if (types[i] == OXXXXP || types[i + 4] == OXXXXP)
            categorys[AliveFour] += 1;
    }
    /* 三三 */
    if (categorys[AliveTwo] + categorys[JumpTwo] + categorys[MiddleTwo] + categorys[SideTwo] > 1)
        categorys[ThreeThree] += 1;
    /* 四四 */
    else if (categorys[SleepThree] > 1)
        categorys[FourFour] += 1;
    /* 四三 */
    else if (categorys[SleepThree] + categorys[AliveTwo] + categorys[JumpTwo] + categorys[MiddleTwo] + categorys[SideTwo] > 1)
        categorys[FourThree] += 1;
    
    return categorys;
}

int Chess::WeightedCalculation(QVector<int> categorys, int pm)
{
    int weight = 0;

    if (pm == Black)
    {
        weight += categorys[SleepOne] * 1;
        weight += categorys[AliveOne] * 2;
        weight += categorys[SleepTwo] * 5;
        weight += (categorys[AliveTwo] + categorys[JumpTwo] + categorys[MiddleTwo] + categorys[SideTwo]) * 10;
        weight += categorys[SleepThree] * 20;
        weight += (categorys[ThreeThree] + categorys[FourFour] + categorys[FourThree]) * 100;
        weight += categorys[AliveThree] * 150;
        weight += categorys[RushFour] * 500;
        weight += categorys[LongFive] * 500;
        weight += categorys[AliveFour] * 500;
    }
    else if (pm == White)
    {
        weight += categorys[SleepOne] * 0;
        weight += categorys[AliveOne] * 1;
        weight += categorys[SleepTwo] * 2;
        weight += (categorys[AliveTwo] + categorys[JumpTwo] + categorys[MiddleTwo] + categorys[SideTwo]) * 5;
        weight += categorys[SleepThree] * 10;
        weight += (categorys[ThreeThree] + categorys[FourFour] + categorys[FourThree]) * 120;
        weight += categorys[AliveThree] * 200;
        weight += categorys[RushFour] * 1000;
        weight += categorys[LongFive] * 1000;
        weight += categorys[AliveFour] * 1000;
    }

    return weight;
}

void Chess::backMove()
{
    if (order > 0)
    {
        order -= 1;
        chessMap[chessOrder[order][0]][chessOrder[order][1]] = None;
        chessOrder[order][0] = chessOrder[order][1] = -1;
        
        if (gameMode == PvP)
        {
            pieceMode = (pieceMode == Black) ? White : Black;
            emit pieceChangedSgn();
        }
        else if (gameMode == PvC)
        {
            order -= 1;
            chessMap[chessOrder[order][0]][chessOrder[order][1]] = None;
            chessOrder[order][0] = chessOrder[order][1] = -1;
            pieceMode = Black;
            emit pieceChangedSgn();
        }

        playing = true;
        update();
    }
}

void Chess::createNewChessMap()
{
    pieceMode = Black;

    createNewChessBoard();

    scoreMap.clear();
    scoreMap.fill(QVector<int>(cellNum + 1, 0), cellNum + 1);

    update();
}

QVector<int> Chess::saveChessMap()
{
    QVector<int> map;
    map.append(gameMode);
    map.append(cellNum);
    map.append(order);
    for (int i = 0; i < pow(cellNum + 1, 2) && chessOrder[i][0] != -1; i++)
    {
        map.append(chessOrder[i][0]);
        map.append(chessOrder[i][1]);
    }
    return map;
}