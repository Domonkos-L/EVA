#ifndef NEWGAMEWINDOW_H
#define NEWGAMEWINDOW_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>

class newgamewindow : public QDialog
{
public:
    newgamewindow(QWidget *parent = 0);
    int Size() {return tableSize->value();}

private:
    QLabel *layoutSize;
    QSpinBox *tableSize;
    QPushButton *cancel;
    QPushButton *ok;
};

#endif // NEWGAMEWINDOW_H
