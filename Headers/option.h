#ifndef OPTION_H
#define OPTION_H

#include <QDialog>
#include <QColor>

namespace Ui {
class Option;
}

class Option : public QDialog
{
    Q_OBJECT

public:
    explicit Option(QDialog *parent = nullptr);
    ~Option();
    Ui::Option *ui;

signals:
    void options(QColor ca, QColor cb, bool showpiece, bool orderShow, bool scoreShow);

private slots:
    void on_pushButton_clicked();

private:

};

#endif // OPTION_H
