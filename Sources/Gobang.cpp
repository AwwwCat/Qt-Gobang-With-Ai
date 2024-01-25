#include "../Headers/Gobang.h"

Gobang::Gobang(QWidget *parent) : QMainWindow(parent)
{
    /* 修改窗口参数 */
    this->setWindowTitle(QStringLiteral("五子棋"));

    /* 定义对象 */
    menuBar = new QMenuBar;
    startMenu = new QMenu;
    optionMenu = new QMenu;
    aboutMenu = new QMenu;
    newGameAction = new QAction;
    saveGameAction = new QAction;
    importGameAction = new QAction;
    mainOptionAction = new QAction;
    playerOptionAction = new QAction;
    debugOptionAction = new QAction;
    playingMethodAction = new QAction;
    aboutGamesAction = new QAction;
    backMoveAction = new QAction;

    mainWidget = new MainWidget;
    mainOption = new MainOption;
    newGame = new NewGame;
    playerOption = new PlayerOption;
    debugOption = new DebugOption;
    importDialog = new ImportDialog;

    /* 修改标签属性 */
    startMenu = menuBar->addMenu(QStringLiteral("开始(&N)"));
    optionMenu = menuBar->addMenu(QStringLiteral("设置(&O)"));
    backMoveAction = menuBar->addAction(QStringLiteral("悔棋(&B)"));
    debugOptionAction = menuBar->addAction(QStringLiteral("Debug(&D)"));
    aboutMenu = menuBar->addMenu(QStringLiteral("关于(&I)"));
    
    newGameAction = startMenu->addAction(QStringLiteral("新游戏"));
    saveGameAction = startMenu->addAction(QStringLiteral("保存游戏"));
    importGameAction = startMenu->addAction(QStringLiteral("导入游戏"));

    mainOptionAction = optionMenu->addAction(QStringLiteral("游戏设置"));
    playerOptionAction = optionMenu->addAction(QStringLiteral("玩家设置"));
    
    playingMethodAction = aboutMenu->addAction(QStringLiteral("游戏玩法"));
    aboutGamesAction = aboutMenu->addAction(QStringLiteral("关于游戏"));

    /* 布局 */
    this->setCentralWidget(mainWidget);
    this->setMenuBar(menuBar);

    /* 链接信号与槽 */
    connect(newGameAction, &QAction::triggered, this, &Gobang::newGameActionTriggered);
    connect(saveGameAction, &QAction::triggered, mainWidget, &MainWidget::receiveSaveChessMapSgn);
    connect(importGameAction, &QAction::triggered, this, &Gobang::importGameActionTriggered);
    connect(mainOptionAction, &QAction::triggered, this, &Gobang::mainOptionActionTriggered);
    connect(playerOptionAction, &QAction::triggered, this, &Gobang::playerOptionActionTriggered);
    connect(debugOptionAction, &QAction::triggered, this, &Gobang::debugOptionActionTriggered);
    connect(playingMethodAction, &QAction::triggered, this, &Gobang::playingMethodActionTriggered);
    connect(aboutGamesAction, &QAction::triggered, this, &Gobang::aboutGamesActionTriggered);
    connect(backMoveAction, &QAction::triggered, this->mainWidget->chess, &Chess::backMove);

    connect(newGame, &NewGame::commitNewGameSgn, mainWidget, &MainWidget::receiveNewGameSgn);
    connect(mainOption, &MainOption::commitOptionsSgn, mainWidget, &MainWidget::receiveMainOptionsSgn);
    connect(playerOption, &PlayerOption::commitOptionsSgn, mainWidget, &MainWidget::receivePlayerOptionsSgn);
    connect(debugOption, &DebugOption::commitOptionsSgn, mainWidget, &MainWidget::receiveDebugOptionsSgn);
    connect(importDialog, &ImportDialog::commitImportSgn, mainWidget, &MainWidget::receiveImportSgn);
}

Gobang::~Gobang()
{
    delete mainWidget;
    delete mainOption;
    delete newGame;
    delete playerOption;

    delete backMoveAction;
    delete aboutGamesAction;
    delete playingMethodAction;
    delete debugOptionAction;
    delete playerOptionAction;
    delete mainOptionAction;
    delete saveGameAction;
    delete newGameAction;
    delete aboutMenu;
    delete optionMenu;
    delete startMenu;
    delete menuBar;
}

void Gobang::openGame()
{
    newGame->exec();
}

void Gobang::newGameActionTriggered()
{
    newGame->exec();
}

void Gobang::mainOptionActionTriggered()
{
    mainOption->exec();
}

void Gobang::importGameActionTriggered()
{
    importDialog->exec();
}

void Gobang::playerOptionActionTriggered()
{
    playerOption->exec();
}

void Gobang::debugOptionActionTriggered()
{
    debugOption->exec();
}

void Gobang::playingMethodActionTriggered()
{
    QMessageBox messageBox(QMessageBox::Question, QStringLiteral("玩法说明"), QStringLiteral("你是傻逼吗五子棋不会玩？\n自己百度谢谢。"), QMessageBox::Ok);
    messageBox.exec();
}

void Gobang::aboutGamesActionTriggered()
{
    QMessageBox messageBox(QMessageBox::Question, QStringLiteral("关于软件"), QStringLiteral("作者：我\n版本：v0.00314152653589793238"), QMessageBox::Ok);
    messageBox.exec();
}

void Gobang::backMoveActionTriggered()
{
    
}
