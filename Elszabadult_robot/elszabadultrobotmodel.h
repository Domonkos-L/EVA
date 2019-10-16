#ifndef ELSZABADULTROBOTMODEL_H
#define ELSZABADULTROBOTMODEL_H

#include <QObject>
#include<QVector>

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


private:
    int size;
    Direction  Dir;
    QVector<QVector<Table>> _gameTable;
    bool wasBroken = false;

signals:

public slots:

};

#endif // ELSZABADULTROBOTMODEL_H
