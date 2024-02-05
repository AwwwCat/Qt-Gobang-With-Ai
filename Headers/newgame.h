#ifndef NEWGAME_H
#define NEWGAME_H

#include "../Headers/define.h"
#include <QButtonGroup>
#include <QDialog>
#include <QLabel>
#include <QLayout>
#include <QPushButton>
#include <QRadioButton>
#include <QSpinBox>
#include <QString>

class NewGame : public QDialog
{
    Q_OBJECT

public:
    explicit NewGame(QWidget* parent = nullptr);
    ~NewGame();

private:
    QLabel* gamemodeLabel;
    QLabel* timeLabel;
    QLabel* cellNumLabel;
    QRadioButton* PVPButton;
    QRadioButton* PVCButton;
    QSpinBox* thinkTimeBox;
    QSpinBox* cellNumBox;
    QPushButton* commitButton;
    QPushButton* cancelButton;
    QButtonGroup* modeButtonGroup;

    QVBoxLayout* modeLayout;
    QHBoxLayout* timeLayout;
    QHBoxLayout* cellLayout;
    QHBoxLayout* buttonLayout;
    QVBoxLayout* widgetLayout;

private slots:
    void commitButtonClicked();
    void cancelButtonClicked();

signals:
    void commitNewGameSgn(int gameMode, int thinkTime, int cellNum);
};

#endif // !NEWGAME_H
