//   STL格式
//   char[80] (80 bytes) – Header
//   unsigned long (4 bytes) – Number of triangles
//
//   foreach triangle
//       float[3] (12 bytes) – Normal vector
//       float[3] (12 bytes) – Vertex 1
//       float[3] (12 bytes) – Vertex 2
//       float[3] (12 bytes) – Vertex 3
//       short (2 bytes) – Attribute byte count
//   end

#include <define.h>





tsp::v3::v3(char *facet)
{
    char f1[4] = {facet[0],
            facet[1],facet[2],facet[3]};
    char f2[4] = {facet[4],
        facet[5],facet[6],facet[7]};
    char f3[4] = {facet[8],
        facet[9],facet[10],facet[11]};

    float xx = *((float*) f1 );
    float yy = *((float*) f2 );
    float zz = *((float*) f3 );

    //转化为与多面体网格相同的尺寸
    m_x = double(xx/RATE_TRI2POLY_X);
    m_y = double(yy/RATE_TRI2POLY_Y);
    m_z = double(zz/RATE_TRI2POLY_Z);
}

tsp::tri::tri(v3 p1, v3 p2, v3 p3):
    m_p1(p1),m_p2(p2),m_p3(p3)
{

}

void tsp::read_stl(std::string fname, vec_tri &v_tri)
{
    std::ifstream myFile (fname.c_str(), std::ios::in | std::ios::binary);

    double max_coord[3];
    max_coord[0]=max_coord[1]=max_coord[2]=0.0;

    char header_info[80] = "";
    char nTri[4];
    unsigned long nTriLong;

    //read 80 byte header
    if (myFile)
    {
        myFile.read (header_info, 80);
    }
    else
    {
        cout << "error" << endl;
    }
    //read 4-byte ulong
    if (myFile)
    {
        myFile.read (nTri, 4);
        nTriLong = *((unsigned long*)nTri) ;
    }
    else{
        cout << "error" << endl;
    }

    //now read in all the triangles
    for(int i = 0; i < nTriLong; i++)
    {

        char facet[50];
        if (myFile)
        {
            myFile.read (facet, 50);
            v3 p1(facet+12);
            v3 p2(facet+24);
            v3 p3(facet+36);
//            //获取STL中的x,y,z坐标的最大值，为了和多边形网格对应
//            double m_tx = max_three(p1.m_x,p2.m_x,p3.m_x);
//            double m_ty = max_three(p1.m_y,p2.m_y,p3.m_y);
//            double m_tz = max_three(p1.m_z,p2.m_z,p3.m_z);

//            max_coord[0] = max_coord[0] >m_tx ? max_coord[0] : m_tx;
//            max_coord[1] = max_coord[1] >m_ty ? max_coord[1] : m_ty;
//            max_coord[2] = max_coord[2] >m_tz ? max_coord[2] : m_tz;

            //add a new triangle to the array
            v_tri.push_back( tri(p1,p2,p3) );
        }
    }

//    cout<<"x max: "<<max_coord[0]<<endl
//       <<"y max: "<<max_coord[1]<<endl
//      <<"z max: "<<max_coord[2]<<endl;

    return;
}

void tsp::write_tecplot(std::string fileName, const vec_tri &Tri)
{
    // 输出题头
    stringstream ss;
    ofstream outfile(fileName.c_str());


    int num_tri = Tri.size();
    int num_points = num_tri*3;

    //先只考虑单一区间 XYZ + 温度数据
    ss<<"TITLE = \"STL\" \n";
    ss<<"VARIABLES = \"X\", \"Y\", \"Z\", \"Temperature\"\n";
    ss<<"ZONE N = "<<num_points<<", E = "<<num_tri<<", DATAPACKING = POINT, ZONETYPE = FETRIANGLE\n";
    outfile<<ss.str();

    //输出点数据
    for(size_t i = 0 ; i < num_tri ; i++)
    {
        outfile<<Tri[i].m_p1.m_x<<" "<<Tri[i].m_p1.m_y<<" "<<Tri[i].m_p1.m_z<<" "<<0.0<<endl;
        outfile<<Tri[i].m_p2.m_x<<" "<<Tri[i].m_p2.m_y<<" "<<Tri[i].m_p2.m_z<<" "<<0.0<<endl;
        outfile<<Tri[i].m_p3.m_x<<" "<<Tri[i].m_p3.m_y<<" "<<Tri[i].m_p3.m_z<<" "<<0.0<<endl;
    }
    outfile<<endl;
    //输出三角面片连接关系
    int count = 0;
    for(size_t i = 0 ; i< num_points ; i++)
    {
        output_line(count, outfile, i+1);
    }

    return;
}
