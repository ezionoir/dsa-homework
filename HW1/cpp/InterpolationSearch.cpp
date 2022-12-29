// https://www.geeksforgeeks.org/interpolation-search/

#include <iostream>
#include <cmath>

using namespace std;

int InterpolationSearch(int a[], int n, int k, int& loopCount) {
    int left = 0, right = n - 1;
    loopCount = 0;

    // If all conditions are sastified, then start a new loop
    while ((left <= right) && (k >= a[left]) && (k <= a[right]) && (++loopCount)) {
        //   x - left          right - left
        // -------------- = ------------------
        // a[x] - a[left]   a[right] - a[left]
        int x = left + int(floor((right - left) * double(k - a[left]) / double(a[right] - a[left])));
        if (a[x] == k) return x;
        if (a[x] < k) left = x + 1;
        else right = x - 1;
    }

    return -1;
}