#include <qcustomplot.h>
#include <QVector>

#include "system.h"
#include "box.h"

#ifndef VIEWER1D_H
#define VIEWER1D_H


class Viewer1D:public QCustomPlot
{
    Q_OBJECT
public:
    Viewer1D();
    ~Viewer1D();

    void setPath(std::vector<VectorXd> path);

public slots:
    void slot_set_data(std::vector<double> data,Box box);

signals:
    void pick(double p0);

private:
    std::vector<double> data;
    std::vector<VectorXd> path;
    Box box;

protected:
    //void mouseMoveEvent(QMouseEvent * event);

    QVector<double> extract(std::vector<VectorXd> v,int id);
    QVector<double> buildXQVector(unsigned int sz);
    QVector<double> buildNULLQVector(unsigned int sz);

};

#endif // VIEWER1D_H
