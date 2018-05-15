#include <iostream>
#include <sstream>
#include <vector>

#include "cgnslib.h"
#include "cgns_header.h"

#include "cgnsclass.h"


using namespace std;

inline void errChk(const int& ierr, const string& err_msg){
    if (ierr!=CG_OK){
        cout<<"Failed to read cgns file during: "<<err_msg<<endl;
        cg_error_exit();
    }
    else{
        return;
    }
}
inline void prMsg(const string & Msg){
    cout<<"// "<<Msg<<endl;
}

void read_bc_conditions(char* name, int **bc);


int main(){


    string mFilename="E:\\PROJECTS\\PLAYGROUND\\CGNS\\X43A32Bit.cgns";
    CgnsClass mCgns(mFilename);
    mCgns.read_bc_conditions();
    mCgns.read_coords();
    //mCgns.write_bc_coords("bc_coords.txt");
    //mCgns.write_coords("coords.txt");
    /*
    int index_file;
    int numBase;
    int numZone;
    int ierr;
    string fileName="E:\\PROJECTS\\PLAYGROUND\\CGNS\\X43A32Bit.cgns";
    cout<<"FileName: "<<fileName<<endl;
    cout<<"////////////////////////////////////////////////////////////"<<endl;
    ierr=cg_open(fileName.c_str(),CG_MODE_READ,&index_file);
    errChk(ierr,"open file");

    //////////////////////////////////////////////////////////////////////////
    //Base
    ierr = cg_nbases(index_file,&numBase);
    errChk(ierr,"check base");
    auto index_base=numBase;
    cout<<"BaseNumber: "<<numBase<<endl;
    char baseName[32];
    int icelldim = 0;
    int iphysdim = 0;
    ierr = cg_base_read(index_file,index_base,baseName,&icelldim,&iphysdim);
    errChk(ierr,"read base");
    cout<<"BaseName: "<<baseName<<endl;
    cout<<"Dimension: "<<"cell:"<<icelldim<<"  phy:"<<iphysdim<<endl;
    //////////////////////////////////////////////////////////////////////////
    //Zones
    ierr=cg_nzones(index_file,index_base,&numZone);
    cout<<"ZoneNumber: "<<numZone<<endl;
    int index_zone = 1;
    CGNS_ENUMT(ZoneType_t) ZONETYPE;
    ierr = cg_zone_type(index_file,index_base,index_zone,&ZONETYPE);
    cout<<"ZoneType: "<<((ZONETYPE==Structured)?"Structures":"Unstructures")<<endl;
    char zoneName[32];
    cgsize_t zoneSize[9];
    ierr=cg_zone_read(index_file,index_base,index_zone,zoneName,zoneSize);
    cout<<"ZoneName: "<<zoneName<<endl;
    cout<<"NVertex: "<<zoneSize[0]<<endl;
    errChk(ierr,"open zones");
    //////////////////////////////////////////////////////////////////////////
    //Grids ??怎么用?? 好像要用到cg_goto之类的才能读取网格位置
    GridLocation_t gridLocation;
    int ngrids;
    char gridName[32];
    //ierr = cg_gridlocation_read(&gridLocation);
    //cout<<"GridLocation: "<<gridLocation<<endl;
    ierr = cg_ngrids(index_file,index_base,index_zone,&ngrids);
    cout<<"GridNumber: "<<ngrids<<endl;
    for(int i = 1; i<ngrids+1;i++){
        ierr = cg_grid_read(index_file,index_base,index_zone,i,gridName);
        cout<<"GridName: "<<gridName<<endl;
    }
    errChk(ierr,"read grid");
    //////////////////////////////////////////////////////////////////////////
    //Solution Data 1sol 1field
    DataType_t fieldType;
    char fieldName[32];
    ierr = cg_field_info(index_file,index_base,index_zone,1,1,&fieldType,fieldName);
    cout<<"FieldType: "<<fieldName<<"  "<<"FieldName: "<<fieldName<<endl;
    errChk(ierr,"read field");

    //重点研究如何读取field中的数据
    //cg_field_read

    //////////////////////////////////////////////////////////////////////////
    //Boundary Condition
    int nbocos,normalList;
    char bocoName[32];
    BCType_t bocotype;
    PointSetType_t ptset_type;
    cgsize_t npnts;
    cgsize_t* ipnts;
    int NormalIndex;
    cgsize_t  NormalListSize;
    DataType_t NormalDataType;
    GridLocation_t bcGridLocation;
    int ndataset;
    ierr = cg_nbocos(index_file,index_base,index_zone,&nbocos);
    cout<<"Boco Number: "<<nbocos<<endl;
    for(int iBoco=1;iBoco<nbocos+1;iBoco++){
        ierr = cg_boco_info(index_file,index_base,index_zone,iBoco,bocoName,&bocotype,&ptset_type,&npnts,&NormalIndex,&NormalListSize,&NormalDataType,&ndataset);
            {
            cout<<"Boco Name: "<<bocoName<<endl;
            switch (bocotype) {
            case BCFarfield:
                cout<<"Boco Type: Far field"<<endl;
                break;
            case  BCWall:
                cout<<"Boco Type: Wall"<<endl;
            default:
                break;
             }

        }
        cout<<"Boco points: "<<"Total:"<<npnts<<endl;
        ipnts = new cgsize_t[npnts];
        ierr = cg_boco_read(index_file,index_base,index_zone,iBoco,ipnts,&normalList);
        errChk(ierr,"read boco pnts");

        for(int i=0;i<100;i++){
            cout<<"/:"<<ipnts[i];
        }

        cout<<endl;
        delete [] ipnts;
    }




    errChk(ierr,"read boundary condition");
    //////////////////////////////////////////////////////////////////////////
    //Coordinates 坐标
    // lower range index of vertices
    cgsize_t rmin = 1;
    // upper range index of vertices
    cgsize_t rmax = zoneSize[0];
    char coordx[20];
    char coordy[20];
    char coordz[20];
    int ncoords = 0;
    CGNS_ENUMT(DataType_t) DATATYPE;
    ierr = cg_ncoords(index_file,index_base,index_zone,&ncoords);
    errChk(ierr,"check coordinates");
    cout<<"CoordNumber: "<<ncoords<<endl;
    ierr = cg_coord_info(index_file,index_base,index_zone,1,&DATATYPE,coordx);
    ierr = cg_coord_info(index_file,index_base,index_zone,2,&DATATYPE,coordy);
    ierr = cg_coord_info(index_file,index_base,index_zone,3,&DATATYPE,coordz);
    errChk(ierr,"read coordinates");

    //////////////////////////////////////////////////////////////////////////
    // Get element connectivity and element type
    // reading nsections
    int nsections = 0;
    ierr = cg_nsections(index_file,index_base,index_zone,&nsections);
    errChk(ierr,"check sections");
    cout<<"SectionNumber: "<<nsections<<endl;

    for(int iSec=1; iSec<=nsections; iSec++){
            char SectionName[20];
            CGNS_ENUMT(ElementType_t) EleType;
            cgsize_t secStart;
            cgsize_t secEnd;
            int nbndry;
            int parent_flag;
            ierr = cg_section_read(
                        index_file,
                        index_base,
                        index_zone,
                        iSec,
                        SectionName,
                        &EleType,
                        &secStart,
                        &secEnd,
                        &nbndry,
                        &parent_flag);
            errChk(ierr,"read section:"+iSec);

            cout<<"==========================="<<endl;
            cout<<"SectionType"<<iSec<<":"<<EleType<<endl;

            // !!!输出的网格是多边形和NFACE格式的!!!可能之后要修改
            // npe什么意思？每个单元的节点数量，假如不清楚怎么办？
            //cgsize_t npe = 0;
            //ierr = cg_npe(EleType,&npe);
            //errChk(ierr,"read npe");

            cgsize_t elem_start = secStart;
            cgsize_t elem_end = secEnd;
            cgsize_t size_ielem = 0;
            ierr = cg_ElementDataSize(index_file,index_base,index_zone,iSec,&size_ielem);
            errChk(ierr,"check elementData");
            cout<<"ElementDataSize: "<<size_ielem<<"  "<<endl;
            cgsize_t* elemDataBuff = new cgsize_t[size_ielem];
            cgsize_t parent_data = 0;

            //读取了element数据之后如何差值？
            ierr = cg_elements_read(index_file,index_base,index_zone,iSec,elemDataBuff,&parent_data);
            //BCWallInviscid
            //cg_element_type_
    }

    cg_close(index_file);
    */
}

