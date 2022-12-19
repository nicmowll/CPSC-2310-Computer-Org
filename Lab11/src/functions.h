/*************************
*Nic Mowll
*CPSC 2311 Sp22 Section 004
*nmowll@clemson.edu
*************************/

#ifndef rodriguez
#define rodriguez

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

/*
Header struct holds information from ppm file about the type
of file, the height, width and max value
*/
typedef struct header {
    char magicNum[3];
    int width;
    int height;
    int maxVal;
} header_t;

/*
Pixel struct represents a pixel and holds color values in RGB
(Red, green and blue)
*/
typedef struct pixel {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} pixel_t;

/*
Parameter: File pointer of ppm file
Returns: Header struct with info from the header of the file
Description: Reads in the header from a ppm file and saves it into a header struct
*/
header_t* readHeader(FILE*);

/*
Parameter: File pointer of ppm file
           Header struct pointer with info about ppm file
Returns: Pixel double pointer to 2D array of pixels
Description: Reads the ppm file's pixel info and stores them into a 2D array
*/
pixel_t** readPPM(FILE*, header_t*);

/*
Parameter: Header struct pointer with info about ppm file
           Pixel 2D array holding pixel info
           File pointer of ppm file
Returns: void
Description: Writes the header and pixel info in a file to create a ppm file
*/
void writeP6Image(header_t*, pixel_t**, FILE*);

/*
Parameter: Header struct pointer with info about ppm file
Returns: pixel double pointer to 2D array
Description: allocates of 2D array of type pixel_t based on header info
*/
pixel_t** allocateMemory(header_t*);

/*
Parameter: int for size of side of filter (its a square)
Returns: int double pointer to filter
Description: These allocates memory for a 2d int array of a designated size
*/
int** allocateFilter(int);

/*
Parameter: Header struct pointer with info about ppm file
           Pixel 2D array holding pixel info
           
Returns: void
Description: frees memory for the 2D pixel array and header pointer
*/
void freeMemory(pixel_t**, header_t*);

/*
Parameter: pixel_t** is original pixel 2D array to be filtered
           header_t** holds header information for the pixel 2D array
           int holds the filterType, either 3 or 5
Returns: pixel_t** pixel 2D array which is the filtered image
Description: sharpen takes in a pixel 2D array and filters it by either a 3x3 or 5x5
             sharpen filter
*/
pixel_t** sharpen(pixel_t**, header_t*, int);

/*
Parameter: none
Returns: int** 3x3 filter
Description: creates the 3x3 filter and assigns it with necessary sharpen values
*/
int** create3x3Filter();

/*
Parameter: none
Returns: int** 5x5 filter
Description: creates the 5x5 filter and assigns it with necessary sharpen values
*/
int** create5x5Filter();

/*
Parameter: pixel_t** pixel 2D array holding values to be calculated and filtered
           int** filter array to cause the filtering
           int is size of filter side
           int represents the color, r = 0, g = 1, b = 2, to know which color val to calc
Returns: int is the value that was calculated
Description:
*/
int calculateVal(pixel_t**, int**, int, int);

/*
Parameter: int value that's bounds will be checked
Returns: int value that if put in correct bounds was changed
Description: this function takes in an int and if it is below 0 it makes it zero,
             or above 255 it makes it 255. Otherwise returns same int
*/
int isValid(int);


#endif