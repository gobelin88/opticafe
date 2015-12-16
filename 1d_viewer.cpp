#include "1d_viewer.h"

Viewer1D::Viewer1D()
{
    this->addGraph();
    QPen pen_data(QColor(0,0,255));
    pen_data.setStyle(Qt::SolidLine);
    this->graph()->setBrush(QBrush(QColor(0,0,255,32)));
    this->graph()->setPen(pen_data);
    this->graph()->setLineStyle(QCPGraph::lsLine);
    this->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssPlus, 10));
    this->rescaleAxes();
    this->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
    this->legend->setFont(QFont("Helvetica", 9));

    this->addGraph();
    QPen pen_model(QColor(255,1,0));
    pen_model.setStyle(Qt::SolidLine);
    this->graph()->setPen(pen_model);
    this->graph()->setLineStyle(QCPGraph::lsLine);
    this->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssPlus, 10));
    this->rescaleAxes();
    this->legend->setFont(QFont("Helvetica", 9));
}

Viewer1D::~Viewer1D()
{

}

void Viewer1D::setPath(std::vector<VectorXd> path,int id1)
{
    this->path=path;
    this->id1=id1;

    graph(1)->setData( extract(path,id1),buildNULLQVector(path.size()));
    rescaleAxes();
    replot();
}
void Viewer1D::slot_set_data(std::vector<double> data)
{
    this->data=data;

    for(int i=0;i<data.size();i++)
    {
        std::cout<<data[i]<<std::endl;
    }


    graph(0)->setData(buildXQVector(data.size()), QVector<double>::fromStdVector(data));
    rescaleAxes();
    replot();
}

QVector<double> Viewer1D::extract(std::vector<VectorXd> v,int id)
{
    QVector<double> v_out(v.size());
    for(unsigned int i=0;i<v.size();i++)
    {
        v_out[i]=v[i][id];
    }
    return v_out;
}

QVector<double> Viewer1D::buildXQVector(unsigned int sz)
{
    QVector<double> qv(sz,0.0);
    for(int i=0;i<sz;i++)
    {
        qv[i]=box.getP0(i);
    }
    return qv;
}

QVector<double> Viewer1D::buildNULLQVector(unsigned int sz)
{
    QVector<double> qv(sz,0.0);
    for(int i=0;i<sz;i++)
    {
        qv[i]=0;
    }
    return qv;
}

void Viewer1D::mouseMoveEvent(QMouseEvent * event)
{

}
