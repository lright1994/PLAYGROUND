#include "define.h"


int CFD_Post_Face::find_nearest_face(KPoint pnt, double &min_dist)
{
    min_dist = 1.0e20; int i_min_dist=-1;
    for(int f=0; f<fc.size(); f++)
    {
        double tmp = (fc[f] - pnt).getLength();

        if(tmp < min_dist){
            min_dist = tmp;
            i_min_dist = f;
        }
    }

    return i_min_dist;
}

double CFD_Post_Face::get_value_p(KPoint pnt, int fid)
{
    ivector &f2n = face2node[fid];

    double p_aver = 0.0, wei = 0.0;
    for(int i=0; i<f2n.size(); i++)
    {
        int nid = f2n[i];
        KPoint p0(x[nid], y[nid], z[nid]);

        double dist = (pnt - p0).getLength();

        wei    += 1.0    / (dist + 1.0e-20);
        p_aver += p[nid] / (dist + 1.0e-20);
    }

    p_aver /= wei;

    return p_aver;
}

double CFD_Post_Face::get_value_cp(KPoint pnt, int fid)
{
    ivector &f2n = face2node[fid];

    double p_aver = 0.0, wei = 0.0;
    for(int i=0; i<f2n.size(); i++)
    {
        int nid = f2n[i];
        KPoint p0(x[nid], y[nid], z[nid]);

        double dist = (pnt - p0).getLength();

        wei    += 1.0    / (dist + 1.0e-20);
        p_aver += cp[nid]/ (dist + 1.0e-20);
    }

    p_aver /= wei;

    return p_aver;
}
