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

class Viewer2D:public QWidget
{
    Q_OBJECT
public:
    Viewer2D();
    ~Viewer2D();

    QImage getImage(){return this->image;}
    void setImage(QImage image)
    {
        this->image=image;
        this->setFixedSize(image.size()*zoom);
        update();
    }

    void setBox(Box box){this->box=box;}

    void setPath(std::vector<VectorXd> path,int id1,int id2)
    {
        this->path=path;
        this->id1=id1;
        this->id2=id2;
    }

    void createPopup();

public slots:
    void slot_set_data(std::vector<std::vector<double>> data);

    void slot_save_image();
    void slot_load_image();

    void slot_set_gamma(double value);
    void slot_set_color_mode(int mode);

signals:
    void pick(double p0,double p1);

protected:
    void paintEvent(QPaintEvent * event);
    void mousePressEvent(QMouseEvent * event);
    void wheelEvent(QWheelEvent * event);

    std::vector<std::vector<double>> data;
    std::vector<VectorXd> path;
    Box box;
    int id1,id2;

    QImage image;
    ScaleColorMode scale_color_mode;
    double gamma;

    QString current_filename;
    double zoom;
    QMenu * popup_menu;
    QAction * actSave;
};

#endif // IMAGE_VIEWER_H
