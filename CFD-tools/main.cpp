#include "define.h"

using namespace tsp;
int main()
{
    vec_tri m_tri;
    read_stl("E:\\PROJECTS\\PLAYGROUND\\CFD-tools\\data\\X43A_open_fix.stl", m_tri);
    write_tecplot("E:\\PROJECTS\\PLAYGROUND\\CFD-tools\\data\\test.dat",m_tri);

    return 0;
}
