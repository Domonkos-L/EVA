#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollArea>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMenuBar>
#include <QAction>

#include "iconeditor.h"
#include "selectcolorbutton.h"

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

public slots:
    void saveImage();
    void loadImage();

private:
    IconEditor iconEditor;
    QVBoxLayout* layout;
    QScrollArea* scrollArea;

    QMenuBar* menubar;
    QMenu* file;
    QAction* save;
    QAction* load;

    SelectColorButton* changeColor;
};

#endif // MAINWINDOW_H
