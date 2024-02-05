#ifndef IMPORTDIALOG_H
#define IMPORTDIALOG_H

#include "../Headers/ChessBoard.h"
#include "../Headers/define.h"
#include <QComboBox>
#include <QCoreApplication>
#include <QDataStream>
#include <QDebug>
#include <QDialog>
#include <QDir>
#include <QLabel>
#include <QLayout>
#include <QPushButton>

class ImportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ImportDialog(QWidget* parent = nullptr);
    ~ImportDialog();

private:
    int gameMode = 0;
    int cellNum = 0;
    int order = 0;
    QVector<QVector<int>> chessOrder;

    ChessBoard* chessBoard;

    QLabel* chooseLabel;
    QComboBox* chooseBox;
    QPushButton* refreshButton;
    QPushButton* commitButton;
    QPushButton* cancelButton;

    QHBoxLayout* chooseLayout;
    QHBoxLayout* buttonLayout;
    QVBoxLayout* widgetLayout;

    void loadChessMaps();
    void readChessMap();
    void wrongChessMap();

private slots:
    void refreshButtonClicked();
    void commitButtonClicked();
    void cancelButtonClicked();

signals:
    void commitImportSgn(int gameMode, int cellNum, int order, QVector<QVector<int>>chessOrder);
};

#endif // !IMPORTDIALOG_H