#include <chrono>
#include <iostream>
#include <vector>

#include "../sortings/sort.h"

using namespace std;

int *genIntArr(size_t size) {
  int *arr = new int[size];
  for (size_t i = 0; i < size; i++) arr[i] = static_cast<int>(rand() % INT_MAX);

  return arr;
}

long *genLongArr(size_t size) {
  long *arr = new long[size];
  for (size_t i = 0; i < size; i++) arr[i] = rand() % 2147;

  return arr;
}

int main() {
  srand(time(0));
  auto sort = new QuickSort<long>("Quick Sort", static_cast<unsigned short>(1),
                                  [](long a, long b) {
                                    if (a < b) return (char)-1;
                                    if (a > b) return (char)1;
                                    return (char)0;
                                  });

  for (size_t i = 1000; i <= SIZE_T_MAX; i *= 2) {
    cout << "Test size: " << i << endl;
    long *arr1 = genLongArr(i);
    // long* arr2 = new long[i];
    // std::copy(arr1, arr1 + i, arr2);
    sort->test(arr1, i);
    cout << endl;

    delete[] arr1;
  }

  return 1;
}
