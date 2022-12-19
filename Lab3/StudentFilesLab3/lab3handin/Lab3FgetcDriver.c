/***********************
   *Nic Mowll
   *CPSC 2311 Sp22 004
   *nmowll@clemson.edu
   *********************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "Lab3Fgetc.h"
#include "Lab3Fgetc.c"

/*Parameters: argc - holds number of command line arguments
 *            argv - array of each argument
 *Return: main function return - at end of program
 *Description: This function asserts there are 2 arguments, 
 *the executive and the input file. It opens the file correctly
 *and calls the start function. After, it cleans up.
*/
int main(int argc, char* argv[])
{
    //making sure there are 2 arguments
    assert(argc == 2);
    FILE * in = fopen(argv[1], "r");
    //making sure file is correctly opened
    assert(in != NULL);
    start(in);

    //closes file and returns
    fclose(in);
    return 0;
}