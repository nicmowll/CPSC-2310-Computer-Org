/*
Name: Nic Mowll
Lab Section: 004
Lab 8
username: nmowll
*/
#include "functions.h"

#include <stdio.h>

int main() {
    //testing absolute value function
    assert(absValue(-1) == 1);
    assert(absValue(1) == 1);

    //testing bindary & operator function
    assert(binaryAnd(5, 6) == 4);
    assert(binaryAnd(-3, 5) == 5);
    assert(binaryAnd(-1, 1) == 1);

    //testing binary ~| operator function
    assert(binaryNotOr(0x6, 0x5) == 0xFFFFFFF8);
    assert(binaryNotOr(0x8, 0xE) == 0xFFFFFFF1);

    //testing binary | operator function
    assert(binaryOr(6, 5) == 7);
    assert(binaryOr(3, -6) == -5);

    //testing binary ^ operator function
    assert(binaryXor(4, 5) == 1);
    assert(binaryXor(6, -6) == -4);

    //testing adding unsigned int function
    assert(unsignedAddOK(0xFFFFFFFE, 0x1) == 1);
    assert(unsignedAddOK(0xFFFFFFFE, 0x2) == 0);

    //testing adding int function
    assert(twosAddOk(0x7FFFFFFF, 0x1) == 0);
    assert(twosAddOk(0x0FFFFFFF, 0x1) == 1);
    assert(twosAddOk(0x80000000, -1) == 0);
    assert(twosAddOk(0x80000001, -1) == 1);
    assert(twosAddOk(0x80000000, 0x0FFFFFFF) == 1);

    //testing subtracting in function
    assert(twosSubtractOK(0x80000000, 0x1) == 0);
    assert(twosSubtractOK(0xFFFFFFFC, 0x1) == 1);
    assert(twosSubtractOK(0x7FFFFFFF, -1) == 0);
    assert(twosSubtractOK(4, -1) == 1);
    assert(twosSubtractOK(7, 8) == 1);

    return 0;
}