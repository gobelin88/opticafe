#include "image_viewer.h"

ImageViewer::ImageViewer()
{
    path.clear();
}

ImageViewer::~ImageViewer()
{

}


void ImageViewer::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);
    painter.drawImage(this->rect(), image, this->rect());

    painter.setPen(QPen(QColor(255,0,0)));
    if(path.size()>2)
    {
        for(int i=1;i<path.size();i++)
        {
            if(path[i-1].rows()>=2)
            {
                painter.drawLine(box.fromP0(path[i-1][0]),
                        box.fromP1(path[i-1][1]),
                        box.fromP0(path[i][0]),
                        box.fromP1(path[i][1]));
            }
        }
    }
}

void ImageViewer::mousePressEvent(QMouseEvent * event)
{
    emit pick(box.getP0(event->x()),
              box.getP1(event->y()));

}
