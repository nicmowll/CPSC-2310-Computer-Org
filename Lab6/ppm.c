/*************************
 *Name: Nic Mowll
 *CPSC 2311 004
 *Spring 22
 *nmowll@g.clemson.edu
 *Collaborated with: Clarke Reabel
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
    pixel_t** pixel = allocateMemory(header->width, header->height);
    //nested loop that goes through each row and column and assings the RGB data to the pixels
    for(int row = 0; row < header->height; row++) {
        for(int col = 0; col < header->width; col++) {
            fscanf(file, "%c%c%c", &pixel[row][col].red, &pixel[row][col].green, &pixel[row][col].blue);
        }
    }
    
    return pixel;
}

void imageResize(int orgWidth, int orgHeight, pixel_t** original, int newWidth, int newHeight, pixel_t** newImage) {
    //relative width of new image size compared to original
    double relWidth = (double)orgWidth / (double)newWidth;
    //relative height of new image size compared to original
    double relHeight = (double)orgHeight / (double)newHeight;
    //loops through each row and col of resized 2D array and sets the relative pixels of the original
    for(int row = 0; row < newHeight; row++) {
        for(int col = 0; col < newWidth; col++) {
            //formula to find relative pixels
            int orgRow = (int)floor(0.5 + (relHeight * (double)row));
            int orgCol = (int)floor(0.5 + (relWidth * (double)col));
            newImage[row][col] = original[orgRow][orgCol];
        }
    }
}

void createCollage(header_t* header, pixel_t** pixel, FILE* file) {
    //calls recursive function printCollage with the original file's width and height and pixel array
    collage(header->width, header->height, 0, 0, pixel, pixel);
    //calls writeP6Image after recursive function creates the collage to print it to file.
    writeP6Image(header, pixel, file);
}

void collage(int width, int height, int prevRow, int prevCol, pixel_t** orgPixel, pixel_t** pixel) {
    //SIZE is the proportion of the size the risized image will be (Original size * size constant)
    //MUST be less than 1 and greater than 0
    const double SIZE = 0.6;
    //MINSIZE represents the smallest the middle image can get (height and width in pixels)
    const int MINSIZE = 150;
    
    //base case: we don't want the function to recurse forever, so when width/height < MINSIZE pixels, return
    if(width < MINSIZE || height < MINSIZE) return;

    //calculates the new width/height of the resized image based on SIZE constant
    //it casts the new width/height as an int and makes sure to round correctly
    int newWidth = (int)floor(0.5 + ((double)width * SIZE));
    int newHeight = (int)floor(0.5 + ((double)height * SIZE));

    //creates and allocates a new pixel 2D array with the new width/height
    pixel_t** newPixel = allocateMemory(width, height);
    //calls image resize, seding the current image and its width/height
    //and also the new to be resized image's pixel 2D array and width/height
    imageResize(width, height, pixel, newWidth, newHeight, newPixel);
    //after the image is resized into the newPixel array, we call flipImage on it to flip
    flipImage(newWidth, newHeight, newPixel);

    //calculates the new row and column in which to place the new smaller image in the original
    //Because the image was shrunk to a proportion of its size, the printRow and printCol will be
    //1/2 * (the original height - the new height). Same for width.
    int printRow = prevRow + ((int)floor(0.5 + (0.5 * ((double)height - (double)newHeight))));
    int printCol = prevCol + ((int)floor(0.5 + (0.5 * ((double)width - (double)newWidth))));

    //places the pixels from the new resized flipped image into the middle of the original image
    //using the resized 2D pixel array and printRow and printCol
    for(int row = printRow; row < (newHeight + printRow); row++) {
        for(int col = printCol; col < (newWidth + printCol); col++) {
            orgPixel[row][col] = newPixel[row - printRow][col - printCol];
        }
    }

    //frees memory for previously created resized image if it is not the original image
    if(pixel != orgPixel) {
        for(int row = 0; row < height; row++) {
            free(pixel[row]);
        }
        free(pixel);
    }

    //recurses, sending the newWidth and newHeight, because we want to keep decreasing the size of the image.
    //Also, sends printRow and printCol to keep track of where to place the new image.
    //We keep orgPixel, because that is the original image we want to keep placing resized images on
    //We send newPixel, because we want to further shrink the image that we just shrunk
    collage(newWidth, newHeight, printRow, printCol, orgPixel, newPixel);
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

void flipImage(int width, int height, pixel_t** pixel) {
    //creates new 2D pixel array with allocateMemory() (this is temporary)
    pixel_t** flip = allocateMemory(width, height);
    //nested loops assigns exisiting pixles into the new flipped array positions
    for(int row = 0; row < height; row++) {
        for(int col = 0; col < width; col++) {
            flip[row][col] = pixel[height - row - 1][col];
        }
    }
    //inserts pixels from new flip 2D array back into pixel
    for(int row = 0; row < height; row++) {
        for(int col = 0; col < width; col++) {
            pixel[row][col] = flip[row][col];
        }
    }
    //frees memory for flip 2D array
    for(int row = 0; row < height; row++) {
            free(flip[row]);
    }
    free(flip);
}

pixel_t** allocateMemory(int width, int height) {
    //creates double pointer to 2D array and allocates row of pointers
    pixel_t** pixels = malloc(height * sizeof(pixel_t*));
    //loops through each pointer and allocates the rest of the needed memory to hold the pixels
    for(int i = 0; i < height; i++) {
        pixels[i] = (pixel_t*)malloc(sizeof(pixel_t) * width);
    }
    return pixels;
}

void freeMemory(pixel_t** pixel, header_t* header) {
    //frees memory for 2D array by looping through pointers first
    for(int row = 0; row < header->height; row++) {
            free(pixel[row]);
    }
    //frees double pointer
    free(pixel);
    //frees header pointer
    free(header);
}