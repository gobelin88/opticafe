#include "3d_viewer.h"

Viewer3D::Viewer3D()
{
    popup_menu=new QMenu(this);

    display_grid=true;
    slot_init();
    createPopup();

    scale_color_mode=(ScaleColorMode)0;
    gamma=1.0;
    cut=1.0;

    mode=0;

    cloud.clear();
    data.clear();

    mutex=NULL;
}

Viewer3D::~Viewer3D()
{
    delete popup_menu;
    delete actFront;
    delete actBack;
    delete actLeft;
    delete actRight;
    delete actTop;
    delete actBottom;
    delete actInit;
}

void Viewer3D::createPopup()
{
    actFront   = new QAction("Front",  this);
    actFront->setShortcut(QKeySequence(tr("1")));
    actBack    = new QAction("Back",   this);
    actBack->setShortcut(QKeySequence(tr("2")));
    actLeft    = new QAction("Left",   this);
    actLeft->setShortcut(QKeySequence(tr("3")));
    actRight   = new QAction("Right",  this);
    actRight->setShortcut(QKeySequence(tr("4")));
    actTop     = new QAction("Top",    this);
    actTop->setShortcut(QKeySequence(tr("5")));
    actBottom  = new QAction("Bottom", this);
    actBottom->setShortcut(QKeySequence(tr("6")));
    actInit  = new QAction("Init", this);
    actInit->setShortcut(QKeySequence(tr("0")));

    this->addAction(actInit);
    this->addAction(actFront);
    this->addAction(actBack);
    this->addAction(actLeft);
    this->addAction(actRight);
    this->addAction(actTop);
    this->addAction(actBottom);

    popup_menu->addAction(actInit);
    popup_menu->addSeparator();
    popup_menu->addAction(actFront);
    popup_menu->addAction(actBack);
    popup_menu->addAction(actLeft);
    popup_menu->addAction(actRight);
    popup_menu->addAction(actTop);
    popup_menu->addAction(actBottom);

    connect(actInit,SIGNAL(triggered()),this,SLOT(slot_init()));
    connect(actFront,SIGNAL(triggered()),this,SLOT(slot_front()));
    connect(actBack,SIGNAL(triggered()),this,SLOT(slot_back()));
    connect(actLeft,SIGNAL(triggered()),this,SLOT(slot_left()));
    connect(actRight,SIGNAL(triggered()),this,SLOT(slot_right()));
    connect(actTop,SIGNAL(triggered()),this,SLOT(slot_top()));
    connect(actBottom,SIGNAL(triggered()),this,SLOT(slot_bottom()));
}

void Viewer3D::slot_init()
{
    a=M_PI/4.0;  b=-M_PI/4.0;
    r=0.5;
    xo=0.0;yo=0.0;zo=0.0;
    updateCamera();
    update();
}

void Viewer3D::slot_front()
{
    a=M_PI/2.0;  b=0;
    r=0.5;
    xo=0.0;yo=0.0;zo=0.0;
    updateCamera();
    update();
}

void Viewer3D::slot_back()
{
    a=-M_PI/2.0;  b=0;
    r=0.5;
    xo=0.0;yo=0.0;zo=0.0;
    updateCamera();
    update();
}

void Viewer3D::slot_left()
{
    a=0.0;  b=0;
    r=0.5;
    xo=0.0;yo=0.0;zo=0.0;
    updateCamera();
    update();
}

void Viewer3D::slot_right()
{
    a=M_PI;  b=0;
    r=0.5;
    xo=0.0;yo=0.0;zo=0.0;
    updateCamera();
    update();
}

void Viewer3D::slot_top()
{
    a=0.0;  b=M_PI/2.0;
    r=0.5;
    xo=0.0;yo=0.0;zo=0.0;
    updateCamera();
    update();
}

void Viewer3D::slot_bottom()
{
    a=0.0;  b=-M_PI/2.0;
    r=0.5;
    xo=0.0;yo=0.0;zo=0.0;
    updateCamera();
    update();
}

void Viewer3D::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,(GLdouble)w/(GLdouble)h,0.001,1000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(1,1,1,0);
}

void Viewer3D::paintGL()
{

    if( !mutex || (mutex && mutex->tryLock()) )
    {
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
        glLoadIdentity();

        gluLookAt(vcam[0],vcam[1],vcam[2],
                xo,yo,zo,0,1,0);

        glBegin(GL_POINTS);
        for(unsigned int i=0;i<cloud.size();i++)
        {
            qglColor(cloud[i].second);
            glVertex3dv(&cloud[i].first[0]);
        }
        glEnd();

        glPushMatrix();
        glScaled(-1.0,1.0,1.0);
        //GLdouble light_position[] = { -1.0, -1.0, -1.0, 0.0 };
        //glLightfv(GL_LIGHT0, GL_POSITION, light_position);

        if(display_grid)
        {
            glEnable (GL_LINE_SMOOTH);
            glEnable (GL_BLEND);
            glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);

            double step=0.01;
            double s=0.5;

            int i=0;
            for(double x=-s;x<s+step;x+=step)
            {
                if((i++)%5==0) {glColor3f(0,0,0);glLineWidth(1.5);}
                else {glColor3f(0.5,0.5,0.5);glLineWidth(1);}

                glBegin(GL_LINES);
                glVertex3d(x,0,-s);
                glVertex3d(x,0,s);

                glVertex3d(-s,0,x);
                glVertex3d(s,0,x);
                glEnd();
            }

            glDisable (GL_BLEND);
            glDisable (GL_LINE_SMOOTH);
        }

        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);

        glColor3f(1,1,1);
        for(unsigned int i=0;i<drawable_objects.size();i++)
        {
            if(drawable_objects[i])
            {
                glColor3f(1,1,1);
                //glColor3fv(drawable_objects[i]->color);
                if(drawable_objects[i]->mutex!=NULL)drawable_objects[i]->mutex->lock();
                drawable_objects[i]->draw(mode,this);
                if(drawable_objects[i]->mutex!=NULL)drawable_objects[i]->mutex->unlock();
            }
        }

        glDisable(GL_LIGHTING);


        if(mutex)mutex->unlock();
    }

    glPopMatrix();

}




void Viewer3D::initializeGL()
{
    glClearColor(0.0,0.0,0.0,0.0);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    GLfloat global_ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);

    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    glShadeModel (GL_SMOOTH);

    glEnable(GL_COLOR_MATERIAL);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, light_diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat_shininess);    

    GLfloat light_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}

void Viewer3D::mouseMoveEvent(QMouseEvent * e)
{
    if(e->buttons()==Qt::MiddleButton)
    {

        Vector3d u( cos(a)*cos(b) , sin(b) , sin(a)*cos(b) );
        Vector3d v( cos(a)*cos(b+M_PI/2.0) , sin(b+M_PI/2.0) , sin(a)*cos(b+M_PI/2.0) );
        Vector3d w=u.cross(v);

        double scalex=(mx-e->x())/1000.0;
        double scaley=(my-e->y())/1000.0;

        xo=xo-(-w[0]*scalex+v[0]*scaley);
        yo=yo-(-w[1]*scalex+v[1]*scaley);
        zo=zo-(-w[2]*scalex+v[2]*scaley);

    }
    else if(e->buttons()==Qt::LeftButton)
    {
        a-=(mx-e->x())/100.0;
        b+=(my-e->y())/100.0;

        if(a>2*M_PI)a=a-M_PI*2;
        if(a<0)a=a+M_PI*2;
        if(b>M_PI/2.01)b=M_PI/2.01;
        if(b<-M_PI/2.01)b=-M_PI/2.01;
    }
    mx=e->x();
    my=e->y();

    updateCamera();
    update();
}

void Viewer3D::wheelEvent( QWheelEvent * event )
{
    r+=( event->delta() )/10000.0;
    if(r<0)r=0;
    updateCamera();
    update();
}

void Viewer3D::mousePressEvent(QMouseEvent * e)
{
    mx=e->x();
    my=e->y();

    update();
}

void Viewer3D::mouseDoubleClickEvent(QMouseEvent * event)
{
    if(event->button() == Qt::LeftButton)
    {
        display_grid=!display_grid;
    }
    else if(event->button() == Qt::MiddleButton)
    {
        mode=1-mode;
    }
    update();
}

void Viewer3D::mouseReleaseEvent ( QMouseEvent * event )
{
    if(event->button() == Qt::RightButton)
    {
        popup_menu->exec(mapToGlobal(event->pos()));
    }
    QGLWidget::mouseReleaseEvent(event);  //Dont forget to pass on the event to parent
}

void Viewer3D::add(DrawableInterface * drawable_object)
{
    if(drawable_object!=NULL)
    {
        drawable_objects.push_back(drawable_object);
    }
}

void Viewer3D::slot_set_gamma(double value)
{
    this->gamma=value;
    cloud=System::toCloud(data,scale_color_mode,gamma,cut,0.001);
    update();
}

void Viewer3D::slot_set_color_mode(int color_mode)
{
    this->scale_color_mode=(ScaleColorMode)color_mode;
    cloud=System::toCloud(data,scale_color_mode,gamma,cut,0.001);
    update();
}

void Viewer3D::slot_set_data(std::vector<std::vector<std::vector<double>>> data)
{
    this->data=data;
    cloud=System::toCloud(data,scale_color_mode,gamma,cut,0.001);
    update();
}

void Viewer3D::slot_set_cut(double value)
{
    this->cut=value;
    cloud=System::toCloud(data,scale_color_mode,gamma,cut,0.001);
    update();
}
