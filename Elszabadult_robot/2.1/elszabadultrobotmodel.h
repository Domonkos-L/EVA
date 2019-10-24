#ifndef ELSZABADULTROBOTMODEL_H
#define ELSZABADULTROBOTMODEL_H

#include <QObject>
#include<QVector>
#include <QTime>

class elszabadultrobotmodel : public QObject
{
    Q_OBJECT
public:
    explicit elszabadultrobotmodel(QObject *parent = nullptr, int size = 7);
    enum Table{Robot, Wall, Broken_Wall, Magnet, Empty};
    enum Direction{E, H, J, B};
    int getSize();
    void newDir();
    void robotStep();
    void checkGame();
    Table getButton(int i, int j);
    void setButton(int i, int j, Table t);
    void startTimer() {myTimer.start();}
    int getAllTime() {return myTimer.elapsed();}
    int getTime() {return elapsedTime;}
    void setEndTime(int et) {endTime = et;}
    void addToElapsed(int t) {elapsedTime += t;}
    bool getEnd() {return isEnd;}
    void reTimer() {myTimer.restart();}
    void pause();
    void resume();
    bool getPaused() {return isPaused;}



private:
    int size;
    Direction  Dir;
    QVector<QVector<Table>> _gameTable;
    bool wasBroken = false;
    QTime myTimer;
    bool isEnd = false;
    int remainingTime;
    bool isPaused = false;
    int elapsedTime = 0;
    int endTime;
    
    
signals:

public slots:

};

#endif // ELSZABADULTROBOTMODEL_H
