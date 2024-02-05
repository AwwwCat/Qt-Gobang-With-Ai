#ifndef GOBANG_H
#define GOBANG_H

#include "../Headers/define.h"
#include "../Headers/DebugOption.h"
#include "../Headers/ImportDialog.h"
#include "../Headers/MainOption.h"
#include "../Headers/MainWidget.h"
#include "../Headers/NewGame.h"
#include "../Headers/PlayerOption.h"
#include <QAction>
#include <QApplication>
#include <QCoreApplication>
#include <QDesktopWidget>  
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>

class Gobang : public QMainWindow
{
    Q_OBJECT

public:
    Gobang(QWidget* parent = nullptr);
    ~Gobang();

private:
    QMenuBar* menuBar;
    QMenu* startMenu;
    QMenu* optionMenu;
    QMenu* aboutMenu;
    QAction* newGameAction;
    QAction* saveGameAction;
    QAction* importGameAction;
    QAction* mainOptionAction;
    QAction* playerOptionAction;
    QAction* debugOptionAction;
    QAction* playingMethodAction;
    QAction* aboutGamesAction;
    QAction* backMoveAction;

    MainWidget* mainWidget;
    MainOption* mainOption;
    NewGame* newGame;
    PlayerOption* playerOption;
    DebugOption* debugOption;
    ImportDialog* importDialog;

public:
    void openGame();

private slots:
    void newGameActionTriggered();
    void mainOptionActionTriggered();
    void importGameActionTriggered();
    void playerOptionActionTriggered();
    void debugOptionActionTriggered();
    void playingMethodActionTriggered();
    void aboutGamesActionTriggered();
    void backMoveActionTriggered();
};

#endif // !GOBANG_H