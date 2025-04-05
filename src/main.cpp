#include <chrono>
#include <iostream>
#include <vector>

#include "../sortings/sort.h"

using namespace std;

chrono::milliseconds testSortingAlgorithm(  // (this comment is for new line)
    function<void(long*, long)> sortFunc, long* arr, long size) {
  auto start = chrono::high_resolution_clock::now();
  sortFunc(arr, size);
  auto end = chrono::high_resolution_clock::now();
  return chrono::duration_cast<chrono::milliseconds>(end - start);
}

long* genArr(long size) {
  long* arr = new long[size];
  srand(time(0));
  for (long i = 0; i < size; i++) arr[i] = rand() % 100;

  return arr;
}

enum SortingAlgs { MERGE_SORT, QUICK_SORT };

void test(long* arr, long N, SortingAlgs alg) {
  // auto func = alg == SortingAlgs::MERGE_SORT ? MergeSort : QuickSort;

  cout << "\tAlg: "
       << (alg == SortingAlgs::MERGE_SORT ? "MergeSort" : "QuickSort") << '\n';
  // auto duration = testSortingAlgorithm(QuickSort, arr, N);
  // cout << '\t' << (isOrdered(arr, N) ? "✅ Pass" : "❌ Failed") << '\n';
  // cout << "\tTime: " << duration.count() << " ms\n";
}

int main() {
  new QuickSort<int>(                  //
      static_cast<unsigned short>(1),  //
      [](int a, int b) {
        if (a < b) return (char)-1;
        if (a > b) return (char)1;
        return (char)0;
      });
  // for (long i = 1000; i <= 100000000; i *= 2) {
  //   long* arr1 = genArr(i);
  //   long* arr2 = new long[i];
  //   std::copy(arr1, arr1 + i, arr2);

  //   cout << "Test\n";
  //   cout << "\tN: " << i << '\n';
  //   test(arr1, i, SortingAlgs::MERGE_SORT);
  //   cout << "\t----------\n";
  //   test(arr2, i, SortingAlgs::QUICK_SORT);
  //   cout << '\n';

  //   delete[] arr1;
  //   delete[] arr2;
  // }

  return 1;
}
