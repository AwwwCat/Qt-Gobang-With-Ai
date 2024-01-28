#ifndef MAINOPTION_H
#define MAINOPTION_H

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
    QColor colorA = QColor(0, 0, 0);
    QColor colorB = QColor(255, 255, 255);
    QColor chessBoardColor = QColor(247, 230, 182, 255);
    QPalette colorAPalette = QPalette(colorA);
    QPalette colorBPalette = QPalette(colorB);
    QPalette chessBoardColorPalette = QPalette(chessBoardColor);

    QLabel* colorLabel;
    QLabel* colorALabel;
    QLabel* colorBLabel;
    QLabel* chessBoardColorLabel;
    QLabel* colorAShow;
    QLabel* colorBShow;
    QLabel* chessBoardColorShow;
    QLabel* otherLabel;
    QCheckBox* nextPieceShow;
    QCheckBox* orderShow;
    
    QPushButton* colorAButton;
    QPushButton* colorBButton;
    QPushButton* chessBoardColorButton;
    QPushButton* commitButton;
    QPushButton* cancelButton;

    QHBoxLayout* colorALayout;
    QHBoxLayout* colorBLayout;
    QHBoxLayout* chessBoardColorLayout;
    QHBoxLayout* buttonLayout;
    QVBoxLayout* widgetLayout;

private slots:
    void colorAButtonClicked();
    void colorBButtonClicked();
    void chessBoardColorButtonClicked();
    void commitButtonClicked();
    void cancelButtonClicked();

signals:
    void commitOptionsSgn(QColor ca, QColor cb, QColor cbc, bool nextPieceShow, bool orderShow);
};

#endif // !MAINOPTION_H