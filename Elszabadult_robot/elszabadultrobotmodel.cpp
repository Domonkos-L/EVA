#include "elszabadultrobotmodel.h"
#include "rand.h"

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
    int nextI, nextJ;


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
        nextI = currI - 1;
        nextJ = currJ;
        collidedwall = _gameTable[nextI][nextJ] == Wall;
        collidedother = currI == 0;
        break;
    case H:
        nextI = currI + 1;
        nextJ = currJ;
        collidedwall = _gameTable[nextI][nextJ] == Wall;
        collidedother = currI == size;
        break;
    case J:
        nextI = currI;
        nextJ = currJ + 1;
        collidedwall = _gameTable[nextI][nextJ] == Wall;
        collidedother = currJ == size;
        break;
    case B:
        nextI = currI;
        nextJ = currJ - 1;
        collidedwall = _gameTable[nextI][nextJ] == Wall;
        collidedother = currJ == 0;
        break;

    }

    if (collidedwall)
    {
        _gameTable[nextI][nextJ] = Broken_Wall;
        newDir();
        return;
    }
    else if(collidedother)
    {
        newDir();
        return;
    }
    else
    {
        _gameTable[currI][currJ] = Empty;
        _gameTable[nextI][nextJ] = Robot;
    }

}

void elszabadultrobotmodel::checkGame()
{
    bool isWon = _gameTable[(size-1)/2][(size-1)/2] == Robot;

    if(isWon)
    {
        //gyozelmi szoveg, ido
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


