#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

#include "define.h"


using namespace std;





int main()
{
    /*
    map<string, string>commads;
    CFD_Post cfdData;
    commads["-cfd"] = "E:\\PROJECTS\\CFD\\X43A\\object-mesh\\open\\data\\cfdpost.cdat";
    read_CFD_Post(commads,cfdData);

    commads["-cfd"] = "E:\\PROJECTS\\CFD\\X43A\\object-mesh\\open\\data\\tecplot.dat";
    commads["-title"] = "Test";
    write_tecplot(commads,cfdData);
    */

    iivector node2face(8, ivector(1, 0));
    iivector face;
    vector<pair<int,int>> facelist;//cfdpost和tecplot中都是逆时针排序的
    //排序为先left 后right
    ivector left_e;
    ivector right_e;
    //测试数据
    ivector tmp1={5,4,3,2,1};
    ivector tmp2={1,8,7,6,5};
    face.push_back(tmp1);
    face.push_back(tmp2);
    for(size_t i=0;i<face.size();++i)
    {
        for(size_t j=0;j<face[i].size();++j)
        {
            // 输入节点与面元的对应关系
            node2face[face[i][j]-1].push_back(i+1);//teplot中节点从1开始
            //输入facelist
            int jp=(j==face[i].size()-1)?0:j+1;
            facelist.push_back(make_pair(face[i][j],face[i][jp]));
            cout<<face[i][j]<<" "<<face[i][jp]<<endl;
        }
    }
    //清空第一个0，实现的不好待优化。能不能不给初始化的0？
    for(auto it=node2face.begin();it!=node2face.end();++it)
    {
        auto itt=it->begin();
        it->erase(itt);
    }
    for(size_t i=0;i<facelist.size();i++)
    {
        ivector v;
        set_intersection(node2face[facelist[i].first-1].begin(),node2face[facelist[i].first-1].end(),
                node2face[facelist[i].second-1].begin(),node2face[facelist[i].second-1].end(),back_inserter(v));
        if(v.size()==1)
        {
            left_e.push_back(v[0]);
            right_e.push_back(0);
        }

        else if(v.size()==2)
        {
            auto f=find(face[v[0]].begin(),face[v[0]].end(),facelist[i].first);
            auto s=find(face[v[0]].begin(),face[v[0]].end(),facelist[i].second);

            if((f-s)<0)
            {
                 left_e.push_back(v[0]);
                 right_e.push_back(v[1]);
            }
            else
            {
                left_e.push_back(v[1]);
                right_e.push_back(v[0]);
            }

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


    return 0;
}


