#include "cgnsclass.h"
#include "cgnslib.h"
#include "cgns_header.h"

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>



//为了简化，先假设只有一个file base zone
CgnsClass::CgnsClass(const string& filename):
    num_file(1),
    num_base(1),
    num_zone(1),
    fileName(filename)
{

}
CgnsClass::~CgnsClass()
{

}


int CgnsClass::read_bc_info()
{
    return 0;
}

void CgnsClass::errChk(const int& ierr,const string& Msg)
{
    if (ierr!=CG_OK){
        cout<<"Failed to read cgns file during: "<<Msg<<endl;
        cg_error_exit();
    }
    else{
        return;
    }
}

int CgnsClass::write_bc_coords(const string fileName)
{
    ofstream outPut;
    outPut.open(fileName);
    for(int i=0;i<bc_pnt_index[1].size();i++)
    {
        int index_vex=bc_pnt_index[1][i];
        outPut<<coords[index_vex][0]<<"  "<<coords[index_vex][1]<<"  "<<coords[index_vex][2]<<endl;
    }
    outPut.close();
    return 0;
}

int CgnsClass::write_coords(const string fileName)
{
    ofstream outPut;
    outPut.open(fileName);
    for(int i=0;i<coords.size();i++)
    {
        outPut<<coords[i][0]<<"  "<<coords[i][1]<<"  "<<coords[i][2]<<endl;
    }
    outPut.close();
    return 0;
}


int CgnsClass::read_bc_conditions()
{
    int index_file;
    cg_open(fileName.c_str(),CG_MODE_READ,&index_file);

    int ierr;
    int nbocos,normalList,NormalIndex;
    char bocoName[32];
    BCType_t bocotype;
    PointSetType_t ptset_type;
    cgsize_t npnts;
    cgsize_t* ipnts;
    cgsize_t  NormalListSize;
    DataType_t NormalDataType;
    //GridLocation_t bcGridLocation;
    int ndataset;

    ierr = cg_nbocos(index_file,1,1,&nbocos);
    cout<<"Boco Number: "<<nbocos<<endl;

    this->bc_pnt_index.clear();
    //vector<vector<int>>().swap(bc_points);

    for(int iBoco=1;iBoco<nbocos+1;iBoco++)
    {
        ierr = cg_boco_info(index_file,1,1,iBoco,bocoName,&bocotype,&ptset_type,&npnts,&NormalIndex,&NormalListSize,&NormalDataType,&ndataset);
        cout<<"Boco Name: "<<bocoName<<endl;
        switch (bocotype)
        {
        case BCFarfield:
            cout<<"Boco Type: Far field"<<endl;
            break;
        case  BCWall:
            cout<<"Boco Type: Wall"<<endl;
        default:
            break;
         }
        cout<<"Boco points: "<<"Total:"<<npnts<<endl;
        //cout<<"Bc dataset: "<<ndataset<<endl; 不是用dataset定义的


        ipnts = new cgsize_t[npnts];
        ierr = cg_boco_read(index_file,1,1,iBoco,ipnts,&normalList);//读取了边界点的位置
        cout<<"first point: "<<ipnts[1]<<"  "<<ipnts[2]<<"  "<<ipnts[3]<<endl;
        //cout<<"last point: "<<ipnts[3*npnts-2]<<"  "<<ipnts[3*npnts-1]<<"  "<<ipnts[3*npnts]<<endl;
/*
        vector<int> index_temp;
        for(int i=0;i<npnts;i++)
        {
            index_temp.push_back(ipnts[i]);
        }
        bc_pnt_index.push_back(index_temp);
        delete [] ipnts;
*/
    }
    return ierr;
    cg_close(index_file);
}


//读取坐标
int CgnsClass::read_coords()
{
    int index_file;
    int ierr;
    cg_open(fileName.c_str(),CG_MODE_READ,&index_file);

    char zoneName[32];
    cgsize_t zoneSize[9];

    ierr = cg_zone_read(index_file,1,1,zoneName,zoneSize);
    cout<<"Zone Vertex Number: "<<zoneSize[0]<<endl;
    cout<<"Zone Cell Number: "<<zoneSize[1]<<endl;

    // lower range index of vertices
    cgsize_t rmin = 1;
    // upper range index of vertices
    cgsize_t rmax = zoneSize[0];
    char coordx[20];
    char coordy[20];
    char coordz[20];
    int ncoords = 0;
    CGNS_ENUMT(DataType_t) DATATYPE;

    ierr = cg_ncoords(index_file,1,1,&ncoords);

    ierr = cg_coord_info(index_file,1,1,1,&DATATYPE,coordx);
    errChk(ierr,"getting coordinateX information");

    ierr = cg_coord_info(index_file,1,1,2,&DATATYPE,coordy);
    errChk(ierr,"getting coordinateY information");

    ierr = cg_coord_info(index_file,1,1,3,&DATATYPE,coordz);
    errChk(ierr,"getting coordinateZ information");

    //read x y z
    double* psx = new double[rmax];
    double* psy = new double[rmax];
    double* psz = new double[rmax];
    ierr = cg_coord_read(index_file,1,1,coordx,DATATYPE,&rmin,&rmax,(void*)psx);
    errChk(ierr,"reading x coordinates");

    ierr = cg_coord_read(index_file,1,1,coordy,DATATYPE,&rmin,&rmax,(void*)psy);
    errChk(ierr,"reading y coordinates");

    ierr = cg_coord_read(index_file,1,1,coordz,DATATYPE,&rmin,&rmax,(void*)psz);
    errChk(ierr,"reading z coordinates");

    //ofstream outTest;
    //outTest.open("test.txt");
    this->coords.clear();
    for(int i=0;i<rmax;i++)
    {
        vector<double> xyzTem;
        xyzTem.push_back(psx[i]);
        xyzTem.push_back(psy[i]);
        xyzTem.push_back(psz[i]);
        this->coords.push_back(xyzTem);
        //outTest<<psx[i]<<"  "<<psy[i]<<"  "<<psz[i]<<endl;
        xyzTem.clear();
        vector<double>().swap(xyzTem);

    }
    delete [] psx;
    delete [] psy;
    delete [] psz;

    //outTest.close();
    cg_close(index_file);
    return ierr;
}
