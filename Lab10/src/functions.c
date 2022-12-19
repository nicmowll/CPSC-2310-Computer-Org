/*************************
*Nic Mowll
*CPSC 2311 Sp22 Section 004
*nmowll@g.clemson.edu
*************************/

#include "functions.h"

MATRIX readInput(char* fileName, matrixSize_t* size)
{
    //creates file pointer
    FILE * in = fopen(fileName, "r");
    //makes sure file was opened correctly
    assert(in != NULL);

    //allocates memory for array of proper size
    MATRIX arr = allocateMemory(size);

    //scans in each int value into arr
    for(int i = 0; i < 3; i++) {
        fgetc(in);
    }
    for(int r = 0; r < size->rows; r++) {
        fscanf(in, "\n");
        for(int c = 0; c < size->cols; c++) {
            fscanf(in, "%d ", &arr[r][c]);
        }
    }

    //closes file and returns arr
    fclose(in);
    return arr;
}

matrixSize_t* getMatrixSize(char* fileName) {
    //creates file pointer
    FILE * in = fopen(fileName, "r");
    //makes sure file was opened correctly
    assert(in != NULL);

    //creates size struct and scans in num rows and cols
    matrixSize_t* size = malloc(sizeof(size_t));
    fscanf(in, "%d %d", &size->rows, &size->cols);

    //closes file and returns
    fclose(in);
    return size;
}

MATRIX sharpen(MATRIX original, matrixSize_t* size, int filterType)
{
    assert(filterType == 3 ^ filterType == 5);

    //indent keeps track of how far into the matrix to apply filter
    int indent;
    //2D array that holds filter values
    MATRIX filter=NULL;
    //creates size struct for the filter size
    matrixSize_t* filterSize = malloc(sizeof(matrixSize_t));
    
    //depending on if the filter is of width 3 or 5, sets the indent and filter size
    if(filterType == 3) {
        indent = 1;
        filterSize->rows = 3;
        filterSize->cols = 3;
        assert(filterSize != NULL);
        //calls function to fill the 3x3 filter
        filter = create3x3Filter(filterSize);
    }
    else if(filterType == 5) {
        indent = 2;
        filterSize->rows = 5;
        filterSize->cols = 5;
        assert(filterSize != NULL);
        //calls function to fill the 5x5 filter
        filter = create5x5Filter(filterSize);
    }

    //makes sure filter was successfully opened
    assert(filter != NULL);

    //new filtered matrix
    MATRIX new = allocateMemory(size);
    //temp matrix that is the same size as the filter
    MATRIX temp = allocateMemory(filterSize);

    //copies original matrix to new
    for(int r = 0; r < size->rows; r++) {
        for(int c = 0; c < size->cols; c++) {
            new[r][c] = original[r][c];
        }
    }

    /*loops through each of the needed to be filtered ints in new matrix, then sets 
    the temporary matrix to the filter size around the int and calls function to calculate
    the value*/
    for(int r = 0 + indent; r < size->rows - indent; r++) {
        for(int c = 0 + indent; c < size->cols - indent; c++) {
            for(int tempR = 0; tempR < filterSize->rows; tempR++) {
                for(int tempC = 0; tempC < filterSize->cols; tempC++) {
                    temp[tempR][tempC] = original[r - indent + tempR][c - indent + tempC];
                }
            }
            //sets the int to new value
            new[r][c] = calculateVal(temp, filter, filterSize);
        }
    }

    //frees up memory and returns new matrix
    for(int i = 0; i < filterSize->rows; i++) {
        free(temp[i]);
    }
    free(temp);
    freeMemory(filter, filterSize);
    free(filterSize);
    return new;
}

MATRIX create3x3Filter(matrixSize_t* filterSize) {
    //creates 3x3 filter and fills it with necessary values
    MATRIX filter = allocateMemory(filterSize);
    filter[0][0] = 0;
    filter[0][1] = -1;
    filter[0][2] = 0;
    filter[1][0] = -1;
    filter[1][1] = 5;
    filter[1][2] = -1;
    filter[2][0] = 0;
    filter[2][1] = -1;
    filter[2][2] = 0;

    return filter;
}

MATRIX create5x5Filter(matrixSize_t* filterSize) {
    //creates 5x5 filter and fills it with necessary values
    MATRIX filter = allocateMemory(filterSize);
    for(int r = 0; r < 5; r++) {
        for(int c = 0; c < 5; c++) {
            filter[r][c] = 0;
        }
    }
    for(int c = 0; c < 5; c++) {
        filter[2][c] = -1;
    }
    for(int r = 0; r < 5; r++) {
        filter[r][2] = -1;
    }
    filter[2][2] = 9;

    return filter;
}

int calculateVal(MATRIX arr, MATRIX filter, matrixSize_t* size)
{
    //sum keeps track of the addition of all multiplied values
    int sum = 0;
    //loops through filter and arr, and calculates value
    for(int r = 0; r < size->rows; r++) {
        for(int c = 0; c < size->cols; c++) {
            sum += (arr[r][c] * filter[r][c]);
        }
    }

    //returns sum as a parameter for isValid function
    return isValid(sum);
}

int isValid(int val)
{
    //makes sure the int is 0 < x < 255, and if it exceeds bounds it returns nearest bound
    if(val < 0) {
        return 0;
    }
    else if(val > 255) {
        return 255;
    }
    else return val;
}

void print(MATRIX arr, matrixSize_t* size)
{
    //prints matrix to console
    for(int r = 0; r < size->rows; r++) {
        printf("\n");
        for(int c = 0; c < size->cols; c++) {
            printf("%d ", arr[r][c]);
        }
    }
}

void printToFile(char* fileName, MATRIX arr, matrixSize_t* size) {
    //opens file pointer
    FILE* out = fopen(fileName, "w");
    //makes sure it was opened correctly
    assert(out != NULL);

    //prints matrix to file
    for(int r = 0; r < size->rows; r++) {
        if(r != 0) {fprintf(out, "\n");}
        for(int c = 0; c < size->cols; c++) {
            fprintf(out, "%d ", arr[r][c]);
        }
    }

    //closes file
    fclose(out);
}

MATRIX allocateMemory(matrixSize_t* size)
{
    //creates arr pointer and allocates memory of correct size for Matrix
    MATRIX arr = malloc(size->rows * sizeof(int*));

    for(int i = 0; i < size->rows; i++) {
        arr[i] = malloc(size->cols * sizeof(int));
    }

    return arr;
}

void freeMemory(MATRIX arr, matrixSize_t* size)
{
    //frees memory for matrix
    for(int i = 0; i < size->rows; i++) {
        free(arr[i]);
    }
    free(arr);

    return;
}