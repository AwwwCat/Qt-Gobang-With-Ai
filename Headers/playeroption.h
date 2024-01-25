#ifndef PLAYEROPTION_H
#define PLAYEROPTION_H

#include <QCoreApplication>
#include <QDialog>
#include <QFileDialog>
#include <QLabel>
#include <QLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QString>

class PlayerOption : public QDialog
{
    Q_OBJECT

public:
    explicit PlayerOption(QWidget* parent = nullptr);
    ~PlayerOption();

    QString nameA = QString(QStringLiteral("Baka"));
    QString nameB = QString(QStringLiteral("Baka"));
    QString pathA;
    QString pathB;

private:
    QLabel* ALabel;
    QLabel* BLabel;
    QLabel* nameALabel;
    QLabel* nameBLabel;
    QLabel* photoALabel;
    QLabel* photoBLabel;
    QLineEdit* nameAEdit;
    QLineEdit* nameBEdit;
    QLineEdit* pathAEdit;
    QLineEdit* pathBEdit;
    QPushButton* pathAButton;
    QPushButton* pathBButton;
    QPushButton* commitButton;
    QPushButton* cancelButton;
    
    QHBoxLayout* nameALayout;
    QHBoxLayout* nameBLayout;
    QHBoxLayout* photoALayout;
    QHBoxLayout* photoBLayout;
    QHBoxLayout* buttonLayout;
    QVBoxLayout* widgetLayout;

private slots:
    void commitButtonClicked();
    void cancelButtonClicked();
    void pathAButtonClicked();
    void pathBButtonClicked();

signals:
    void commitOptionsSgn(QString nma, QString pha, QString nmb, QString phb);
};

#endif // !PLAYEROPTION_H

