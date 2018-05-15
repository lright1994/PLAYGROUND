#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <memory>


using std::getline;
using std::endl;
using std::cout;
using std::vector;
using std::string;

inline vector<string> split_string(const string& inputStr){
    vector<string> stringsV;
    std::istringstream  iStr(inputStr);
    string sTem;
    while(getline(iStr,sTem,';')){
        stringsV.push_back(sTem);
    }

    return stringsV;
}

template <typename outType, typename inType>
inline outType convert_type(const inType& in){
    std::stringstream sStream;
    sStream<<inType;
    outType result;
    sStream>>result;
    return std::move(result);
}

std::unique_ptr<int> test;

int main()
{
    auto testStr="Hello;world;!!;test;";
    for(auto outputS:split_string(testStr)){
        cout<<outputS<<endl;
    }
    auto testInt=10;
    cout<<typeid(convert_type<double>(testInt)).name()<<endl;
    testRV=convert_type<double>(2018);

}
