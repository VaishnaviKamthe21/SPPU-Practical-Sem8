#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

// Merge Function
void merge(vector<int>& arr, int l, int m, int r) {

    vector<int> temp;

    int i = l;
    int j = m + 1;

    while (i <= m && j <= r) {

        if (arr[i] < arr[j]) {
            temp.push_back(arr[i++]);
        }
        else {
            temp.push_back(arr[j++]);
        }
    }

    while (i <= m) {
        temp.push_back(arr[i++]);
    }

    while (j <= r) {
        temp.push_back(arr[j++]);
    }

    for (int k = l; k <= r; k++) {
        arr[k] = temp[k - l];
    }
}

// Sequential Merge Sort
void mergeSortSequential(vector<int>& arr, int l, int r) {

    if (l >= r)
        return;

    int m = (l + r) / 2;

    mergeSortSequential(arr, l, m);
    mergeSortSequential(arr, m + 1, r);

    merge(arr, l, m, r);
}

// Parallel Merge Sort
void mergeSortParallel(vector<int>& arr, int l, int r) {

    if (l >= r)
        return;

    int m = (l + r) / 2;

    #pragma omp parallel sections
    {
        #pragma omp section
        mergeSortParallel(arr, l, m);

        #pragma omp section
        mergeSortParallel(arr, m + 1, r);
    }

    merge(arr, l, m, r);
}

// Display Array
void display(vector<int>& arr) {

    for (int x : arr) {
        cout << x << " ";
    }

    cout << endl;
}

int main() {

    vector<int> arr1 = {5,4,3,2,1};
    vector<int> arr2 = arr1;

    // Sequential
    mergeSortSequential(arr1, 0, arr1.size() - 1);

    cout << "Sequential Merge Sort: ";
    display(arr1);

    // Parallel
    mergeSortParallel(arr2, 0, arr2.size() - 1);

    cout << "Parallel Merge Sort: ";
    display(arr2);

    return 0;
}