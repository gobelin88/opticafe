#include "2d_viewer.h"

Viewer2D::Viewer2D()
{
    std::cout<<"Viewer2D constructor"<<std::endl;
    path.clear();

    createPopup();

    this->setInteractions(QCP::iRangeDrag|QCP::iRangeZoom); // this will also allow rescaling the color scale by dragging/zooming
    this->axisRect()->setupFullAxesBox(true);
    this->xAxis->setLabel("p0");
    this->yAxis->setLabel("p1");

    colorMap = new QCPColorMap(this->xAxis, this->yAxis);
    this->addPlottable(colorMap);

    colorScale = new QCPColorScale(this);

    this->plotLayout()->addElement(0, 1, colorScale);
    colorScale->setType(QCPAxis::atRight);
    colorMap->setColorScale(colorScale);
    colorMap->setGradient(QCPColorGradient::gpGrayscale);

    marginGroup = new QCPMarginGroup(this);
    this->axisRect()->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);
    colorScale->setMarginGroup(QCP::msBottom|QCP::msTop, marginGroup);

    this->addGraph();
    QPen pen_model(QColor(255,1,0));
    pen_model.setStyle(Qt::SolidLine);
    this->graph()->setPen(pen_model);
    this->graph()->setLineStyle(QCPGraph::lsLine);
    this->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssPlus, 10));
    this->rescaleAxes();
    this->legend->setFont(QFont("Helvetica", 9));
}

Viewer2D::~Viewer2D()
{

}

QVector<double> Viewer2D::extract(std::vector<VectorXd> v,int id)
{
    QVector<double> v_out(v.size());
    for(unsigned int i=0;i<v.size();i++)
    {
        v_out[i]=v[i][id];
    }
    return v_out;
}

void Viewer2D::setPath(std::vector<VectorXd> path)
{
    this->path=path;

    graph(0)->setData( extract(path,box.id1),extract(path,box.id2));
    rescaleAxes();
    replot();
}

void Viewer2D::createPopup()
{
    popup_menu=new QMenu(this);

    actSave   = new QAction("Save",  this);

    actSave->setShortcut(QKeySequence(tr("Ctrl+Alt+S")));

    popup_menu->addAction(actSave);

    connect(actSave,SIGNAL(triggered()),this,SLOT(slot_save_image()));
}

//void Viewer2D::mousePressEvent(QMouseEvent * event)
//{
//    if(event->button() == Qt::LeftButton)
//    {
////            emit pick(box.getP0(event->x()),
////                      box.getP1(event->y()));
//    }
//    else if(event->button() == Qt::RightButton)
//    {
//        popup_menu->exec(mapToGlobal(event->pos()));
//    }
//}

void Viewer2D::setGradient(int preset)
{
    colorMap->setGradient((QCPColorGradient::GradientPreset)preset);
    this->replot();
}

void Viewer2D::slot_set_data(std::vector<std::vector<double>> data,Box box)
{
    std::cout<<"Viewer2D set data"<<std::endl;
    this->box=box;
    this->data=data;

    colorMap->clearData();

    colorMap->data()->setSize(box.p0_res,box.p1_res);
    colorMap->data()->setRange(QCPRange(box.p0_min,box.p0_max), QCPRange(box.p1_min,box.p1_max));

    for(int i=0;i<box.p0_res;i++)
    {
        for(int j=0;j<box.p1_res;j++)
        {
            colorMap->data()->setCell(i,j, data[i][j]);
        }
    }

    this->xAxis->setLabel(QString("p%1").arg(box.id1));
    this->yAxis->setLabel(QString("p%1").arg(box.id2));

    colorScale->rescaleDataRange(true);
    colorMap->rescaleDataRange();
    this->rescaleAxes();
    this->replot();
}

void Viewer2D::slot_save_image()
{
    QFileInfo info(current_filename);
    QString where=info.path();

    QString filename=QFileDialog::getSaveFileName(this,"Save Image",where,"(*.png)");

    if(!filename.isEmpty())
    {
        this->current_filename=filename;



    }
}
