#include <vector>
using namespace std;

class Vectors_Construct
{
public:
    Vectors_Construct();
    ~Vectors_Construct();

    void Vectors_Read();
    void SetBlockDim();

    vector<int> Getrow_ptr();
    vector<int> Getcol_ind();
    vector<int> Getdiag();
    vector<int> Getsmaller_color();
    vector<int> Getlarger_color();
    vector<int> Getsorted_rows();
    vector<int> Getoffset_rows_per_color();
    vector<double> Getvalue();
    vector<double> Getvaluecolor0();
    vector<double> Getvaluecolor1();
    
    int GetBlockDim(){return block_Dim;};


private:
    int block_Dim;
    int size_col_ind,
    size_diag,
    size_smaller_color,
    size_larger_color,
    size_sorted_rows,
    size_offset_rows_per_color,
    size_value;

    vector<int> row_ptr;
    vector<int> col_ind;
    vector<int> diag;
    vector<int> smaller_color;
    vector<int> larger_color;
    vector<int> sorted_rows;
    vector<int> offset_rows_per_color;
    vector<double> value;
    vector<double> value_color0;
    vector<double> value_color1;

};