#ifndef BOX
#define BOX

struct Box
{
    Box()
    {
        this->p0_min=0;
        this->p0_max=0;
        this->p1_min=0;
        this->p1_max=0;
        this->p0_res=0;
        this->p1_res=0;
    }

    Box(double p0_min,double p0_max,double p1_min,double p1_max,double p0_res,double p1_res)
    {
        this->p0_min=p0_min;
        this->p0_max=p0_max;
        this->p1_min=p1_min;
        this->p1_max=p1_max;
        this->p0_res=p0_res;
        this->p1_res=p1_res;
    }

    double getP0(int i){return (i*(p0_max-p0_min))/p0_res+p0_min;}
    double getP1(int i){return (i*(p1_max-p1_min))/p1_res+p1_min;}
    int fromP0(double i){return (int)((p0_res*(i-p0_min))/(p0_max-p0_min));}
    int fromP1(double i){return (int)((p1_res*(i-p1_min))/(p1_max-p1_min));}

    double p0_min;
    double p0_max;
    double p1_min;
    double p1_max;
    int p0_res;
    int p1_res;

    void Box::operator=(const Box& copy)
    {
        this->p0_min=copy.p0_min;
        this->p0_max=copy.p0_max;
        this->p1_min=copy.p1_min;
        this->p1_max=copy.p1_max;
        this->p0_res=copy.p0_res;
        this->p1_res=copy.p1_res;
    }
};

#endif // BOX

