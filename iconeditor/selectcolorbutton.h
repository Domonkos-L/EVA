#ifndef SELECTCOLORBUTTON_H
#define SELECTCOLORBUTTON_H

#include <QPushButton>

#include "iconeditor.h"

class SelectColorButton : public QPushButton
{
    Q_OBJECT
public:
    SelectColorButton(IconEditor* editor,
                      QWidget* parent = nullptr);

    // TODO
    const QColor& getColor();
    void setColor(const QColor& color);
public slots:
    void changeColor();
private:
    IconEditor* editor;
    QColor color;
    
};

#endif // SELECTCOLORBUTTON_H
