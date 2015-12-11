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

#include "box.h"

class ImageViewer:public QWidget
{
    Q_OBJECT
public:
    ImageViewer();
    ~ImageViewer();

    QImage getImage(){return this->image;}

    void setBox(Box box){this->box=box;}

    void setPath(std::vector<VectorXd> path,int id1,int id2)
    {
        this->path=path;
        this->id1=id1;
        this->id2=id2;
    }

    void createPopup();

public slots:
    void setImage(QImage image)
    {
        zoom=1.0;
        this->image=image;
        this->setFixedSize(image.size()*zoom);
        update();
    }

    void slot_save_image();
    void slot_load_image();

signals:
    void pick(double p0,double p1);

protected:
    void paintEvent(QPaintEvent * event);
    void mousePressEvent(QMouseEvent * event);
    void wheelEvent(QWheelEvent * event);

    QImage image;
    Box box;
    std::vector<VectorXd> path;

    double zoom;

    QMenu * popup_menu;
    QAction * actSave;
    QAction * actLoad;

    QString current_filename;

    int id1,id2;
};

#endif // IMAGE_VIEWER_H
