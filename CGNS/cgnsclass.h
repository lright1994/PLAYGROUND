#ifndef CGNSCLASS_H
#define CGNSCLASS_H

#include <vector>


using namespace std;

class CgnsClass
{

public:
    CgnsClass(const string& fileName);
    ~ CgnsClass();
    int read_bc_conditions();
    int read_coords();
    int write_bc_coords(const string fileName);
    int write_coords(const string fileName);
private:
    int num_file;
    int num_base;
    int num_zone;

    string fileName;
    vector<vector<int>> bc_pnt_index;
    vector<string> bc_name;
    vector<vector<double>> coords;

    void errChk(const int& ierr, const string& Msg);
    int read_bc_info();

};

#endif // CGNSCLASS_H
