#include "../inc/LUDecomposition.hpp"


int main(){

    Vectors_Construct Vectors_AmgX;

    computeLUfactors LUfactor(Vectors_AmgX);

    LUfactor.writeResult();








    return 1;
}