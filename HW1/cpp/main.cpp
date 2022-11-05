#include "../header/InterpolationSearch.h"
#include "../header/GetInput.h"

#include <iostream>

using namespace std;

int main(int argc, char** argv) {
    int *a = nullptr;
    int n, k, loopCount;

    GetInput(argc, argv, a, n, k);

    int pos = InterpolationSearch(a, n, k, loopCount);
    cout << pos << " - " << loopCount << endl;

    delete[] a;

    return 0;
}