#include "3d_viewer.h"

Viewer3D::Viewer3D()
{
    popup_menu=new QMenu(this);

    display_axis=true;
    slot_init();
    createPopup();

    cut=1.0;

    mode=0;

    cloud.clear();
    data_clamped.clear();
    cloud_colors.clear();

    mutex=NULL;

    gradient.loadPreset(QCPColorGradient::gpGrayscale);

    box.p0_min=-1;
    box.p0_max=1;
    box.p0_res=100;
    box.p1_min=-1;
    box.p1_max=1;
    box.p1_res=100;
    box.p2_min=-1;
    box.p2_max=1;
    box.p2_res=100;
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

QVector<double> Viewer3D::extract(std::vector<VectorXd> v,int id)
{
    QVector<double> v_out(v.size());
    for(unsigned int i=0;i<v.size();i++)
    {
        v_out[i]=v[i][id];
    }
    return v_out;
}

void Viewer3D::setPath(std::vector<VectorXd> path)
{

}

void Viewer3D::slot_init()
{
    a=M_PI/4.0;  b=-M_PI/4.0;
    r=1;
    xo=0.0;yo=0.0;zo=0.0;
    updateCamera();
    update();
}

void Viewer3D::slot_front()
{
    a=M_PI/2.0;  b=0;
    r=1;
    xo=0.0;yo=0.0;zo=0.0;
    updateCamera();
    update();
}

void Viewer3D::slot_back()
{
    a=-M_PI/2.0;  b=0;
    r=1;
    xo=0.0;yo=0.0;zo=0.0;
    updateCamera();
    update();
}

void Viewer3D::slot_left()
{
    a=0.0;  b=0;
    r=1;
    xo=0.0;yo=0.0;zo=0.0;
    updateCamera();
    update();
}

void Viewer3D::slot_right()
{
    a=M_PI;  b=0;
    r=1;
    xo=0.0;yo=0.0;zo=0.0;
    updateCamera();
    update();
}

void Viewer3D::slot_top()
{
    a=0.0;  b=M_PI/2.0;
    r=1;
    xo=0.0;yo=0.0;zo=0.0;
    updateCamera();
    update();
}

void Viewer3D::slot_bottom()
{
    a=0.0;  b=-M_PI/2.0;
    r=1;
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

        glColor3f(0,0,0);
        if(cloud.size()>0)
        {
            glEnableClientState(GL_VERTEX_ARRAY);
            glVertexPointer(3, GL_DOUBLE, 0, data_positions_clamped.data());

            glEnableClientState(GL_COLOR_ARRAY);
            glColorPointer (3, GL_UNSIGNED_BYTE,0, cloud_colors.data());

            glDrawArrays(GL_POINTS, 0, data_positions_clamped.size());

            glDisableClientState(GL_VERTEX_ARRAY);
            glDisableClientState(GL_COLOR_ARRAY);
        }


        //GLdouble light_position[] = { -1.0, -1.0, -1.0, 0.0 };
        //glLightfv(GL_LIGHT0, GL_POSITION, light_position);

        if(display_axis)
        {
            glEnable (GL_LINE_SMOOTH);
            glEnable (GL_BLEND);
            glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);


            double margeX=0.2*(box.p0_max-box.p0_min);
            double margeY=0.2*(box.p1_max-box.p1_min);
            double margeZ=0.2*(box.p2_max-box.p2_min);

            glColor3f(0,0,0);
            glBegin(GL_LINES);

                glVertex3d(box.p0_min,box.p1_min,box.p2_min);
                glVertex3d(box.p0_max+margeX,box.p1_min,box.p2_min);

                glVertex3d(box.p0_min,box.p1_min,box.p2_min);
                glVertex3d(box.p0_min,box.p1_max+margeY,box.p2_min);

                glVertex3d(box.p0_min,box.p1_min,box.p2_min);
                glVertex3d(box.p0_min,box.p1_min,box.p2_max+margeZ);

            glEnd();

            renderText(box.p0_max+margeX,box.p1_min,box.p2_min,QString("p%1").arg(box.id1));
            renderText(box.p0_min,box.p1_max+margeY,box.p2_min,QString("p%1").arg(box.id2));
            renderText(box.p0_min,box.p1_min,box.p2_max+margeZ,QString("p%1").arg(box.id3));

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
    r*=1+( event->delta() )/1000.0;
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
        display_axis=!display_axis;
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

void Viewer3D::searchMinMax(const std::vector<std::vector<std::vector<double> >> &data, double &min, double &max)
{
    min=data[0][0][0];
    max=data[0][0][0];


    for(unsigned int i=1;i<data.size();i++)
    {
        for(unsigned int j=0;j<data[0].size();j++)
        {
            for(unsigned int k=0;k<data[0][0].size();k++)
            {
                if(data[i][j][k]<min)min=data[i][j][k];
                if(data[i][j][k]>max)max=data[i][j][k];
            }
        }
    }
}

void Viewer3D::calcDataClamped(const std::vector<std::vector<std::vector<double>>> & data)
{
    unsigned int nb=data.size()*data[0].size()*data[0][0].size();
    data_clamped.resize (nb,0.0);
    data_positions_clamped.resize (nb,Vector3d(0,0,0));

    double min,max;
    searchMinMax(data,min,max);

    unsigned int index=0;
    for(unsigned int i=0;i<data.size();i++)
    {
        for(unsigned int j=0;j<data[0].size();j++)
        {
            for(unsigned int k=0;k<data[0][0].size();k++)
            {
                data_clamped[index]= (data[i][j][k]-min)/(max-min);
                data_positions_clamped[index]=Vector3d(box.getP0(i),
                                                       box.getP0(j),
                                                       box.getP0(k));
                index++;
            }
        }
    }
}

void Viewer3D::setGradient(int preset)
{
    gradient.loadPreset((QCPColorGradient::GradientPreset)preset);
    calcCloud();
    update();
}

void Viewer3D::slot_set_data(std::vector<std::vector<std::vector<double>>> data,Box box)
{
    this->box=box;
    calcDataClamped(data);
    calcCloud();
    update();
}

void Viewer3D::calcCloud()
{
    QCPRange range(0,1);
    cloud.resize(data_clamped.size(),QRgb(0));
    cloud_colors.resize(data_clamped.size(),Vector3b(0,0,0));

    gradient.colorize(data_clamped.data(),range,cloud.data(),data_clamped.size());

    for(int i=0;i<data_clamped.size();i++)
    {
        cloud_colors[i]=Vector3b(qRed(cloud[i]),
                                 qGreen(cloud[i]),
                                 qBlue(cloud[i]));
    }
}
