#ifndef IMAGE_VIEWER_H
#define IMAGE_VIEWER_H

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

#include <Eigen/Dense>
using Eigen::VectorXd;

#include "box.h"

class ImageViewer:public QWidget
{
    Q_OBJECT
public:
    ImageViewer();
    ~ImageViewer();

    void setImage(QImage image)
    {
        this->image=image;
        this->resize(image.size());
    }
    QImage getImage(){return this->image;}

    void setBox(Box box){this->box=box;}

    void setPath(std::vector<VectorXd> path)
    {
        this->path=path;
    }


signals:
    void pick(double p0,double p1);

protected:
    void paintEvent(QPaintEvent * event);
    void mousePressEvent(QMouseEvent * event);

    QImage image;
    Box box;
    std::vector<VectorXd> path;
};

#endif // IMAGE_VIEWER_H
