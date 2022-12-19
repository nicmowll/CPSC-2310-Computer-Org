/*************************
 *Name: Nic Mowll
 *CPSC 2311 004
 *Spring 22
 *nmowll@g.clemson.edu
 *************************/

#include "ppm.h"
#include "ppm.c"

int main(int argc, char* argv[]) {
    //makes sure correct number of arguments given
    if(argc != 4) {
        fprintf(stderr, "\nCommand line arguments not equal to 4\n");
    }
    //creates 3 file pointers
    FILE * in = fopen(argv[1], "r");
    FILE * outGray = fopen(argv[2], "w");
    FILE * outFlip = fopen(argv[3], "w");
    //makes sure files were opened correctly
    if(in == NULL || outFlip == NULL || outGray == NULL) {
        fprintf(stderr, "\nFiles not opened correctly\n");
    }

    //calls methods to read in header, pixel values, and create gray and flipped version of image
    header_t* header = readHeader(in);
    pixel_t** pixels = readPPM(in, header);
    grayScaleImage(header, pixels, outGray);
    flipImage(header, pixels, outFlip);

    //clean up
    fclose(in);
    fclose(outFlip);
    fclose(outGray);
    freeMemory(pixels, header);
    
    return 0;
}