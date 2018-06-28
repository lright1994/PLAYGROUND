#ifndef DEFINE_H
#define DEFINE_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

using std::cout;
using std::endl;
using std::stringstream;
using std::ofstream;


namespace tsp
{
    //三角面片网格与多边形网格的尺寸呢比，之后寻求自动求解，暂用定值
    static const double  RATE_TRI2POLY_X = 25.41;
    static const double  RATE_TRI2POLY_Y = 25.28;
    static const double  RATE_TRI2POLY_Z = 25.03;


    class   v3
    {
    public:
        v3();
        v3(char* bin);
        v3(double x, double y, double z);

        double m_x, m_y, m_z;
    };

    class tri
    {
        public:

        tri();
        tri(v3 p1, v3 p2, v3 p3);
        void draw();

        v3 m_p1, m_p2, m_p3;
    };

    using vec_tri = std::vector<tri>;



    void read_stl(std::string fname, vec_tri &v);
    void write_tecplot(std::string fname, const vec_tri& vecTri);

    template <typename Out>
    void inline output_line(int &count,ofstream& outfile,const Out&out)
    {
        outfile<<out<<" ";
        ++count;
        if(count%20==0)
        {
            outfile<<endl;
            count=0;
        }
    }
    double inline max_three(double d1, double d2, double d3)
    {
        double out = d1 > d2 ? d1 : d2;
        out = out > d3 ? out : d3;

        return out;
    }
}


#endif // DEFINE_H
