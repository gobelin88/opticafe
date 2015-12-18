#ifndef IMAGE_VIEWER_H
#define IMAGE_VIEWER_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <iostream>
#include <QAction>
#include <QMenu>
#include <QFileInfo>
#include <QFileDialog>

#include <Eigen/Dense>
using Eigen::VectorXd;

#include "system.h"
#include "box.h"

class Viewer2D:public QCustomPlot
{
    Q_OBJECT
public:
    Viewer2D();
    ~Viewer2D();

    void setPath(std::vector<VectorXd> path);

    void createPopup();

public slots:
    void slot_set_data(std::vector<std::vector<double>> data, Box box);
    void slot_save_image();
    void setGradient(int preset);

signals:
    void pick(double p0,double p1);

protected:
    QVector<double> extract(std::vector<VectorXd> v,int id);

    //void mousePressEvent(QMouseEvent * event);

    std::vector<std::vector<double>> data;
    std::vector<VectorXd> path;
    Box box;

    QCPMarginGroup * marginGroup;
    QCPColorScale * colorScale;
    QCPColorMap * colorMap;

    QString current_filename;
    QMenu * popup_menu;
    QAction * actSave;
};

#endif // IMAGE_VIEWER_H
