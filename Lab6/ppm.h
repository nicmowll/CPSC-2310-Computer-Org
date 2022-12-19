/*************************
 *Name: Nic Mowll
 *CPSC 2311 004
 *Spring 22
 *nmowll@g.clemson.edu
 *Collaborated with: Clarke Reabel
 *************************/

//header guard
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
Parameter: int: width of orignal image we will resize
           int: height of original image we will resize
           pixel_t**: original image pixels in 2D array
           int: width of new image size
           int: height of new image size
           pixel_t**: 2D array with new width and height that new pixels will go in
Returns: void
Description: Takes in a 2D pixel array and resizes it to a new array with the given width and height
*/
void imageResize(int, int, pixel_t**, int, int, pixel_t**);

/*
Parameter: header_t*: header of the original pixel image used to print header for collage
           pixel_t**: original pixel 2D array image 
           FILE*: file pointer that the collage will be printed to
Return: void
Description: Create collage calls the collage() recursive function andthen printP6Image to print 
             new collage to the file
*/
void createCollage(header_t*, pixel_t**, FILE*);

/*
Parameter: int: width of the current image being passed
           int: height of the current image being passed
           int: the row that the previous recursion printed the resized image on
           int: the col that the previous recursion printed the resized image on
           pixel_t**: the original 2D image that the full collage goes on
           pixel_t**: 2D array image that was previously resized in last recursion
Return: void
Description: collage is a recursive function, where an image is passed in and then it resizes it,
             places it in the middle of the original image and then recurses by passing the newly resized
             image back into the function and the width, height, and row and column that that image was
             printed on. These parameters are all necessary in keeping track of what size to make each image
             and where to place it on the 2D array.
*/
void collage(int, int, int, int, pixel_t**, pixel_t**);

/*
Parameter: int: width of image to be flipped
           int: height of image to be flipped
           pixel_t**: 2D array holding pixel info
Returns: void
Description: Creates a vertically flipped version of a ppm image in the pixel 2D array
*/
void flipImage(int, int, pixel_t**);

/*
Parameter: int: width of 2D array
           int: height of 2D array
Returns: pixel double pointer to 2D array
Description: allocates of 2D array of type pixel_t based on width and height info
*/
pixel_t** allocateMemory(int, int);

/*
Parameter: Header struct pointer with info about ppm file
           Pixel 2D array holding pixel info
           
Returns: void
Description: frees memory for the 2D pixel array and header pointer
*/
void freeMemory(pixel_t**, header_t*);

#endif /* rodriguez */