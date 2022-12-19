/***********************
   *Nic Mowll
   *CPSC 2311 Sp22 004
   *nmowll@clemson.edu
   *********************/

//header guard
#ifndef rodriguez
#define rodriguez

/*Parameter: in is the file pointer that should have been opened in the driver.
 *Return: void
 *Description: 
 *This function will use the 'C' style function fgetc to read in characters, 
 *one at a time, from the input file. As you read in the characters from the 
 *file, check each to determine if you are at the beginning of a comment.  
 *If you are at the beginning of a comment call the function rcomment 
 *(read comment). If you are not then use the 'C' function putchar to print the 
 *chararacter to stdout (standard out, a.k.a. the terminal). */
void start(FILE* in);

/*Parameter: 
 *'in' is the file pointer that should have been opened in the driver.
 *Return: void
 *Description:  
 *This function is called if you have determined you are at the beginning of a 
 *of a comment. It is called by the function start.
 *Now determine the type of comment. Continue to read until 
 *you are at the end of the comment.  There are two types of comments. If you
 *determine the comment is of type // then call skipS_comment (skip single line
 *comment) otherwise call skipM_comment (skip multi-line comment) */
void rcomment(FILE* in); 

/*This function continues to read and discard everything in a multi-line 
 *comment. You are required to use fgetc to read the characters in the 
 *comment.*/
void skipM_comment(FILE* in);

/*This function continues to read and discard everything in a single-line 
 *comment. You are required to use fgetc to read the characters in the 
 *comment.*/
void skipS_comment(FILE* in);

#endif /* rodriguez */