#include "./GetAlpha.h"

int isLess(int a, int b) {
    return (a < b) ? a : b;
}

int isGreater(int a, int b) {
    return (a > b) ? a : b;
}

int findGCD(int a, int b) {
    if (b == 0) return a;
    return findGCD(b, a % b);
}