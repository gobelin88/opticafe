#include <QtOpenGL>
#include <QGLWidget>

#ifndef DRAWABLEINTERFACE_H
#define DRAWABLEINTERFACE_H

class DrawableInterface
{
public:
    DrawableInterface()
    {
        color[0]=1.0;
        color[1]=1.0;
        color[2]=1.0;

        this->mutex=NULL;
    }

    virtual void draw(int mode,QGLWidget * widget)=0;

    void setMutex(QMutex * mutex){this->mutex=mutex;}

    void setColor(double r,double g,double b)
    {
        color[0]=r;
        color[1]=g;
        color[2]=b;
    }

    double color[3];
    QMutex * mutex;
};

#endif // DRAWABLEINTERFACE_H
