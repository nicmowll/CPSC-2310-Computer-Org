/*************************
*Nic Mowll
*CPSC 2311 Sp22 Section 004
*nmowll@g.clemson.edu
*************************/

#ifndef rodriguez
#define rodriguez

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

//alias for int** 
typedef int** MATRIX;

/*matrixSize holds the size of a matrix
    rows: number of rows
    cols: number of cols
*/
typedef struct matrixSize {
    int rows;
    int cols;
} matrixSize_t;

/*Parameters:
    char* fileName: string, name of file that will be read
    matrixSize_t* size: pointer to size struct holding size of matrix
  Returns: 
    MATRIX: Matrix of ints from input file
  Description: readInput reads int information from an input file and 
               stores them into a 2D array
*/
MATRIX readInput(char*, matrixSize_t*);

/*Parameters:
    MATRIX original: original matrix from input
    matrixSize_t* size: size of original matrix
    int filterType: width of sharpen filter (must be 3 or 5)
  Returns:
    MATRIX: filtered new matrix
  Description: sharpen takes in an original matrix and filter width,
               and filters an image into a new array 
*/
MATRIX sharpen(MATRIX, matrixSize_t*, int);

/*Parameters:
    matrixSize_t* filterSize: size of filter
  Returns:
    MATRIX: matrix filter
  Description: create3x3Filter creates a 3x3 grid and fills it in 
               with filter values
*/
MATRIX create3x3Filter(matrixSize_t*);

/*Parameters:
    matrixSize_t* filterSize: size of filter
  Returns:
    MATRIX: matrix filter
  Description: create5x5Filter creates a 5x5 grid and fills it in
               with filter values
*/
MATRIX create5x5Filter(matrixSize_t*);

/*Parameters:
    MATRIX arr: piece of original array that is same size as filter
    MATRIX filter: filter matrix
    matrixSize_t* size: size of filter matrix
  Returns:
    int: value that is calculated from filtering one int
  Description: calculateVal takes in a filter and a smaller chunk of original array
               to calculate the filtered value that will then be put into new array
*/
int calculateVal(MATRIX, MATRIX, matrixSize_t*);

/*Parameters:
    int val: val to be checked
  Returns:
    int: returns value, unless it was out of bounds, then closest bound
  Description: isValid checks to see if an int is withing 0 to 255, and if it is out
               of those bounds, then it returns the closest bound
*/
int isValid(int);

/*Parameters:
    MATRIX arr: matrix to be printed 
    matrixSize_t* size: size of matrix
  Returns:
    void
  Description: print prints a matrix out onto the console
*/
void print(MATRIX, matrixSize_t*);

/*Parameters:
    char* fileName: name of file to print to
    MATRIX arr: array to be printed to file
    matrixSize_t* size: size of matrix
  Returns:
    void
  Description: printToFile prints a matrix out to a file
*/
void printToFile(char*, MATRIX, matrixSize_t*);

/*Parameters:
    matrixSize_t*: size of matrix to be allocated
  Returns:
    MATRIX: returns pointer to allocated matrix
  Description: allocateMemory allocates memory for a matrix of certain size
*/
MATRIX allocateMemory(matrixSize_t*);

/*Parameters:
    MATRIX arr: matrix to be freed
    matrixSize_t*: size of matrix to be freed
  Returns:
    void
  Description: freeMemory frees memory for a 2D matrix
*/
void freeMemory(MATRIX, matrixSize_t*);

/*Parameters:
    char* fileName: name of file to read
  Returns:
    matrixSize_t*: pointer to size struct of matrix
  Description: getMatrixSize reads in num of rows and cols from input file and 
               creates size struct
*/
matrixSize_t* getMatrixSize(char*);

#endif