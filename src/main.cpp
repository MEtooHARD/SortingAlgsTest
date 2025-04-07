/**
 * compile command: g++ -std=c++17 -I./sortings src/main.cpp -o main
 */

#include <chrono>
#include <iostream>
#include <vector>

#include "../sortings/quick_sort.h"
#include "../sortings/sort.h"

using namespace std;

template <typename T>
typename std::enable_if<std::is_integral<T>::value, T *>::type  //
genIntgrArr(size_t size) {
  T *arr = new T[size];
  for (size_t i = 0; i < size; i++) arr[i] = static_cast<T>(rand() % 100);

  return arr;
}

unsigned short EDGE = 0;
size_t RCR_LIMIT = 10'000'000;  // 10M

/**
 * Test subjects:
 * 1. QuickSort (pivot picking, recursive/iterative)
 *   - QuickSort (median of 3, recursive)
 *   - QuickSort (median of 3, iterative)
 *   - QuickSort (last element, recursive)
 *   - QuickSort (last element, iterative)
 * 2. MergeSort ()
 *   - MergeSort (reuse array)
 *   - MergeSort (non-reuse array)
 */

int main() {
  srand(time(0));

  for (size_t i = 1000; i <= SIZE_MAX; i *= 10) {
    cout << "Test size: " << i << endl << "====================" << endl;
    int *refArr = genIntgrArr<int>(i);
    int *testArr = new int[i];

    /* test with different config */
    for (char m = 0; m < 2; m++) {
      for (char r = 0; r < 2; r++) {
        copy(refArr, refArr + i, testArr);

        QuickSort<int>(  //
            m, r, EDGE, RCR_LIMIT,
            [](int a, int b) {
              if (a < b) return (char)-1;
              if (a > b) return (char)1;
              return (char)0;
            })  //
            .test(testArr, i);
      }
    }

    cout << endl << endl;

    delete[] refArr;
    delete[] testArr;
  }

  return 3;
}
