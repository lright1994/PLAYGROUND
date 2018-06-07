#include <define.h>

void CFD_Post_Face::get_neighbor()
{
    int size_node=this->x.size();

    iivector node2face(size_node, ivector(1, 0));//ÿ���ڵ��Ӧ��element
    iivector &element=this->face2node;
    vector<pair<int,int>> &point_pair=this->facelist;
    ivector left_e;
    ivector right_e;

    for(size_t i=0;i<element.size();++i)
    {
        for(size_t j=0;j<element[i].size();++j)
        {
            // ����ڵ�����Ԫ�Ķ�Ӧ��ϵ
            node2face[element[i][j]].push_back(i);
            //����point_pair
            int jp=(j==element[i].size()-1)?0:j+1;
            point_pair.push_back(make_pair(element[i][j],element[i][jp]));
        }
    }
    //�����һ����
    for(auto it=node2face.begin();it!=node2face.end();++it)
    {
        auto itt=it->begin();
        it->erase(itt);
    }


    //��ȡ������Ԫ �˴�Ϊ�˷�������±��1��ʼ���ش�ע��

    for(size_t i=0;i<element.size();++i)
    {
        for(size_t j=0;j<element[i].size();j++)
        {
            left_e.push_back(i);
        }
    }
    int tmp=0;
    for(size_t i=0;i<point_pair.size();i++)
    {
        ivector v;
        set_intersection(node2face[point_pair[i].first].begin(),node2face[point_pair[i].first].end(),
                node2face[point_pair[i].second].begin(),node2face[point_pair[i].second].end(),back_inserter(v));
        if(v.size()==1)
        {
            right_e.push_back(-1);
            ++tmp;
            //cout<<"#error :"<<point_pair[i].first+1<<"  "<<point_pair[i].second+1<<endl;
            //cout<<"up to "<<tmp<<endl;
        }
        else if(v.size()==2)
        {
            int right=(v[0]==left_e[i])?v[1]:v[0];
            right_e.push_back(right);
            if(left_e[i]!=v[0]&&left_e[i]!=v[1])
            {
                cout<<"#error 2 ";
            }
        }
        else
        {

        }
    }

    this->neighbor.push_back(left_e);
    this->neighbor.push_back(right_e);

}
