#include "stdlib.h"
#include "math.h"
#include <vector>
#include <fstream>

using namespace std;
#define Epsilon 1e-2

int main()
{

    const char* case_filename_corelink = "./colorend/LU_corelink.dat";
    const char* case_filename_lasd = "./colorend/LU_lasd.dat";

    ifstream case_file_corelink;
    ifstream case_file_lasd;
    case_file_corelink.open(case_filename_corelink, ios::in);
    case_file_lasd.open(case_filename_lasd, ios::in);
    if (case_file_corelink.fail() || case_file_lasd.fail() ) {
        printf("The data file is missing\n");
        return 1;
    }
    
    int num_size_corelink,num_size_lasd;
    case_file_corelink >> num_size_corelink;
    case_file_lasd >> num_size_lasd;
    if(num_size_lasd != num_size_corelink)
    {
        printf("rows color don't match corelink %d and lasd %d\n",num_size_corelink,num_size_lasd);
        return 1;
    }


    for(int i = 0; i < num_size_corelink; i++){
        double tmp_corelink,tmp_lasd;
        case_file_corelink >> tmp_corelink;
        case_file_lasd >> tmp_lasd;

        if(abs(tmp_corelink - tmp_lasd) > Epsilon)
            printf("the %dth corelink: %lf and lasd:%lf\n",i,tmp_corelink,tmp_lasd);


        
    }

    case_file_corelink.close();
    case_file_lasd.close();




    return 0;
}