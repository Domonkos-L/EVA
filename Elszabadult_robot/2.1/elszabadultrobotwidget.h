#ifndef ELSZABADULTROBOTWIDGET_H
#define ELSZABADULTROBOTWIDGET_H

#include "elszabadultrobotmodel.h"
#include "newgamewindow.h"
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QTimer>
#include <QLabel>

class elszabadultrobotwidget : public QWidget
{
    Q_OBJECT

public:

    elszabadultrobotwidget(QWidget *parent = nullptr);
    ~elszabadultrobotwidget();


private slots:
    void tableButtonClicked();
    void newGameButtonClicked();
    void pauseClicked();
    void resumeClicked();
    void timerover();

private:
    QGridLayout *tableLayout;
    QVBoxLayout *mainLayout;
    QHBoxLayout *buttonLayout;
    QPushButton *newGameButton;
    QPushButton *pause;
    QPushButton *resume;
    QLabel *time;
    QTimer *timer;
    QVector<QVector<QPushButton*>> tableButton;
    elszabadultrobotmodel *model;
    newgamewindow *newGame;
    int remTime;
    void generateTable();
    void redrawTable();

};
#endif // ELSZABADULTROBOTWIDGET_H
