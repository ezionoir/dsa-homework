#ifndef COMMAND_PROCESS_H
#define COMMAND_PROCESS_H

#include "./SparseTable.h"

#include <cstring>

using namespace std;

int isLess(int a, int b);
int isGreater(int a, int b);
int findGCD(int a, int b);
void CommandProcess(int argc, char** argv);

#endif