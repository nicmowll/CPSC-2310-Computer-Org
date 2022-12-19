/*
Name: Nic Mowll
Lab Section: 004
Lab 8
username: nmowll
*/
#include "functions.h"

int absValue(int x) {
    int a = x >> 31;
    int b = (x ^ a) + !!a;
    return b;
}

int binaryAnd(int x, int y) {
    return ~(~x | ~y);
}

int binaryNotOr(int x, int y) {
    return (~x & ~y);
}

int binaryOr(int x, int y) {
    return ~(~x & ~y);
}

int binaryXor(int x, int y) {
    int p = ~(x & y);
    int a = x & p;
    int b = y & p;
    return ~(~a & ~b);
}

int unsignedAddOK(unsigned x, unsigned y) {
    unsigned int a = ~x;
    return (y <= a);
}

int twosAddOk(int x, int y) {
    int z = x + y;

    unsigned int a = x < 0;
    unsigned int b = y < 0;
    unsigned int c = z < 0;

    unsigned int dif = a ^ b;
    unsigned int signsEqual = (a == b && b == c);

    return (dif | signsEqual);
}

int twosSubtractOK(int x, int y) {
    int z = x - y;

    unsigned int a = x < 0;
    unsigned int b = y < 0;
    unsigned int c = z < 0;

    unsigned int same = !(a ^ b);
    unsigned int signsEqual = (a == c);

    return (same | signsEqual);
}