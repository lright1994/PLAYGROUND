#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

#include "define.h"
#include "read_cfd_post.h"

using namespace std;





int main()
{
    map<string, string>commads;
    CFD_Post cfdData;
    //commads["-cfd"]="E:\\PROJECTS\\PLAYGROUND\\CGNS\\flntgz-1276484.cdat";
    commads["-cfd"]="E:\\PROJECTS\\CFD\\X43A\\object-mesh\\open\\data\\cfdpost.cdat";
    read_CFD_Post(commads,cfdData);


    return 0;
}


