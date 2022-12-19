#include "./SparseTable.h"

SparseTable::SparseTable(string name) {
    string fileName = "./";
    fileName += name + ".txt";
    ifstream reader(fileName, ios::in);
    
    _name = name;
    reader >> _type;
    reader >> _nRow >> _nCol;

    _table = new int*[_nRow];
    for (int i = 0; i < _nRow; ++i)
        _table[i] = new int[_nCol];

    for (int i = 0; i < _nRow; ++i)
        for (int j = 0; i + (1 << j) - 1 < _nRow; ++j)
            reader >> _table[i][j];

    reader.close();
}

// SparseTable::SparseTable(string name, vector<int> arr, int (*getAlpha)(int x, int y)) {
//     _name = name;

//     _nRow = arr.size();
//     _nCol = int(ceil(log2(arr.size() + 1)));

//     _table = new int*[_nRow];
//     for (int i = 0; i < _nRow; ++i)
//         _table[i] = new int[_nCol];

//     for (int i = 0; i < _nRow; ++i)
//         _table[i][0] = arr[i];

//     for (int j = 1; j < _nCol; ++j) {
//         int interval = 1 << (j - 1);
//         for (int i = 0; i + interval * 2  - 1 < _nRow; ++i)
//             _table[i][j] = getAlpha(_table[i][j - 1], _table[i + interval][j - 1]);
//     }
// }

SparseTable::SparseTable(string name, vector<int> arr, int type) {
    _name = name;
    _type = type;
    _nRow = arr.size();
    _nCol = int(ceil(log2(arr.size() + 1)));

    _table = new int*[_nRow];
    for (int i = 0; i < _nRow; ++i)
        _table[i] = new int[_nCol];

    for (int i = 0; i < _nRow; ++i)
        _table[i][0] = arr[i];

    int (*getAlpha)(int, int);
    switch (_type) {
        case TYPE_MIN:
            getAlpha = isLess;
            break;
        case TYPE_MAX:
            getAlpha = isGreater;
            break;
        case TYPE_GCD:
            getAlpha = findGCD;
            break;
    }

    for (int j = 1; j < _nCol; ++j) {
        int interval = 1 << (j - 1);
        for (int i = 0; i + interval * 2  - 1 < _nRow; ++i)
            _table[i][j] = getAlpha(_table[i][j - 1], _table[i + interval][j - 1]);
    }
}

SparseTable::~SparseTable() {
    for (int i = 0; i < _nRow; ++i)
        delete[] _table[i];
    delete[] _table;
}

ofstream& operator<<(ofstream& writer, const SparseTable& st) {
    writer << st._type << endl;
    writer << st._nRow << " " << st._nCol << endl;
    for (int i = 0; i < st._nRow; ++i) {
        for (int j = 0; i + (1 << j) - 1 < st._nRow; ++j)
            writer << st._table[i][j] << "\t";
        writer << endl;
    }

    return writer;
}

ostream& operator<<(ostream& writer, const SparseTable& st) {
    for (int i = 0; i < st._nRow; ++i) {
        for (int j = 0; i + (1 << j) - 1 < st._nRow; ++j)
            writer << st._table[i][j] << "\t";
        writer << endl;
    }

    return writer;
}

int SparseTable::query(int lower, int upper) {
    int j = int(floor(log2(upper - lower + 1)));

    int (*getAlpha)(int, int);
    switch (_type) {
        case TYPE_MIN:
            getAlpha = isLess;
            break;
        case TYPE_MAX:
            getAlpha = isGreater;
            break;
        case TYPE_GCD:
            getAlpha = findGCD;
            break;
    }

    return getAlpha(_table[lower][j], _table[upper + 1 - (1 << j)][j]);
}