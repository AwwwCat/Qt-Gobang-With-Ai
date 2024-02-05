#ifndef MAINOPTION_H
#define MAINOPTION_H

#include "../Headers/define.h"
#include "../Headers/ChessBoard.h"
#include <QCheckBox>
#include <QColor>
#include <QColorDialog>
#include <QDialog>
#include <QLabel>
#include <QLayout>
#include <QPushButton>
#include <QPalette>

class MainOption : public QDialog
{
    Q_OBJECT

public:
    explicit MainOption(QWidget* parent = nullptr);
    ~MainOption();

private:
    QColor colorA = DEFAULT_PIECE_A_COLOR;
    QColor colorB = DEFAULT_PIECE_B_COLOR;
    QColor chessBoardColor = DEFAULT_CHESS_BOARD_COLOR;
    QColor chessLineColor = DEFAULT_CHESS_LINE_COLOR;
    QPalette colorAPalette = QPalette(colorA);
    QPalette colorBPalette = QPalette(colorB);
    QPalette chessBoardColorPalette = QPalette(chessBoardColor);
    QPalette chessLineColorPalette = QPalette(chessLineColor);

    QLabel* colorLabel;
    QLabel* colorALabel;
    QLabel* colorBLabel;
    QLabel* chessBoardColorLabel;
    QLabel* chessLineColorLabel;
    QLabel* colorAShow;
    QLabel* colorBShow;
    QLabel* chessBoardColorShow;
    QLabel* chessLineColorShow;
    QLabel* otherLabel;
    QCheckBox* nextPieceShow;
    QCheckBox* orderShow;
    
    QPushButton* colorAButton;
    QPushButton* colorBButton;
    QPushButton* chessBoardColorButton;
    QPushButton* chessLineColorButton;
    QPushButton* commitButton;
    QPushButton* cancelButton;

    QHBoxLayout* colorALayout;
    QHBoxLayout* colorBLayout;
    QHBoxLayout* chessBoardColorLayout;
    QHBoxLayout* chessLineColorLayout;
    QHBoxLayout* buttonLayout;
    QVBoxLayout* widgetLayout;

private slots:
    void colorAButtonClicked();
    void colorBButtonClicked();
    void chessBoardColorButtonClicked();
    void chessLineColorButtonClicked();
    void commitButtonClicked();
    void cancelButtonClicked();

signals:
    void commitOptionsSgn(QColor ca, QColor cb, QColor cbc, QColor clc, bool nextPieceShow, bool orderShow);
};

#endif // !MAINOPTION_H