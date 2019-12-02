#include "../inc/data_read.hpp"
#include <vector>
#include <fstream>


Vectors_Construct::Vectors_Construct(){
    
    Vectors_Read();
    SetBlockDim();
}


Vectors_Construct::~Vectors_Construct(){
    
}

void Vectors_Construct::Vectors_Read(){
    
    int num_size,num_int;
    double num_double;
    ifstream case_file;

    const char* case_filename_row_ptr = "./inputdata/row_ptr.dat";
    const char* case_filename_col_ind = "./inputdata/col_ind.dat";
    const char* case_filename_diag = "./inputdata/diag.dat";
    const char* case_filename_smaller_color = "./inputdata/smaller_color.dat";
    const char* case_filename_larger_color = "./inputdata/larger_color.dat";
    const char* case_filename_sorted_rows = "./inputdata/sorted_rows.dat";
    const char* case_filename_offset_rows_per_color = "./inputdata/offset_rows_per_color.dat";
    const char* case_filename_value = "./inputdata/value.dat";
    const char* case_filename_value_color0 = "./check/color0/LU_corelink.dat";
    const char* case_filename_value_color1 = "./check/color1/LU_corelink.dat";

    case_file.open(case_filename_row_ptr, ios::in);
    if (case_file.fail()) {
        printf("The row_ptr.dat is missing\n");
    }

    case_file >> num_size;
    for(int i = 0; i < num_size; i++){
        case_file >> num_int;
        row_ptr.push_back(num_int);
    }

    case_file.close();


    case_file.open(case_filename_col_ind, ios::in);
    if (case_file.fail()) {
        printf("The col_ind.dat is missing\n");
    }

    case_file >> num_size;
    for(int i = 0; i < num_size; i++){
        case_file >> num_int;
        col_ind.push_back(num_int);
    }

    case_file.close();

    
    case_file.open(case_filename_diag, ios::in);
    if (case_file.fail()) {
        printf("The diag.dat is missing\n");
    }

    case_file >> num_size;
    for(int i = 0; i < num_size; i++){
        case_file >> num_int;
        diag.push_back(num_int);
    }

    case_file.close();



    case_file.open(case_filename_smaller_color, ios::in);
    if (case_file.fail()) {
        printf("The smaller_color.dat is missing\n");
    }

    case_file >> num_size;
    for(int i = 0; i < num_size; i++){
        case_file >> num_int;
        smaller_color.push_back(num_int);
    }

    case_file.close();

    case_file.open(case_filename_larger_color, ios::in);
    if (case_file.fail()) {
        printf("The larger_color.dat is missing\n");
    }

    case_file >> num_size;
    for(int i = 0; i < num_size; i++){
        case_file >> num_int;
        larger_color.push_back(num_int);
    }

    case_file.close();


    case_file.open(case_filename_sorted_rows, ios::in);
    if (case_file.fail()) {
        printf("The sorted_rows.dat is missing\n");
    }

    case_file >> num_size;
    for(int i = 0; i < num_size; i++){
        case_file >> num_int;
        sorted_rows.push_back(num_int);
    }

    case_file.close();

    
    case_file.open(case_filename_offset_rows_per_color, ios::in);
    if (case_file.fail()) {
        printf("The offset_rows_per_color.dat is missing\n");
    }

    case_file >> num_size;
    for(int i = 0; i < num_size; i++){
        case_file >> num_int;
        offset_rows_per_color.push_back(num_int);
    }

    case_file.close();


    case_file.open(case_filename_value, ios::in);
    if (case_file.fail()) {
        printf("The value.dat is missing\n");
    }

    case_file >> num_size;
    for(int i = 0; i < num_size; i++){
        case_file >> num_double;
        value.push_back(num_double);
    }

    case_file.close();

    case_file.open(case_filename_value_color0, ios::in);
    if (case_file.fail()) {
        printf("The value.dat is missing\n");
    }

    case_file >> num_size;
    for(int i = 0; i < num_size; i++){
        case_file >> num_double;
        value_color0.push_back(num_double);
    }

    case_file.close();

    case_file.open(case_filename_value_color1, ios::in);
    if (case_file.fail()) {
        printf("The value.dat is missing\n");
    }

    case_file >> num_size;
    for(int i = 0; i < num_size; i++){
        case_file >> num_double;
        value_color1.push_back(num_double);
    }

    case_file.close();

}

void Vectors_Construct::SetBlockDim(){
    
    int temp = value.size() / col_ind.size();
    int temp_mod = value.size() % col_ind.size();

    if( temp_mod != 0 )
        printf("Error: the calue and colind size don't match\n");

    if( temp == 9 )
        block_Dim = 3;
    else if( temp == 16 )
        block_Dim = 4;
    else if( temp == 25 )
        block_Dim = 5;
    else
        printf("Error: the blockDim larger than 5\n");
}

vector<int> Vectors_Construct::Getrow_ptr(){return row_ptr;};
vector<int> Vectors_Construct::Getcol_ind(){return col_ind;};
vector<int> Vectors_Construct::Getdiag(){return diag;};
vector<int> Vectors_Construct::Getsmaller_color(){return smaller_color;};
vector<int> Vectors_Construct::Getlarger_color(){return larger_color;};
vector<int> Vectors_Construct::Getsorted_rows(){return sorted_rows;};
vector<int> Vectors_Construct::Getoffset_rows_per_color(){return offset_rows_per_color;};
vector<double> Vectors_Construct::Getvalue(){return value;};
vector<double> Vectors_Construct::Getvaluecolor0(){return value_color0;};
vector<double> Vectors_Construct::Getvaluecolor1(){return value_color1;};
