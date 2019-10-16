#include "elszabadultrobotmodel.h"
#include "rand.h"
#include <QDebug>
#include <QMessageBox>

elszabadultrobotmodel::elszabadultrobotmodel(QObject *parent, int size) : QObject(parent)
{
    this->size = size;

    _gameTable.resize(size);
    for(int i = 0; i < size; i++)
    {
        _gameTable[i].resize(size);
        for(int j = 0; j < size; j++)
        {
            _gameTable[i][j] = Empty;
        }
    }
    _gameTable[(size-1)/2][(size-1)/2] = Magnet;
    int randI = randint(1, (size-1));
    int randJ = randint(1, (size-1));
    bool notValidIJ = ((randI == (size-1)/2) && (randJ == (size-1)/2));
    if(notValidIJ)
    {
        while(notValidIJ)
        {
            int randI = randint(1, (size-1));
            int randJ = randint(1, (size-1));
            notValidIJ = ((randI == (size-1)/2) && (randJ == (size-1)/2));
        }
    }

    _gameTable[randI][randJ] = Robot;

    int dir = randint(1,5);
    switch (dir) {
    case 1:
        Dir = E;
        break;
    case 2:
        Dir = H;
        break;
    case 3:
        Dir = J;
        break;
    case 4:
        Dir = B;
        break;

    }

}

int elszabadultrobotmodel::getSize()
{
    return size;
}

void elszabadultrobotmodel::newDir()
{
    Direction currDir = Dir;

    int dir = randint(1,5);
    switch (dir) {
    case 1:
        Dir = E;
        break;
    case 2:
        Dir = H;
        break;
    case 3:
        Dir = J;
        break;
    case 4:
        Dir = B;
        break;
    }

    if(currDir == Dir)
    {
        while(currDir == Dir)
        {
            int dir = randint(1,5);
            switch (dir) {
            case 1:
                Dir = E;
                break;
            case 2:
                Dir = H;
                break;
            case 3:
                Dir = J;
                break;
            case 4:
                Dir = B;
                break;

            }
        }
    }


}

void elszabadultrobotmodel::robotStep()
{
    bool collidedwall = false;
    bool collidedother = false;
    bool found = false;

    int currI = 0;
    int currJ = 0;
    int nextI = 0;
    int nextJ = 0;


    for(int i = 0; i < size; i++)
    {

        for(int j = 0; j < size; j++)
        {
            if(_gameTable[i][j] == Robot)
            {
                currI = i;
                currJ = j;
                found = true;
                break;
            }
        }
        if(found)
            break;

    }

    switch(Dir){
    case E:
        collidedother = (currI == 0);
        nextI = currI - 1;
        nextJ = currJ;
        collidedwall = (_gameTable[nextI][nextJ] == Wall);
        break;
    case H:
        collidedother = (currI == size-1);
        nextI = currI + 1;
        nextJ = currJ;
        collidedwall = (_gameTable[nextI][nextJ] == Wall);
        break;
    case J:
        collidedother = (currJ== size-1);
        nextI = currI;
        nextJ = currJ + 1;
        collidedwall = (_gameTable[nextI][nextJ] == Wall);
        break;
    case B:
        collidedother = (currJ == 0);
        nextI = currI;
        nextJ = currJ - 1;
        collidedwall = (_gameTable[nextI][nextJ] == Wall);
        break;

    }

    if (collidedwall)
    {
        _gameTable[nextI][nextJ] = Broken_Wall;
        newDir();

    }

    if(collidedother)
    {
        newDir();

    }

    if(!collidedwall && !collidedother)
    {

        if(_gameTable[nextI][nextJ] == Broken_Wall)
        {
            _gameTable[currI][currJ] = Empty;
            _gameTable[nextI][nextJ] = Robot;
            wasBroken = true;
            return;
        }

        _gameTable[currI][currJ] = Empty;
        _gameTable[nextI][nextJ] = Robot;



        if(wasBroken)
        {
            _gameTable[currI][currJ] = Broken_Wall;
            _gameTable[nextI][nextJ] = Robot;
            wasBroken = false;
        }



        //checkGame();
    }










}

void elszabadultrobotmodel::checkGame()
{
    bool isWon = _gameTable[(size-1)/2][(size-1)/2] == Robot;
    QMessageBox win;
    win.setWindowTitle("Game Over");
    win.setText("You Won");
    win.setInformativeText("Your Time is: ");
    win.setStandardButtons(QMessageBox::Ok);
    if(isWon)
    {
        win.exec();





    }

}

void elszabadultrobotmodel::setButton(int i, int j, elszabadultrobotmodel::Table t)
{
    _gameTable[i][j] = t;
}

elszabadultrobotmodel::Table elszabadultrobotmodel::getButton(int i, int j)
{
    return _gameTable[i][j];
}


