#include <QtGui>
#include <QImageReader>
#include <QMessageBox>

#include "iconeditor.h"

IconEditor::IconEditor(QWidget *parent)
    : QWidget(parent)
{
    setAttribute(Qt::WA_StaticContents);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    // TODO based on description
    setPenColor(Qt::black);
    setZoomFactor(8);
    image = QImage(32, 32, QImage::Format_ARGB32);
    image.fill(qRgba(0,0,0,0));

}

void IconEditor::setPenColor(const QColor &newColor)
{
    curColor = newColor;
}

void IconEditor::setZoomFactor(int newZoom)
{
    // TODO based on description
    if(newZoom < 1)
    {
        zoom = 1;
    }

    if (newZoom != zoom)
    {
        zoom = newZoom;
        update();
        updateGeometry();
    }

}

void IconEditor::setIconImage(const QImage &newImage)
{
    if (newImage != image)
    {
        image = newImage.convertToFormat(QImage::Format_ARGB32);
        update();
        updateGeometry();
    }
}

// Getter for zoomed image size
QSize IconEditor::sizeHint() const
{ 
    QSize size = zoom * image.size();
    if (zoom >= 3)
    {
        size += QSize(1, 1);
    }
    return size;
}

// Coloring or uncoloring a pixel by click event
void IconEditor::mousePressEvent(QMouseEvent* event)
{
    // TODO based on description
    if(event->button() == Qt::LeftButton)
    {
        setImagePixel(event->pos(), true);
    }
    else if(event->button() == Qt::RightButton)
    {
        setImagePixel(event->pos(), false);
    }
}

// Coloring or uncoloring a pixel by mouse move event
void IconEditor::mouseMoveEvent(QMouseEvent* event)
{
    // TODO based on description
    if(event->buttons() & Qt::LeftButton)
    {
        setImagePixel(event->pos(), true);
    }
    else if(event->buttons() & Qt::RightButton)
    {
        setImagePixel(event->pos(), false);
    }
}

// refreshing image
void IconEditor::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    // paint grid, if zoom >= 3
    if (zoom >= 3)
    {
        painter.setPen(palette().windowText().color());

        for (int i = 0; i <= image.width(); ++i)
        {
            painter.drawLine(zoom * i, 0,
                             zoom * i, zoom * image.height());
        }

        for (int j = 0; j <= image.height(); ++j)
        {
            painter.drawLine(0, zoom * j,
                             zoom * image.width(), zoom * j);
        }
    }

    // ujraszinezes
    for (int i = 0; i < image.width(); ++i)
    {
        for (int j = 0; j < image.height(); ++j)
        {
            QRect rect = pixelRect(i, j);
            if (event->region().intersects(rect))
            {
                QColor color = QColor::fromRgba(image.pixel(i, j));
                painter.fillRect(rect, color);
            }
        }
    }
}

// Coloring of a pixel
void IconEditor::setImagePixel(const QPoint &pos, bool opaque)
{
    int i = pos.x() / zoom;
    int j = pos.y() / zoom;

    if (image.rect().contains(i, j))
    {
        if (opaque)
        {
            image.setPixel(i, j, penColor().rgba());
        }
        else
        {
            image.setPixel(i, j, qRgba(0, 0, 0, 0));
        }

        update(pixelRect(i, j));
    }
}

// Getter for a pixel of an image
QRect IconEditor::pixelRect(int i, int j) const
{
    if (zoom >= 3)
    {
        return QRect(zoom * i + 1, zoom * j + 1, zoom - 1, zoom - 1);
    }
    else
    {
        return QRect(zoom * i, zoom * j, zoom, zoom);
    }
}

bool IconEditor::saveImage()
{
   QImageWriter writer(fileName);

   // TODO based on description, write the image
   if(!writer.write(image))
   {
       QMessageBox::information(this, tr("Elnezest kerek a becses tarsasagtol!"), tr("Nem mentettem te Jagello.") );
       return false;
   }

   const QString message = tr("kimenté a képet eme csodás fos \"%1\"").arg(QDir::toNativeSeparators(fileName));
   QMessageBox::information(this, tr("sikerult fater"),message);
   return true;
}

bool IconEditor::loadImage(const QString& file)
{
    QImageReader reader(file);
    
	// TODO based on description
    const QImage newImage = reader.read();

    if(newImage.isNull())
    {
        QMessageBox::information(this, tr("nemjo fiju, kezgyémagaddal valamit helo!"), tr("nemlódolt befele"));
        return false;
    }

    setIconImage(newImage);
    setFileName(file);
    return true;
}

QString IconEditor::getFileName()
{
    return fileName;
}

void IconEditor::setFileName(QString name)
{
    if(name != fileName)
    {
        fileName = name;
    }
}
