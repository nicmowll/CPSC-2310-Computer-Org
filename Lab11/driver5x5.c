/*************************
*Nic Mowll
*CPSC 2311 Sp22 Section 004
*nmowll@clemson.edu
*************************/

#include "src/functions.h"

int main(int argc, char* argv[]) {
    //Make sure command line arguments is correct number
    if(argc != 2) {
        fprintf(stderr, "\nCommand line arguments not equal to 4\n");
    }

    //opens file pointers
    FILE * in = fopen(argv[1], "r");
    FILE * out = fopen("output5.ppm", "w");

    //makes sure files opened correctly
    if(in == NULL || out == NULL) {
        fprintf(stderr, "\nFiles not opened correctly\n");
    }

    //creates header and 2D array for pixels
    header_t* header = readHeader(in);
    pixel_t** pixels = readPPM(in, header);

    //filters pixels by 5x5 and writes to output
    pixel_t** filteredPixels = sharpen(pixels, header, 5);
    writeP6Image(header, filteredPixels, out);

    //clean up
    fclose(in);
    fclose(out);
    for(int row = 0; row < header->width; row++) {
            free(filteredPixels[row]);
    }
    //frees double pointer
    free(filteredPixels);
    freeMemory(pixels, header);
}