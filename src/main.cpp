/**
 * compile command: g++ -std=c++17 -I./sortings src/main.cpp -o main
 */

#include <chrono>
#include <iostream>
#include <vector>

#include "../sortings/quick_sort.h"
#include "../sortings/sort.h"

using namespace std;

QuickSort<long> *QS_Long_Lo3_R;
QuickSort<int> *QS_Int_Lo3_R;
QuickSort<short> *QS_Short_Lo3_R;

QuickSort<long> *QS_Long_Mo3_R;
QuickSort<int> *QS_Int_Mo3_R;
QuickSort<short> *QS_Short_Mo3_R;

template <typename T>
typename std::enable_if<std::is_integral<T>::value, T *>::type  //
genIntgrArr(size_t size) {
  T *arr = new T[size];
  for (size_t i = 0; i < size; i++) arr[i] = static_cast<T>(rand() % 3000000);

  return arr;
}

void init();
void unitTestWith(size_t size);

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
  init();
  srand(time(0));

  // QuickSort<int>::setRecursionLimit(10_000_000); // default 10M

  auto sort = QS_Long_Mo3_R;
  // SortAlg<long> *sortLong[2] = {QS_Long_Lo3_R, QS_Long_Mo3_R};
  // SortAlg<int> *sortInt[2] = {QS_Int_Lo3_R, QS_Int_Mo3_R};
  // SortAlg<short> *sortShort[2] = {QS_Short_Lo3_R, QS_Short_Mo3_R};

  for (size_t i = 1000; i <= SIZE_MAX; i *= 10) {
    cout << "Test size: " << i << endl << "====================" << endl;
    long *arr1 = genIntgrArr<long>(i);
    // long* arr2 = new long[i];
    // std::copy(arr1, arr1 + i, arr2);
    sort->test(arr1, i);
    cout << endl;

    delete[] arr1;
  }

  return 3;
}

void unitTestWith(size_t size) {
  long *arr1 = genIntgrArr<long>(size);

  cout << "Testing Long" << endl;
  QS_Long_Lo3_R->test(arr1, size);
  QS_Long_Mo3_R->test(arr1, size);
  cout << endl;

  int *arr2 = genIntgrArr<int>(size);

  cout << "Testing Int" << endl;
  QS_Int_Lo3_R->test(arr2, size);
  QS_Int_Mo3_R->test(arr2, size);
  cout << endl;

  short *arr3 = genIntgrArr<short>(size);

  cout << "Testing Short" << endl;
  QS_Short_Lo3_R->test(arr3, size);
  QS_Short_Mo3_R->test(arr3, size);
  cout << endl;

  delete[] arr1;
  delete[] arr2;
  delete[] arr3;
}

void init() {
  QS_Long_Lo3_R = new QuickSort<long>(  //
      false, true, EDGE, RCR_LIMIT,     //
      [](long a, long b) {
        if (a < b) return (char)-1;
        if (a > b) return (char)1;
        return (char)0;
      });
  QS_Int_Lo3_R = new QuickSort<int>(  //
      false, true, EDGE, RCR_LIMIT,   //
      [](int a, int b) {
        if (a < b) return (char)-1;
        if (a > b) return (char)1;
        return (char)0;
      });
  QS_Short_Lo3_R = new QuickSort<short>(  //
      false, true, EDGE, RCR_LIMIT,       //
      [](short a, short b) {
        if (a < b) return (char)-1;
        if (a > b) return (char)1;
        return (char)0;
      });

  QS_Long_Mo3_R = new QuickSort<long>(  //
      true, true, EDGE, RCR_LIMIT,      //
      [](long a, long b) {
        if (a < b) return (char)-1;
        if (a > b) return (char)1;
        return (char)0;
      });
  QS_Int_Mo3_R = new QuickSort<int>(  //
      true, true, EDGE, RCR_LIMIT,    //
      [](int a, int b) {
        if (a < b) return (char)-1;
        if (a > b) return (char)1;
        return (char)0;
      });
  QS_Short_Mo3_R = new QuickSort<short>(  //
      true, true, EDGE, RCR_LIMIT,        //
      [](short a, short b) {
        if (a < b) return (char)-1;
        if (a > b) return (char)1;
        return (char)0;
      });
}