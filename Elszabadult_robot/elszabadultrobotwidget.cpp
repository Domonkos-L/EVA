#include "elszabadultrobotwidget.h"
#include <QDebug>
#include <QMessageBox>


elszabadultrobotwidget::elszabadultrobotwidget(QWidget *parent)
    : QWidget(parent)
{
    setMinimumSize(600,600);
    setWindowTitle(tr("Elszabadult Robot"));
    tableLayout = new QGridLayout;
    newGameButton = new QPushButton(tr("New Game"));
    mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(newGameButton);
    mainLayout->addLayout(tableLayout);

    setLayout(mainLayout);

    newGame = new newgamewindow();
    connect(newGameButton, SIGNAL(clicked()), newGame, SLOT(exec()));
    connect(newGame, SIGNAL(accepted()), this, SLOT(newGameButtonClicked()));


   // generateTable();

}


elszabadultrobotwidget::~elszabadultrobotwidget()
{
}

void elszabadultrobotwidget::tableButtonClicked()
{
    QPushButton* senderButton = dynamic_cast<QPushButton*>(sender());

    int size = model->getSize();

    int loc = tableLayout->indexOf(senderButton);
    int x = loc / size;
    int y = loc % size;

    if(model->getButton(x,y) == elszabadultrobotmodel::Robot ||
       model->getButton(x,y) == elszabadultrobotmodel::Broken_Wall ||
       model->getButton(x,y) == elszabadultrobotmodel::Magnet ||
       model->getButton(x,y) == elszabadultrobotmodel::Wall)
    {
        return;
    }

    model->setButton(x,y, elszabadultrobotmodel::Wall);
    model->robotStep();
    redrawTable();


}

void elszabadultrobotwidget::newGameButtonClicked()
{


    if(!tableButton.empty())
    {
        delete model;
        for( int i = 0; i < tableButton.size(); i++)
        {
            for(int j = 0; j < tableButton.size(); j++)
            {
                tableLayout->removeWidget(tableButton[i][j]);
                delete tableButton[i][j];
            }
        }
    }



    model = new elszabadultrobotmodel(this, newGame->Size());

    int size = model->getSize();




    tableButton.resize(size);
    for(int i = 0; i < size; i++)
    {
        tableButton[i].resize(size);
        for (int j = 0; j < size; j++)
        {
            tableButton[i][j] = new QPushButton;
            connect(tableButton[i][j], SIGNAL(clicked()),this, SLOT(tableButtonClicked()));
            tableButton[i][j]->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
            tableLayout->addWidget(tableButton[i][j], i, j);
        }
    }

    redrawTable();

}

void elszabadultrobotwidget::generateTable()
{


    model = new elszabadultrobotmodel(this, 7);

    if(!tableButton.empty())
    {
        for( int i = 0; i < 7; i++)
        {
            for(int j = 0;j < 7; j++)
            {
                tableLayout->removeWidget(tableButton[i][j]);
                delete tableButton[i][j];
            }
        }
    }

    tableButton.resize(7);
    for(int i = 0; i < 7; i++)
    {
        tableButton[i].resize(7);
        for (int j = 0; j < 7; j++)
        {
            tableButton[i][j] = new QPushButton;
            connect(tableButton[i][j], SIGNAL(clicked()),this, SLOT(tableButtonClicked()));
            tableButton[i][j]->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
            tableLayout->addWidget(tableButton[i][j], i, j);
        }
    }


}

void elszabadultrobotwidget::redrawTable()
{
    int size = model->getSize();

   // tableButton.resize(size);
    for(int i=0; i<size; i++)
    {
       // tableButton[i].resize(size);
        for(int j=0; j<size; j++)
        {
            if(model->getButton(i,j) == elszabadultrobotmodel::Wall)
            {
                tableButton[i][j]->setText(tr("Wall"));
            }
            else if(model->getButton(i,j) == elszabadultrobotmodel::Robot)
            {
                tableButton[i][j]->setText(tr("Robot"));
            }
            else if(model->getButton(i,j) == elszabadultrobotmodel::Broken_Wall)
            {
                tableButton[i][j]->setText(tr("Broken Wall"));
            }
            else if(model->getButton(i,j) == elszabadultrobotmodel::Magnet)
            {
                tableButton[i][j]->setText(tr("Magnet"));
            }
            else if(model->getButton(i,j) == elszabadultrobotmodel::Empty)
            {
                tableButton[i][j]->setStyleSheet("background-color: rgb(200,200,200)");
                tableButton[i][j]->setText(tr(""));
            }
        }
    }

    model->checkGame();

   /* if(model->getWon() == true)
    {
        generateTable();
    }*/
}



