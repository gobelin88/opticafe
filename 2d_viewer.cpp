#include "2d_viewer.h"

Viewer2D::Viewer2D()
{
    path.clear();
    zoom=1.0;

    id1=0;
    id2=0;

    createPopup();

    scale_color_mode=MODE_BLUE_GRADIENT;
    gamma=1;
}

Viewer2D::~Viewer2D()
{

}

void Viewer2D::createPopup()
{
    popup_menu=new QMenu(this);

    actSave   = new QAction("Save",  this);

    actSave->setShortcut(QKeySequence(tr("Ctrl+Alt+S")));

    popup_menu->addAction(actSave);

    connect(actSave,SIGNAL(triggered()),this,SLOT(slot_save_image()));
}

void Viewer2D::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);

    painter.drawImage(this->rect(), image, image.rect());

    painter.setPen(QPen(QColor(255,0,0)));
    if(path.size()>2)
    {
        painter.drawText(zoom*box.fromP0(path[0][id1]),
                         zoom*box.fromP1(path[0][id2]),
                         QString("(%1,%2)").arg(path[0][id1]).arg(path[0][id2]));

        painter.drawText(zoom*box.fromP0(path[path.size()-1][id1]),
                         zoom*box.fromP1(path[path.size()-1][id2]),
                         QString("(%1,%2)").arg(path[path.size()-1][id1]).arg(path[path.size()-1][id2]));

        for(unsigned int i=1;i<path.size();i++)
        {
            if(path[i-1].rows()>=2)
            {
                painter.drawLine(zoom*box.fromP0(path[i-1][id1]),
                        zoom*box.fromP1(path[i-1][id2]),
                        zoom*box.fromP0(path[i][id1]),
                        zoom*box.fromP1(path[i][id2]));
            }
        }
    }
}

void Viewer2D::mousePressEvent(QMouseEvent * event)
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

void Viewer2D::wheelEvent(QWheelEvent *event)
{
    if(event->delta()>0)
    {
        zoom*=1.1;
    }
    else
    {
        zoom/=1.1;
    }
    this->setFixedSize(image.size()*zoom);
    update();
}

void Viewer2D::slot_set_data(std::vector<std::vector<double>> data)
{
    std::cout<<"set data"<<std::endl;
    this->data=data;
    setImage(System::toImage(data,scale_color_mode,gamma));
}

void Viewer2D::slot_save_image()
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

void Viewer2D::slot_load_image()
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

void Viewer2D::slot_set_gamma(double value)
{
    this->gamma=value;
    setImage(System::toImage(data,scale_color_mode,gamma));
}

void Viewer2D::slot_set_color_mode(int mode)
{
    this->scale_color_mode=(ScaleColorMode)mode;
    setImage(System::toImage(data,scale_color_mode,gamma));
}
