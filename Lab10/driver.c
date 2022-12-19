/*************************
*Nic Mowll
*CPSC 2311 Sp22 Section 004
*nmowll@g.clemson.edu
*************************/

#include "src/functions.h"

int main(int argc, char* argv[]) {
    assert(argc == 4 && "Must have 4 command line arguments");

    /*necessary to get the size of the array, 
    because it cannot be accessed after dynamically allocated*/
    matrixSize_t* size = getMatrixSize(argv[1]);
    
    //call to read in original input matrix
    MATRIX orginalMTX = readInput(argv[1], size);
    
    //call sharpen with filter width of 3 to apply filter to matrix
    MATRIX new3x3 = sharpen(orginalMTX, size, 3);
    //prints filtered matrix to 3rd command argument file
    printToFile(argv[2], new3x3, size);
    
    //call sharpen with filter width of 5 to apply filter to matrix
    MATRIX new5x5 = sharpen(orginalMTX, size, 5);
    //prints filtered matrix to 3rd command argument file
    printToFile(argv[3], new5x5, size);
    
    //frees memory
    freeMemory(orginalMTX, size);
    freeMemory(new3x3, size);
    freeMemory(new5x5, size);
    free(size);

    return 0;
}
