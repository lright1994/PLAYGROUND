#include <define.h>

void get_neighbor(CFD_Post_Face &cfdface)
{
    int size_node=cfdface.x.size();
    int size_element=cfdface.face2node.size();


    cout<<"Get the neighbor"<<endl;
    cout<<"up to "<<size_node<<"nodes"<<endl;//��Ӧtecplot�е�Nodes
    cout<<"up to "<<size_element<<"faces"<<endl;//��Ӧtecplot�е�Elements����

    iivector node2face(size_node, ivector(1, 0));//ÿ���ڵ����涼�и�0
    iivector &face=cfdface.face2node;

    for(size_t i=0;i<face.size();i++)
    {
        for(size_t j=0;j<face[i].size();j++)
        {
            node2face[face[i][j]-1].push_back(i);//teplot�нڵ��1��ʼ
        }
    }
    for(auto it=face.begin();it!=face.end();++it)
    {

    }

}
