#ifndef READ_CFD_POST_H
#define READ_CFD_POST_H


#include "define.h"

void split_string(string& chars,vector<string>&strvec)
{
    for(int i=0; i<chars.size(); i++) if(chars[i] == ',') chars[i] = ' ';
    strvec.clear();
    istringstream is(chars);
    string  tmp;
    while(is>>tmp)
    {
        strvec.push_back(tmp);
    }
}




void read_CFD_Post(map<string, string>& commads, CFD_Post &cfdpdata)
{
    std::string fileName = commads["-cfd"];
    printf("\n\n\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
    printf("\nReading CFD-Post from file '%s'", fileName.c_str());

    //////////////////////////////////////////////////////////////////////////
    // ��ȡģ��

    ifstream infile(fileName.c_str());
    //if(!infile) assert(0);
    string str_tmp;
    svector strs_tmp;
    int count_face_Node=0, count_face_f2n=0, count_face_p=0, count_face_cp=0,count_face_st=0;

    while(!infile.eof()){

        getline(infile,str_tmp);
        split_string(str_tmp,strs_tmp);
        if(strs_tmp.size()==0)continue;

        if(strs_tmp.size()>1 && strs_tmp[1] == "\"Node"){

                CFD_Post_Face aface;
                getline(infile, str_tmp);
                int nnodes;
                sscanf(str_tmp.c_str(), "(%*d (%*d %*d %d %*d)", &nnodes);
                printf("\n    Node:  number of node : %d", nnodes);

                for(int f=0; f<nnodes; f++){

                        getline(infile, str_tmp);
                        for(int i=0; i<str_tmp.size(); i++) if(str_tmp[i]=='('||str_tmp[i]==')') str_tmp[i] =' ';
                        split_string(str_tmp, strs_tmp);
                        assert(strs_tmp.size() == 3);
                        aface.x.push_back(atof(strs_tmp[0].c_str()));
                        aface.y.push_back(atof(strs_tmp[1].c_str()));
                        aface.z.push_back(atof(strs_tmp[2].c_str()));

                 }

                count_face_Node++;
                cfdpdata.pface.push_back(aface);
        }

        if(strs_tmp.size()>1 && strs_tmp[1] == "\"Element"){

            getline(infile, str_tmp);
            int nfaces;
            sscanf(str_tmp.c_str(), "(%*d (%*d %*d %d %*d)", &nfaces);
            printf("\n    Element:  number of face : %d", nfaces);

            iivector &face2node = cfdpdata.pface[count_face_f2n].face2node;
            for(int f=0; f<nfaces; f++){

                getline(infile, str_tmp);
                for(int i=0; i<str_tmp.size(); i++) if(str_tmp[i]=='('||str_tmp[i]==')') str_tmp[i] =' ';
                split_string(str_tmp, strs_tmp);

                ivector fnode;
                for(int i=1; i<strs_tmp.size(); i++) fnode.push_back(atoi(strs_tmp[i].c_str())-1);//ע��CFD-POST�±��1��ʼ��

                face2node.push_back(fnode);
            }

            cfdpdata.pface[count_face_f2n].fn.resize(nfaces);
            count_face_f2n++;

        }

        if(strs_tmp.size()>1 && strs_tmp[1] == "\"absolute-pressure"){

            //(612 (4 10 1 0 1 1 401)
            getline(infile, str_tmp);

            int nnodes;
            sscanf(str_tmp.c_str(), "(%*d (%*d %*d %*d %*d %*d %*d %d)", &nnodes);
            printf("\n    absolute-pressure:  number of point : %d", nnodes);

            rvector &p = cfdpdata.pface[count_face_p].p;
            for(int f=0; f<nnodes; f++){

                getline(infile, str_tmp);
                for(int i=0; i<str_tmp.size(); i++) if(str_tmp[i]=='('||str_tmp[i]==')') str_tmp[i] =' ';
                split_string(str_tmp, strs_tmp);
                assert(strs_tmp.size() == 1);

                p.push_back(atof(strs_tmp[0].c_str()));
            }

            assert(p.size() == cfdpdata.pface[count_face_p].x.size());

            count_face_p++;
        }

        if(strs_tmp.size()>1 && strs_tmp[1] == "\"pressure-coefficient"){

            //(612 (2 2 1 0 1 1 12366)
            getline(infile, str_tmp);

            int nnodes;
            sscanf(str_tmp.c_str(), "(%*d (%*d %*d %*d %*d %*d %*d %d)", &nnodes);
            printf("\n    pressure-coefficient:  number of point : %d", nnodes);

            rvector &cp = cfdpdata.pface[count_face_cp].cp;
            for(int f=0; f<nnodes; f++){

                getline(infile, str_tmp);
                for(int i=0; i<str_tmp.size(); i++) if(str_tmp[i]=='('||str_tmp[i]==')') str_tmp[i] =' ';
                split_string(str_tmp, strs_tmp);
                assert(strs_tmp.size() == 1);

                cp.push_back(atof(strs_tmp[0].c_str()));
            }

            assert(cp.size() == cfdpdata.pface[count_face_cp].x.size());

            count_face_cp++;
        }

        if(strs_tmp.size()>1 && strs_tmp[1] == "\"temperature"){

            int size = strs_tmp.size();
            if(strs_tmp[size-1] == "nnodes:\")"){

                getline(infile, str_tmp);
                int nnodes;
                sscanf(str_tmp.c_str(), "(%*d (%*d %*d %*d %*d %*d %*d %d)", &nnodes);
                printf("\n    static temperature:  number of point : %d", nnodes);

                rvector &st = cfdpdata.pface[count_face_st].st;
                for(int f=0; f<nnodes; f++){

                    getline(infile, str_tmp);
                    for(int i=0; i<str_tmp.size(); i++) if(str_tmp[i]=='('||str_tmp[i]==')') str_tmp[i] =' ';
                    split_string(str_tmp, strs_tmp);
                    assert(strs_tmp.size() == 1);
                    st.push_back(atof(strs_tmp[0].c_str()));

                }

                assert(st.size() == cfdpdata.pface[count_face_st].x.size());

                count_face_st++;
            }

        }

    }

    infile.close();

    cout<<"\n>>>>>>>>>>>>>>>>>read successfully!"<<">>>>>>>>>>>>>>>>>"<<endl;

}






#endif // READ_CFD_POST_H
