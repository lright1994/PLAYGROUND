#ifndef DEFINE_H
#define DEFINE_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <stdio.h>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <time.h>
#include <istream>
#include <sstream>
#include <assert.h>
#include <fstream>
#include <algorithm>
#include <map>

using namespace std;

typedef std::vector<int> ivector;
typedef std::vector<ivector> iivector;
typedef std::vector<double> rvector;
typedef std::vector<rvector> rrvector;
typedef std::vector<double *> rpvector;
typedef std::vector<std::string> svector;
typedef std::map<std::string, std::string> ssmap;

class KPoint{
public:
    double	x;
    double	y;
    double	z;
    int		index;

    double getLength()  const{return sqrt(x*x+y*y+z*z);}
    double getLengthSq()const{return x*x+y*y+z*z;}

    KPoint  operator- (const KPoint &pnt) const {return KPoint(x-pnt.x, y-pnt.y, z-pnt.z);}
    KPoint  operator- () const {return KPoint(-x, -y, -z);}
    KPoint  operator+ (const KPoint &pnt) const {return KPoint(x+pnt.x, y+pnt.y, z+pnt.z);}
    KPoint  operator* (const double &in) const {return KPoint(x*in   , y*in   , z*in   );}
    KPoint  operator/ (const double &in) const {return KPoint(x/in   , y/in   , z/in   );}
    double    operator* (const KPoint &pnt) const {return x*pnt.x + y*pnt.y + z*pnt.z;}
    void 	operator +=(const KPoint &rhs) {*this = *this + rhs;}
    void 	operator -=(const KPoint &rhs) {*this = *this - rhs;}
    void 	operator *=(const double rhs) {*this = *this * rhs;}
    void 	operator /=(const double rhs) {*this = *this / rhs;}

    friend KPoint operator* (double lhs, const KPoint &rhs) {return rhs*lhs;}

    KPoint operator^ (const KPoint &pnt) const {
        return KPoint( y * pnt.z - z * pnt.y,
            z * pnt.x - x * pnt.z,
            x * pnt.y - y * pnt.x );
    }

    KPoint operator= (const KPoint &pnt) {
        if(&pnt == this) return *this;
        x=pnt.x;
        y=pnt.y;
        z=pnt.z;
        index=pnt.index;
        return *this;
    }

    KPoint operator= (double in) {
        x=in;
        y=in;
        z=in;
        return *this;
    }

    void unit()
    {
        double tmp = 1.0/getLength();
        x *= tmp;
        y *= tmp;
        z *= tmp;
    }

    void set(const double &xin, const double &yin, const double &zin)
    {
        x=xin; y=yin; z=zin;
    }
    void set(const double &xin, const double &yin, const double &zin, const int &in)
    {
        x=xin; y=yin; z=zin; index=in;
    }

    KPoint():x(0.),y(0.),z(0.),index(-1){}
    KPoint(double xin, double yin, double zin) {x=xin; y=yin; z=zin; index=-1;}
    KPoint(double xin, double yin, double zin, int in){x=xin; y=yin; z=zin; index=in;}
    ~KPoint(){};
};typedef KPoint KVector;
typedef vector<KPoint> KPVector;
typedef vector<KPVector> KPPVector;

#ifndef MAX
#define MAX(a,b) (((a)>(b))?(a):(b))
#endif

#ifndef MIN
#define MIN(a,b) (((a)<(b))?(a):(b))
#endif



class CFD_Post_Face
{
public:
    rvector x,y,z;
    iivector face2node;
    rvector p,cp;
    rvector st;//static temperature;

    std::vector<KPoint> fn,fc;
    rvector area;

    int find_nearest_face(KPoint pnt, double &min_dist);

    double get_value_p(KPoint pnt, int fid);
    double get_value_cp(KPoint pnt, int fid);
};

class CFD_Post
{
public:
    std::vector<CFD_Post_Face> pface;
};

void split_string(std::string &chars, svector &strvec);
void read_CFD_Post(ssmap &commads, CFD_Post &cfdpdata);
void write_tecplot(map<string, string>& commads, CFD_Post &cfdpdata);

#endif // DEFINE_H
