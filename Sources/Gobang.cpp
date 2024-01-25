#include "../Headers/Gobang.h"

Gobang::Gobang(QWidget *parent) : QMainWindow(parent)
{
    /* �޸Ĵ��ڲ��� */
    this->setWindowTitle(QStringLiteral("������"));

    /* ������� */
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

    /* �޸ı�ǩ���� */
    startMenu = menuBar->addMenu(QStringLiteral("��ʼ(&N)"));
    optionMenu = menuBar->addMenu(QStringLiteral("����(&O)"));
    backMoveAction = menuBar->addAction(QStringLiteral("����(&B)"));
    debugOptionAction = menuBar->addAction(QStringLiteral("Debug(&D)"));
    aboutMenu = menuBar->addMenu(QStringLiteral("����(&I)"));
    
    newGameAction = startMenu->addAction(QStringLiteral("����Ϸ"));
    saveGameAction = startMenu->addAction(QStringLiteral("������Ϸ"));
    importGameAction = startMenu->addAction(QStringLiteral("������Ϸ"));

    mainOptionAction = optionMenu->addAction(QStringLiteral("��Ϸ����"));
    playerOptionAction = optionMenu->addAction(QStringLiteral("�������"));
    
    playingMethodAction = aboutMenu->addAction(QStringLiteral("��Ϸ�淨"));
    aboutGamesAction = aboutMenu->addAction(QStringLiteral("������Ϸ"));

    /* ���� */
    this->setCentralWidget(mainWidget);
    this->setMenuBar(menuBar);

    /* �����ź���� */
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
    QMessageBox messageBox(QMessageBox::Question, QStringLiteral("�淨˵��"), QStringLiteral("����ɵ���������岻���棿\n�Լ��ٶ�лл��"), QMessageBox::Ok);
    messageBox.exec();
}

void Gobang::aboutGamesActionTriggered()
{
    QMessageBox messageBox(QMessageBox::Question, QStringLiteral("�������"), QStringLiteral("���ߣ���\n�汾��v0.00314152653589793238"), QMessageBox::Ok);
    messageBox.exec();
}

void Gobang::backMoveActionTriggered()
{
    
}
