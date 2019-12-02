#include "../inc/data_read.hpp"
#include "../inc/computeLUfactors.hpp"
#include <stdio.h> 
#include <fstream>
#include <math.h>
#define epsilon 1e-12


computeLUfactors::computeLUfactors(Vectors_Construct &vectors)
{
    vectors_initial(vectors);
    
    int num_colors = offset_rows_per_color_vec.size() - 1;
    printf("num_colors = %d\n",num_colors);
    for(int i = 0; i <  num_colors; i++)
    {
        int color_offset = offset_rows_per_color_vec[i];
        int num_rows_per_color = offset_rows_per_color_vec[i+1] - color_offset;

        for(int j = 0; j < num_rows_per_color; j++)
        {
            // the row we process
            int aRowId = sorted_rows_vec[color_offset + j];
            //the columns position of this rows in memory
            int aColBeg = row_ptr_vec[aRowId + 0];
            int aColEnd = row_ptr_vec[aRowId + 1];
            int aColSmaller = smaller_color_vec[aRowId];
            // the number of columns
            const int nCols = aColEnd - aColBeg;


            s_keys.resize(nCols);
            for(int step = 0; step < nCols; step ++)
                s_keys[step] = col_ind_vec[aColBeg+step];
            
            // aColIt: the column we process
            for ( int aColIt = aColBeg; aColIt < aColSmaller ; aColIt++)
            {

                // the sub-row ID
                int waRowId = col_ind_vec[aColIt];
                // the sub-row diag in memome
                int aColIdx = diag_vec[waRowId];

                for(int i_sq = 0; i_sq < blockSq; i_sq++)
                    s_C_mtx[i_sq] = value_vec[blockSq * aColIdx+ i_sq];
                for(int i_sq = 0; i_sq < blockSq; i_sq++)
                    s_C_mtx[blockSq + i_sq] = value_vec[blockSq * aColIt+ i_sq];
                for(int i_sq = 0; i_sq < blockSq; i_sq++)
                    s_F_mtx[i_sq] = 0.0;
                for(int i_sq = 0; i_sq < blockSq; i_sq++)
                    temp[i_sq] = 0.0;

                for(int i_dim = 0; i_dim < blockDim; i_dim++)
                    for(int j_dim = 0; j_dim < blockDim; j_dim++)
                    {
                        for(int m = 0; m < blockDim; m++)
                            s_F_mtx[i_dim * blockDim + j_dim] += s_C_mtx[ blockSq + i_dim * blockDim + m] * s_C_mtx[ m * blockDim + j_dim];                  
                    }

                
                for(int i_sq = 0; i_sq < blockSq; i_sq++){
                    value_vec[blockSq * aColIt+ i_sq] = s_F_mtx[i_sq];
                }
                    


                int waColLarger = larger_color_vec[waRowId];
                int waColEnd = row_ptr_vec[waRowId+1];

                for(int waColIt = waColLarger; waColIt < waColEnd; waColIt++)
                {
                    int waColId = col_ind_vec[waColIt];

                    int found_aColIt = 0;
                    for(int i_keys = 0; i_keys < nCols; i_keys++)
                    {
                        if(s_keys[i_keys] == waColId)
                            found_aColIt = i_keys;
                    }
                    
                    if( found_aColIt != 0)
                    {
                        found_aColIt += aColBeg;
      
                        for(int i_sq = 0; i_sq < blockSq; i_sq++)
                            s_C_mtx[i_sq] = value_vec[blockSq * waColIt+ i_sq];
                        for(int i_sq = 0; i_sq < blockSq; i_sq++)
                            temp[i_sq] = 0.0;

                        for(int i_dim = 0; i_dim < blockDim; i_dim++)
                            for(int j_dim = 0; j_dim < blockDim; j_dim++)
                            {
                                for(int m = 0; m < blockDim; m++)
                                temp[i_dim * blockDim + j_dim] += s_F_mtx[ i_dim * blockDim + m] * s_C_mtx[ m * blockDim + j_dim];                  
                            }
                        
                        for(int i_sq = 0; i_sq < blockSq; i_sq++){
                            value_vec[found_aColIt * blockSq + i_sq] -= temp[i_sq];
                        }
                    }
                }
            }


            int offset = blockSq * diag_vec[aRowId];
            for(int i_sq = 0; i_sq < blockSq; i_sq++)
                block[i_sq] = value_vec[offset+i_sq];            
        
                      
 
            computeBlockInverse(offset);
            // for(int i_sq = 0; i_sq < blockSq; i_sq++)
            // if( i == 0)
            //     if(abs(value_vec[offset+ i_sq]-value_color0_vec[offset + i_sq]) > 1e-5)
            //                 printf("%d color aRowId %d (%lf  %lf )wrong!!!!!\n",i,aRowId,value_vec[offset+ i_sq],value_color0_vec[offset + i_sq]);
            // else if(i==1)
            //     if(abs(value_vec[offset+ i_sq]-value_color1_vec[offset + i_sq]) > 1e-5)
            //                 printf("%d color aRowId %d (%lf  %lf )wrong!!!!!\n",i,aRowId,value_vec[offset+ i_sq],value_color0_vec[offset + i_sq]);

                if(j == num_rows_per_color-1 && i == num_colors - 1)
                {
                    ofstream case_file;
                    const char* case_filename_value = "LU_value_lasd.dat";
                    case_file.open(case_filename_value, ios::out);
                    if (case_file.fail()) {
                        printf("The row_ptr.dat is missing\n");
                    }

                    case_file << value_vec.size() << endl;
                    // printf("value.number:%d\n",value_vec.size());
                    for(int k = 0; k < value_vec.size(); k++){
                        case_file << value_vec[k] << endl;
                    }

                    case_file.close();

                }

        }
    }


}

computeLUfactors::~computeLUfactors()
{
}

void computeLUfactors::vectors_initial(Vectors_Construct &vectors)
{
    row_ptr_vec = vectors.Getrow_ptr();
    col_ind_vec = vectors.Getcol_ind();
    diag_vec = vectors.Getdiag();
    smaller_color_vec = vectors.Getsmaller_color();
    larger_color_vec = vectors.Getlarger_color();
    sorted_rows_vec = vectors.Getsorted_rows();
    offset_rows_per_color_vec = vectors.Getoffset_rows_per_color();
    value_vec = vectors.Getvalue();
    value_color0_vec = vectors.Getvaluecolor0();
    value_color1_vec = vectors.Getvaluecolor1();

    blockDim = vectors.GetBlockDim();
    blockSq = blockDim * blockDim;
    s_C_mtx.resize(blockSq * 2);
    s_F_mtx.resize(blockSq);
    temp.resize(blockSq);
    block.resize(blockSq);

}

void computeLUfactors::computeBlockInverse(int offset)

{

    for (int row = 0; row < blockDim; row++)
    {
                            double diag = fabs( block[row * blockDim + row]) > epsilon ? 1.0 / block[row * blockDim + row] : copysign(epsilon,block[row * blockDim + row]);
        for(int i = 0; i < blockDim; i++)
            for(int j = 0; j < blockDim; j++)
            {
                double tmp = 0.0;
                {

                    if ((i == 0) && !(j == row))
                    {
                        tmp = block[row * blockDim + j] * diag;
                        block[row * blockDim + j] = tmp;
                    }
                }
            }
        
        for(int i = 0; i < blockDim; i++)
            for(int j = 0; j < blockDim; j++)
            {
                double tmp = 0.0;
                {

                    if ((i != row) && !(j == row))
                    {
                        tmp = - (block[i * blockDim + row] * block[row * blockDim + j]) + block[i * blockDim + j];
                        block[i * blockDim + j] = tmp; 
                    }
                }
            }
        
        for(int i = 0; i < blockDim; i++)
            for(int j = 0; j < blockDim; j++)
            {
                double tmp = 0.0;
                {            
                    if (i == 0)
                    {
                        tmp = (j == row) ? diag :  (- (block[j * blockDim + row] * diag));
                        block[j * blockDim + row] = tmp;

                    }

                }

            }

    }


        for(int i_sq = 0; i_sq < blockSq; i_sq++)
            value_vec[offset+i_sq] = block[i_sq];    


}

void computeLUfactors::writeResult()
{
    ofstream case_out;

    const char* case_filename_output = "./result/out.dat";

    case_out.open(case_filename_output,ios::out);
    if (case_out.fail()) {
        printf("The out.dat can not open\n");
    }

    case_out << value_vec.size() << endl;

    for(int i = 0; i < value_vec.size(); i++)
        case_out << value_vec[i] << endl;





}