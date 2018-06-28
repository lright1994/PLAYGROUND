#include "kd_tree.h"
using namespace nanoflann;

using rrvector = std::vector<std::vector<double> >;

void get_kd_tree(int dim, const rrvector& data,)
{
    if(dim != data.size())
    {
        cout<<"wrong data dim"<<endl;
        return;
    }
}
