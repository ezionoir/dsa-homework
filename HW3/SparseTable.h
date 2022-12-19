#ifndef SPARSE_TABLE_H
#define SPARSE_TABLE_H

#include "./GetAlpha.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

#define TYPE_MIN 0
#define TYPE_MAX 1
#define TYPE_GCD 2

class SparseTable {
public:
    string _name;
    int _type;
    int** _table;
    int _nRow, _nCol;
public:
    SparseTable(string name);
    // SparseTable(string name, vector<int> arr, int (*getAlpha)(int x, int y));
    SparseTable(string name, vector<int> arr, int type);
    ~SparseTable();
public:
    friend ofstream& operator<<(ofstream& writer, const SparseTable& st);
    friend ostream& operator<<(ostream& writer, const SparseTable& st);
public:
    int query(int lower, int upper);
};

#endif