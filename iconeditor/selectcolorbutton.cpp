#include "selectcolorbutton.h"

#include <QColorDialog>

SelectColorButton::SelectColorButton(IconEditor* editor,
                                     QWidget* parent)
{
    this->editor = editor;
    // TODO
    connect(this, SIGNAL(clicked()), this, SLOT(changeColor()));
}

void SelectColorButton::changeColor()
{
    // TODO based on description
    QColor newColor = QColorDialog::getColor(color, parentWidget());
    setColor(newColor);
}

void SelectColorButton::setColor(const QColor& color)
{
    // TODO based on description
    this->color = color;
    editor->setPenColor(color);

}

const QColor& SelectColorButton::getColor()
{
    return color;
}
