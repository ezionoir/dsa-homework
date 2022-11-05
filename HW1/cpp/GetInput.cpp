#include <iostream>

using namespace std;

void GetInput(int argc, char** argv, int* &a, int &n, int &k) {
    k = atoi(argv[1]);

    n = argc - 2;
    
    a = new int[n];
    for (int i = 0; i < n; ++i)
        a[i] = atoi(argv[2 + i]);
}