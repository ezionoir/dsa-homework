#ifndef LZW_H
#define LZW_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

#define CHAR_SIZE 9

vector<int> encode(string input);
string decode(vector<int> input);

#endif