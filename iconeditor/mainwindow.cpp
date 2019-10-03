#include "mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Icon editor");

    changeColor = new SelectColorButton(&iconEditor, this);
    changeColor->setText("Change color");

    scrollArea = new QScrollArea(this);
    scrollArea->setWidget(&iconEditor);
    scrollArea->viewport()->setBackgroundRole(QPalette::Dark);
    scrollArea->viewport()->setAutoFillBackground(true);
    scrollArea->setWidgetResizable(true);

    layout = new QVBoxLayout(this);
    layout->addWidget(changeColor, 1, Qt::AlignRight);
    layout->addWidget(scrollArea);

    menubar = new QMenuBar(this);

    file = new QMenu(tr("File"), menubar);
    menubar->addMenu(file);

    // TODO save and load based on description
    load = new QAction(tr("képbetőtés"), menubar);
    connect(load, SIGNAL(triggered()), this, SLOT(loadImage()));
    file->addAction(load);

    save = new QAction(tr("képemmentés"), menubar);
        connect(save, SIGNAL(triggered()), this, SLOT(saveImage()));
        file->addAction(save);

    save->setEnabled(false);
}

void MainWindow::saveImage()
{
    // TODO based on description
    if(iconEditor.getFileName().isEmpty())
    {
        QMessageBox::information(this, tr("csuhajja"), tr("nicsbetűtvesemmi"));
    }
    else
    {
        iconEditor.saveImage();
    }
}

void MainWindow::loadImage()
{
   // TODO based on descriptionű
    QString filePath = QFileDialog::getOpenFileName(this, tr("nyitás kép"), tr(""), tr("PNG (*.png)"));

    if(!filePath.isNull() && iconEditor.loadImage(filePath))
    {
        save->setEnabled(true);

    }
}
