#include "image_viewer.h"

ImageViewer::ImageViewer()
{
    path.clear();
    zoom=1.0;


    createPopup();
}

ImageViewer::~ImageViewer()
{

}

void ImageViewer::createPopup()
{
    popup_menu=new QMenu(this);

    actSave   = new QAction("Save",  this);
    actLoad    = new QAction("Load",   this);

    actSave->setShortcut(QKeySequence(tr("Ctrl+S")));
    actLoad->setShortcut(QKeySequence(tr("Ctrl+L")));

    popup_menu->addAction(actSave);
    popup_menu->addAction(actLoad);

    connect(actSave,SIGNAL(triggered()),this,SLOT(slot_save_image()));
    connect(actLoad,SIGNAL(triggered()),this,SLOT(slot_load_image()));
}

void ImageViewer::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);

    painter.drawImage(this->rect(), image, image.rect());

    painter.setPen(QPen(QColor(255,0,0)));
    if(path.size()>2)
    {
        painter.drawText(zoom*box.fromP0(path[0][0]),
                         zoom*box.fromP1(path[0][1]),
                         QString("(%1,%2)").arg(path[0][0]).arg(path[0][1]));

        painter.drawText(zoom*box.fromP0(path[path.size()-1][0]),
                         zoom*box.fromP1(path[path.size()-1][1]),
                         QString("(%1,%2)").arg(path[path.size()-1][0]).arg(path[path.size()-1][1]));

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
    if(event->button() == Qt::LeftButton)
    {
        if(!image.isNull())
        {
            emit pick(box.getP0(event->x()/zoom),
                      box.getP1(event->y()/zoom));
        }
    }
    else if(event->button() == Qt::RightButton)
    {
        popup_menu->exec(mapToGlobal(event->pos()));
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

void ImageViewer::slot_save_image()
{
    QFileInfo info(current_filename);
    QString where=info.path();

    QString filename=QFileDialog::getSaveFileName(this,"Save Image",where,"(*.png)");

    if(!filename.isEmpty())
    {
        this->current_filename=filename;
        if(!image.isNull())
        {
            image.save(filename);
        }
    }
}

void ImageViewer::slot_load_image()
{
    QFileInfo info(current_filename);
    QString where=info.path();

    QString filename=QFileDialog::getOpenFileName(this,"Load Image",where,"(*.png)");

    if(!filename.isEmpty())
    {
        if(!image.isNull())
        {
            image.load(filename);
        }
    }
}
