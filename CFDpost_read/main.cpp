//
//ע��tecplot���б�Ƕ���1��ʼ�����롢���ʱҪע�⡣
//


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
    commads["-cfd"] = "E:\\PROJECTS\\CFD\\X43A\\object-mesh\\open\\data\\cfdpost.cdat";
    read_CFD_Post(commads,cfdData);

    cfdData.pface[0].get_neighbor();
    commads["-outName"] = "E:\\PROJECTS\\PLAYGROUND\\CFDpost_read\\tecplot_polygon.dat";
    write_tecplot(commads,cfdData.pface[0]);
    /*
    commads["-cfd"] = "E:\\PROJECTS\\CFD\\X43A\\object-mesh\\open\\data\\tecplot.dat";
    commads["-title"] = "Test";
    write_tecplot(commads,cfdData);
    */

/*
    iivector node2face(10, ivector(1, 0));
    iivector face;
    vector<pair<int,int>> facelist;//cfdpost��tecplot�ж�����ʱ�������
    //����Ϊ��left ��right
    ivector left_e;
    ivector right_e;
    //��������
    ivector tmp1={5,4,3,2,1};
    ivector tmp2={1,8,7,6,5};
    ivector tmp3={5,6,9,10};
    face.push_back(tmp1);
    face.push_back(tmp2);
    face.push_back(tmp3);
    for(size_t i=0;i<face.size();++i)
    {
        for(size_t j=0;j<face[i].size();++j)
        {
            // ����ڵ�����Ԫ�Ķ�Ӧ��ϵ
            node2face[face[i][j]-1].push_back(i+1);//teplot�нڵ��1��ʼ
            //����facelist
            int jp=(j==face[i].size()-1)?0:j+1;
            facelist.push_back(make_pair(face[i][j],face[i][jp]));
            cout<<face[i][j]<<" "<<face[i][jp]<<endl;
        }
    }
    //��յ�һ��0��ʵ�ֵĲ��ô��Ż����ܲ��ܲ�����ʼ����0��
    for(auto it=node2face.begin();it!=node2face.end();++it)
    {
        auto itt=it->begin();
        it->erase(itt);
    }

    for(size_t i=0;i<face.size();++i)
    {
        for(size_t j=0;j<face[i].size();j++)
        {
            left_e.push_back(i+1);
        }
    }
    for(size_t i=0;i<facelist.size();i++)
    {
        ivector v;
        set_intersection(node2face[facelist[i].first-1].begin(),node2face[facelist[i].first-1].end(),
                node2face[facelist[i].second-1].begin(),node2face[facelist[i].second-1].end(),back_inserter(v));
        if(v.size()==1)
        {
            right_e.push_back(0);
        }
        else if(v.size()==2)
        {
            int right=(v[0]==left_e[i])?v[1]:v[0];
            right_e.push_back(right);
        }
        else
        {

        }

    }

    cout<<endl<<"# left"<<endl;
    for(size_t i=0;i<left_e.size();++i)
    {
        cout<<left_e[i]<<" ";
    }
    cout<<endl<<"# right"<<endl;
    for(size_t i=0;i<right_e.size();++i)
    {
        cout<<right_e[i]<<" ";
    }
*/

    return 0;
}


