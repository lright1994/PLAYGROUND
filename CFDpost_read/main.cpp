#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

#include "define.h"


using namespace std;





int main()
{
    map<string, string>commads;
    CFD_Post cfdData;
    //commads["-cfd"]="E:\\PROJECTS\\PLAYGROUND\\CGNS\\flntgz-1276484.cdat";
    commads["-cfd"] = "E:\\PROJECTS\\CFD\\X43A\\object-mesh\\open\\data\\cfdpost.cdat";
    //commads["-cfd"] = "E:\\PROJECTS\\PLAYGROUND\\CFDpost_read\\tecplot-data\\test.cdat";
    read_CFD_Post(commads,cfdData);

    commads["-cfd"] = "E:\\PROJECTS\\CFD\\X43A\\object-mesh\\open\\data\\tecplot.dat";
    commads["-title"] = "Test";
    write_tecplot(commads,cfdData);

    return 0;
}


