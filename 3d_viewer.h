#include <iostream>
#include <assert.h>

//Qt
#include <QtOpenGL>
#include <QGLWidget>
#include <gl/GLU.h>

//Std

//Autre
#include "DrawableInterface.h"
#include "system.h"

//Eigen
#include <Eigen/Dense>
using Eigen::Vector3d;
using Eigen::VectorXd;

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

    void add(DrawableInterface * drawable_object);

    inline void enableGrid(bool value){display_grid=value;}
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

    void setBox(Box box){this->box=box;}

public slots:
    void slot_front();
    void slot_back();
    void slot_left();
    void slot_right();
    void slot_top();
    void slot_bottom();
    void slot_init();
    void slot_set_gamma(double value);
    void slot_set_cut(double value);
    void slot_set_color_mode(int color_mode);
    void slot_set_data( std::vector<std::vector<std::vector<double>>> data);

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
    bool display_grid;
    int mode;

    QAction* actFront;
    QAction* actBack;
    QAction* actLeft;
    QAction* actRight;
    QAction* actTop;
    QAction* actBottom;
    QAction* actInit;

    std::vector<std::vector<std::vector<double>>> data;
    std::vector<std::pair<Vector3d,QColor>> cloud;
    ScaleColorMode scale_color_mode;
    double gamma,cut;

    Box box;
};

#endif
