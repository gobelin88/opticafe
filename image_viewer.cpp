#include "image_viewer.h"

ImageViewer::ImageViewer()
{
    path.clear();
    zoom=1.0;
    std::cout<<zoom<<std::endl;
}

ImageViewer::~ImageViewer()
{

}


void ImageViewer::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);

    painter.drawImage(this->rect(), image, image.rect());

    painter.setPen(QPen(QColor(255,0,0)));
    if(path.size()>2)
    {
        for(int i=1;i<path.size();i++)
        {
            if(path[i-1].rows()>=2)
            {
                painter.drawLine(zoom*box.fromP0(path[i-1][0]),
                        zoom*box.fromP1(path[i-1][1]),
                        zoom*box.fromP0(path[i][0]),
                        zoom*box.fromP1(path[i][1]));
            }
        }
    }
}

void ImageViewer::mousePressEvent(QMouseEvent * event)
{
    if(!image.isNull())
    {
        emit pick(box.getP0(event->x()/zoom),
                  box.getP1(event->y()/zoom));
    }
}

void ImageViewer::wheelEvent(QWheelEvent *event)
{
    std::cout<<zoom<<std::endl;
    if(event->delta()>0)
    {
        zoom*=1.1;
    }
    else
    {
        zoom/=1.1;
    }
    this->setFixedSize(image.size()*zoom);
    std::cout<<zoom<<std::endl;
    update();
}
