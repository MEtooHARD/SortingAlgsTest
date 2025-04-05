#ifndef SORT_H
#define SORT_H

#include <chrono>
#include <functional>

#include "arr_manager.h"

using namespace std;

/* BASIC */
template <typename T>
class SortAlg {
 protected:
  // <0: a<b | 0: a==b | >0: a>b
  using Comparator = std::function<char(const T &, const T &)>;
  using Edge = unsigned short;

  Edge edge;
  Comparator compare;
  virtual void sorter(T *arr, size_t size) = 0;

 public:
  SortAlg(Edge edge, Comparator comp) : edge(edge), compare(comp) {}

  chrono::milliseconds test(T *arr, size_t size) {
    auto start = chrono::high_resolution_clock::now();
    sorter(arr, size);
    auto end = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::milliseconds>(end - start);
  };

 protected:
  void swap(T &a, T &b) {
    T temp = a;
    a = b;
    b = temp;
  }
  bool isOrdered(T *arr, size_t size) {
    for (size_t i = 1; i < size; i++)
      if (compare(arr[i - 1], arr[i]) > 0) return false;

    return true;
  }
};
/* BASIC */

/* Quick Sort */
template <typename T>
class QuickSort : public SortAlg<T> {
  using Base = SortAlg<T>;
  using typename Base::Comparator;
  using typename Base::Edge;

  void sorter(T *arr, size_t size) { quickSort(arr, 0, size); }

  void quickSort(T *arr, size_t low, size_t high) {
    if (low < high) {
      T p = partition(arr, low, high);
      quickSort(arr, low, p - 1);
      quickSort(arr, p + 1, high);
    }
  }

 public:
  QuickSort(Edge edge, Comparator comp) : SortAlg<T>(edge, comp) {}

 protected:
  size_t partition(T *arr, size_t low, size_t high) {
    size_t pivot = arr[high];
    size_t i = low;
    size_t j = high - 1;

    while (true) {
      while (i <= j && this->compare(arr[i], pivot) <= 0) i++;
      while (j >= i && this->compare(arr[j], pivot) > 0) j--;
      if (i >= j) break;
      this->swap(arr[i], arr[j]);
    }

    this->swap(arr[i], arr[high]);
    return i;
  }
};
/* Quick Sort */

/* Merge Sort */
template <typename T>
class MergeSort : public SortAlg<T> {
  using Base = SortAlg<T>;
  using typename Base::Comparator;
  using typename Base::Edge;

 private:
  bool reuseArr;
  ArrayManager<T> arrManager;

  void sorter(T *arr, size_t size) { mergeSort(arr, 0, size - 1); }

  void mergeSort(T *arr, size_t l, size_t r) {
    if (l < r) {
      size_t m = l + (r - l) / 2;

      mergeSort(arr, l, m);
      mergeSort(arr, m + 1, r);

      merge(arr, l, m, r);
    }
  }

 public:
  MergeSort(Edge edge, Comparator comp, bool reuseArr)
      : SortAlg<T>(edge, comp), reuseArr(reuseArr) {}

 protected:
  void merge(T *arr, size_t l, size_t m, size_t r) {
    size_t n = r - l + 1;
    T *tempArr = this->reuseArr ? arrManager.getArray(n) : new T[n];
    size_t Ls = l, Le = m, Rs = m + 1, k = 0;  // r = Re

    while (Ls <= Le && Rs <= r) {
      if (this->compare(arr[Ls], arr[Rs]) <= 0)
        tempArr[k++] = arr[Ls++];
      else
        tempArr[k++] = arr[Rs++];
    }

    while (Rs <= r) tempArr[k++] = arr[Rs++];
    while (Ls <= Le) tempArr[k++] = arr[Ls++];

    for (size_t j = l, i = 0; j <= r; i++, j++)  //
      arr[j] = tempArr[i];

    if (!reuseArr) delete[] tempArr;
  }
};
/* Merge Sort */

#endif