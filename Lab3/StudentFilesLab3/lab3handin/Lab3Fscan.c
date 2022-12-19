/***********************
   *Nic Mowll
   *CPSC 2311 Sp22 004
   *nmowll@clemson.edu
   *********************/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

#include "Lab3Fscan.h"

/*Parameters: in - file pointer that points to open file
 *Return: void
 *Description: This function uses fscanf to read each
 *character from the file and if it is the start of a
 *comment, it calls rcomment. If not, it prints it to
 *the console.
*/
void start(FILE* in) {
    char ch;
    //scans in char if not end of file
    while(fscanf(in, "%c", &ch) !=EOF) {
        if(ch == '/') rcomment(in);
        else putchar(ch);
    }

}

/*Parameters: in - file pointer that points to open file
 *Return: void
 *Description: This function reads the next char of a comment
 *and determines the comment type. If it is a multiline comment
 *it calls skipM_comment, and if it is a single line comment
 *it calls skipM_comment
*/
void rcomment(FILE* in) {
    char ch;
    if(fscanf(in, "%c", &ch) !=EOF) {
        //if single line comment
        if(ch == '/') skipS_comment(in);
        //if multiline comment
        else if(ch == '*') skipM_comment(in);
    }
}

/*Parameters: in - file pointer that points to open file
 *Return: void
 *Description: This function skips a multiline comment and 
 *returns when it reaches the end of it
*/
void skipM_comment(FILE* in) {
    char ch;
    //boolean to keep track of if the last char was a '*'
    bool astr = false;
    while(fscanf(in, "%c", &ch) !=EOF) {
        /*if last char was a '*', and the current is '/'
         *then the comment is over and return*/
        if(astr && ch == '/') return;
        //if the current char is a '*' set bool to true
        if(ch == '*') astr = true;
        //if it isn't set bool to false
        else astr = false;
    }

    return;
}

/*Parameters: in - file pointer that points to open file
 *Return: void
 *Description: This function skips a single line comment and 
 *returns when it reaches the end of it
*/
void skipS_comment(FILE* in) {
    char ch;
    while(fscanf(in, "%c", &ch) !=EOF) {
        /*if the character is at the end of the line, the comment
         *is over so return*/
        if(ch == '\n') {
            //puts char back to not erase '\n'
            putchar(ch);
            return;
        }
    }

    return;
}