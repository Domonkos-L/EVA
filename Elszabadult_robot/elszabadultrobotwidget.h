#ifndef ELSZABADULTROBOTWIDGET_H
#define ELSZABADULTROBOTWIDGET_H

#include "elszabadultrobotmodel.h"
#include "newgamewindow.h"
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QTimer>

class elszabadultrobotwidget : public QWidget
{
    Q_OBJECT

public:

    elszabadultrobotwidget(QWidget *parent = nullptr);
    ~elszabadultrobotwidget();


private slots:
    void tableButtonClicked();
    void newGameButtonClicked();

private:
    QGridLayout *tableLayout;
    QVBoxLayout *mainLayout;
    QHBoxLayout *buttonLayout;
    QPushButton *newGameButton;
    QVector<QVector<QPushButton*>> tableButton;
    elszabadultrobotmodel *model;
    newgamewindow *newGame;
    void generateTable();
    void redrawTable();

};
#endif // ELSZABADULTROBOTWIDGET_H
