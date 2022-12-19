/*************************
*Nic Mowll
*CPSC 2311 Sp22 Section 004
*nmowll@clemson.edu
*************************/

#include "functions.h"

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

pixel_t** sharpen(pixel_t** pixels, header_t* header, int filterType) {
    assert((filterType == 3) ^ (filterType == 5));

    //indent keeps track of how far into the matrix to apply filter
    int indent;
    //2D array that holds filter values
    int** filter = NULL;

    if(filterType == 3) {
        indent = 1;
        //calls function to fill the 3x3 filter
        filter = create3x3Filter(3);
    }
    else if(filterType == 5) {
        indent = 2;
        //calls function to fill the 5x5 filter
        filter = create5x5Filter(5);
    }

    //makes sure filter was successfully filled
    assert(filter != NULL);

    //new filtered pixel array
    pixel_t** new = allocateMemory(header);
    //temp pixel array that is the same size as the filter
    pixel_t** temp = malloc(filterType * sizeof(pixel_t*));
    for(int i = 0; i < filterType; i++) {
        temp[i] = (pixel_t*)malloc(filterType * sizeof(pixel_t));
    }

    //copies original pixels to new
    for(int r = 0; r < header->height; r++) {
        for(int c = 0; c < header->width; c++) {
            new[r][c] = pixels[r][c];
        }
    }

    /*loops through each of the needed to be filtered pixels, then sets 
    the temporary pixels to the filter size around the middle pixel and calls function to calculate
    the value*/
    //loops 3 times for each color
    for(int i = 0; i < 3; i++) {
        for(int r = 0 + indent; r < header->height - indent; r++) {
            for(int c = 0 + indent; c < header->width - indent; c++) {
                for(int tempR = 0; tempR < filterType; tempR++) {
                    for(int tempC = 0; tempC < filterType; tempC++) {
                        temp[tempR][tempC] = pixels[r - indent + tempR][c - indent + tempC];
                    }
                }
                //sets the pixel color val to new value depending on color
                if(i == 0) {
                    new[r][c].red = calculateVal(temp, filter, filterType, 0);
                }
                else if(i == 1) {
                    new[r][c].green = calculateVal(temp, filter, filterType, 1);
                }
                else if(i == 2) {
                    new[r][c].blue = calculateVal(temp, filter, filterType, 2);
                }
            }
        }
    }

    //frees up memory and returns new pixels
    for(int i = 0; i < filterType; i++) {
        free(temp[i]);
    }
    free(temp);
    for(int i = 0; i < filterType; i++) {
        free(filter[i]);
    }
    free(filter);
    return new;
}

int** create3x3Filter() {
    //allocates filter and fills vals
    int** filter = allocateFilter(3);
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

int** create5x5Filter() {
    //allocates filter and fills vals
    int** filter = allocateFilter(5);

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

int calculateVal(pixel_t** pixels, int** filter, int size, int color) {
    //sum keeps track of the addition of all multiplied values
    int sum = 0;
    //loops through filter and pixels, and calculates value for each color
    for(int r = 0; r < size; r++) {
        for(int c = 0; c < size; c++) {
            if(color == 0) {
                sum += (pixels[r][c].red * filter[r][c]);
            }
            else if(color == 1) {
                sum += (pixels[r][c].green * filter[r][c]);
            }
            else {
                sum += (pixels[r][c].blue * filter[r][c]);
            }
        }
    }

    //returns sum as a parameter for isValid function
    return isValid(sum);
}

int isValid(int val) {
    //makes sure the int is 0 < x < 255, and if it exceeds bounds it returns nearest bound
    if(val < 0) {
        return 0;
    }
    else if(val > 255) {
        return 255;
    }
    else return val;
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

int** allocateFilter(int size) {
    //allocates a square 2D int array of size
    int** filter = malloc(size * sizeof(int*));
    for(int i = 0; i < size; i++) {
        filter[i] = (int*)malloc(sizeof(int) * size);
    }
    return filter;
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

