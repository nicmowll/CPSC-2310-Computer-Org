/*************************
 *Name: Nic Mowll
 *CPSC 2311 004
 *Spring 22
 *nmowll@g.clemson.edu
 *************************/

#include "ppm.h"

header_t* readHeader(FILE* file) {
    //allocates memory to header
    header_t * header = malloc(sizeof(header_t));
    //scans in data from ppm file to header
    fscanf(file, "%s", header->magicNum);
    fscanf(file, "\n%d %d %d\n", &header->width, &header->height, &header->maxVal);
    return header;
}
pixel_t** readPPM(FILE* file, header_t* header) {
    //creates pixel 2D array by calling allocateMemory()
    pixel_t** pixel = allocateMemory(header);
    //nested loop that goes through each row and column and assings the RGB data to the pixels
    for(int row = 0; row < header->height; row++) {
        for(int col = 0; col < header->width; col++) {
            fscanf(file, "%c%c%c", &pixel[row][col].red, &pixel[row][col].green, &pixel[row][col].blue);
        }
    }
    
    return pixel;
}
void writeP6Image(header_t* header, pixel_t** pixel, FILE* file) {
    //prints header info to file
    fprintf(file, "%s\n", header->magicNum);
    fprintf(file, "%d %d %d\n", header->width, header->height, header->maxVal);
    //prints pixel data to file
    for(int row = 0; row < header->height; row++) {
        for(int col = 0; col < header->width; col++) {
            fprintf(file, "%c%c%c", pixel[row][col].red, pixel[row][col].green, pixel[row][col].blue);
        }
    }
}
void grayScaleImage(header_t* header, pixel_t** pixel, FILE* file) {
    //pixelVal holds value for gray pixel
    unsigned char pixelVal;
    //prints header info to file
    fprintf(file, "P5\n");
    fprintf(file, "%d %d %d\n", header->width, header->height, header->maxVal);
    //nested loop converts RGB data to gray color value and prints pixel data to file
    for(int row = 0; row < header->height; row++) {
        for(int col = 0; col < header->width; col++) {
            pixelVal = (.299*pixel[row][col].red) + (.587*pixel[row][col].green) + (.114*pixel[row][col].blue);
            fprintf(file, "%c", pixelVal);
        }
    }
}
void flipImage(header_t* header, pixel_t** pixel, FILE* file) {
    //creates new 2D pixel array with allocateMemory()
    pixel_t** flip = allocateMemory(header);
    //nested loops assigns exisiting pixles into the new flipped array positions
    for(int row = 0; row < header->height; row++) {
        for(int col = 0; col < header->width; col++) {
            flip[row][col] = pixel[header->height - row - 1][col];
        }
    }
    //writes image to file
    writeP6Image(header, flip, file);
    
    //frees memory for flip 2D array
    for(int row = 0; row < header->width; row++) {
            free(flip[row]);
    }
    free(flip);
}
pixel_t** allocateMemory(header_t* header) {
    //creates double pointer to 2D array and allocates row of pointers
    pixel_t** pixels = malloc(header->height * sizeof(pixel_t*));
    //loops through each pointer and allocates the rest of the needed memory to hold the pixels
    for(int i = 0; i < header->height; i++) {
        pixels[i] = (pixel_t*)malloc(sizeof(pixel_t) * header->width);
    }
    return pixels;
}
void freeMemory(pixel_t** pixel, header_t* header) {
    //frees memory for 2D array by looping through pointers first
    for(int row = 0; row < header->width; row++) {
            free(pixel[row]);
    }
    //frees double pointer
    free(pixel);
    //frees header pointer
    free(header);
}