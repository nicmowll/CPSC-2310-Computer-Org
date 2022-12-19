/*************************
 *Name: Nic Mowll
 *CPSC 2311 004
 *Spring 22
 *nmowll@g.clemson.edu
 *Collaborated with: Clarke Reabel
 *************************/

#include "ppm.h"
#include "ppm.c"

int main(int argc, char* argv[]) {
    //makes sure correct number of arguments given
    if(argc != 3) {
        fprintf(stderr, "\nCommand line arguments not equal to 3\n");
    }
    //creates file pointers
    FILE * in = fopen(argv[1], "r");
    FILE * out = fopen(argv[2], "w");
    //makes sure files were opened correctly
    if(in == NULL || out == NULL) {
        fprintf(stderr, "\nFiles not opened correctly\n");
    }

    //calls methods to read in header, pixel values, and create collage
    header_t* header = readHeader(in); //reads in ppm header
    pixel_t** pixels = readPPM(in, header); //reads in ppm pixel data
    createCollage(header, pixels, out); //runs create collage function

    //clean up
    fclose(in);
    fclose(out);
    freeMemory(pixels, header);
    
    return 0;
}