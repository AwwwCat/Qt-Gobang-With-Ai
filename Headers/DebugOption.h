#ifndef DEBUGOPTION_H
#define DEBUGOPTION_H

#include "../Headers/define.h"
#include <QCheckBox>
#include <QDialog>
#include <QLabel>
#include <QLayout>
#include <QPushButton>
#include <QSpinBox>

class DebugOption : public QDialog
{
    Q_OBJECT

public:
    explicit DebugOption(QWidget* parent = nullptr);
    ~DebugOption();

private:
    QCheckBox* weightShowBox;
    QPushButton* commitButton;
    QPushButton* cancelButton;

    QHBoxLayout* buttonLayout;
    QVBoxLayout* widgetLayout;

private slots:
    void commitButtonClicked();
    void cancelButtonClicked();

signals:
    void commitOptionsSgn(bool weightshow);
};

#endif // !DEBUGOPTION_H