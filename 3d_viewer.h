#include <iostream>
#include <assert.h>

//Qt
#include <QtOpenGL>
#include <QGLWidget>
#include <gl/GLU.h>

//Std

//Autre
#include "qcustomplot.h"
#include "DrawableInterface.h"
#include "system.h"

//Eigen
#include <Eigen/Dense>
using Eigen::Vector3d;
using Eigen::VectorXd;

typedef Eigen::Matrix<unsigned char,3,1> Vector3b;

#ifndef Viewer3D_H
#define Viewer3D_H

/**
  @brief Classe pour la visualisation d'objets 3D
  */

class Viewer3D:public QGLWidget
{
    Q_OBJECT
public:

    Viewer3D();
    ~Viewer3D();

    void capture(QString filename)
    {
        show();
        QImage pix=grabFrameBuffer();
        pix.save(filename);
        hide();
    }



    void setPath(std::vector<VectorXd> path);

    void add(DrawableInterface * drawable_object);

    inline void enableGrid(bool value){display_axis=value;}
    inline void setZoom(double r){this->r=r;}
    inline void setA(double a){this->a=a;}
    inline void setB(double b){this->b=b;}

    inline void setO(double xo,double yo,double zo)
    {
        this->xo=xo;
        this->yo=yo;
        this->zo=zo;
    }

    inline void clear(){drawable_objects.clear();}

public slots:
    void slot_front();
    void slot_back();
    void slot_left();
    void slot_right();
    void slot_top();
    void slot_bottom();
    void slot_init();
    void slot_set_data( std::vector<std::vector<std::vector<double>>> data,Box box);
    void setGradient(int preset);

protected:
    void resizeGL(int w, int h);
    void paintGL();
    void initializeGL();
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void mouseReleaseEvent ( QMouseEvent * event );
    void wheelEvent( QWheelEvent * event );

private:
    void createPopup();

    QVector<double> Viewer3D::extract(std::vector<VectorXd> v,int id);

    //Vue
    double a,b,r;
    double xo,yo,zo;
    int mx,my;
    double vcam[3];
    void updateCamera()
    {
        vcam[0]=xo-r*cos(a)*cos(b);
        vcam[1]=yo-r*sin(b);
        vcam[2]=zo-r*sin(a)*cos(b);
    }

    QMenu * popup_menu;

    std::vector<DrawableInterface *> drawable_objects;

    QMutex * mutex;
    bool display_axis;
    int mode;

    QAction* actFront;
    QAction* actBack;
    QAction* actLeft;
    QAction* actRight;
    QAction* actTop;
    QAction* actBottom;
    QAction* actInit;


    QCPColorGradient gradient;
    void searchMinMax(const std::vector<std::vector<std::vector<double> >> &data, double &min, double &max);
    void calcDataClamped(const std::vector<std::vector<std::vector<double>>> & data);
    void calcCloud();

    std::vector<Vector3d> data_positions_clamped;
    std::vector<double> data_clamped;
    std::vector<QRgb> cloud;
    std::vector<Vector3b> cloud_colors;
    double cut;

    Box box;
};

#endif
