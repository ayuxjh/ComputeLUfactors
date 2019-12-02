class computeLUfactors
{
private:
    vector<int> row_ptr_vec;
    vector<int> col_ind_vec;
    vector<int> diag_vec;
    vector<int> smaller_color_vec;
    vector<int> larger_color_vec;
    vector<int> sorted_rows_vec;
    vector<int> offset_rows_per_color_vec;
    vector<double> value_vec;
    vector<double> value_color0_vec;
    vector<double> value_color1_vec;

    vector<int> s_keys;
    vector<double> s_C_mtx;
    vector<double> s_F_mtx;
    vector<double> temp;
    vector<double> block;


    int blockDim,blockSq;

public:
    computeLUfactors(Vectors_Construct &vectors);
    ~computeLUfactors();

    void vectors_initial(Vectors_Construct &Vectors);
    
    void computeBlockInverse(int offset);
    void writeResult();

};

