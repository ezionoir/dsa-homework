#ifndef COMMAND_PROCESS_H
#define COMMAND_PROCESS_H

#include "./LZW.h"

#include <sstream>
#include <cstring>
#include <iomanip>

string ToBinary(int x, int nbits);
void CommandProcess(int argc, char** argv);

#endif