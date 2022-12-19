/*************************
 *Name: Nic Mowll
 *CPSC 2311 004
 *Spring 22
 *nmowll@g.clemson.edu
 *************************/

//header guard
#ifndef rodriguez
#define rodriguez

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

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
           Pixel 2D array holding pixel info
           File pointer of ppm file
Returns: void
Description: Creates a gray scale version of a ppm image and writes it to designated file
*/
void grayScaleImage(header_t*, pixel_t**, FILE*);

/*
Parameter: Header struct pointer with info about ppm file
           Pixel 2D array holding pixel info
           File pointer of ppm file
Returns: void
Description: Creates a vertically flipped version of a ppm image and writes it to the file
*/
void flipImage(header_t*, pixel_t**, FILE*);

/*
Parameter: Header struct pointer with info about ppm file
Returns: pixel double pointer to 2D array
Description: allocates of 2D array of type pixel_t based on header info
*/
pixel_t** allocateMemory(header_t*);

/*
Parameter: Header struct pointer with info about ppm file
           Pixel 2D array holding pixel info
           
Returns: void
Description: frees memory for the 2D pixel array and header pointer
*/
void freeMemory(pixel_t**, header_t*);

#endif /* rodriguez */