#ifndef SORT_H
#define SORT_H

#include <chrono>
#include <functional>
#include <string>

#include "arr_manager.h"

/* BASIC */
template <typename T>
class SortAlg {
 protected:
  // <0: a<b | 0: a==b | >0: a>b
  using Comparator = std::function<char(const T &, const T &)>;
  using Edge = unsigned short;

  Edge edge;
  Comparator compare;
  std::string name;
  virtual void sorter(T *arr, size_t size) = 0;

  virtual std::string info() { return "Alg: " + name; }

 public:
  SortAlg(Edge edg, Comparator comp, std::string name)
      : edge(edg), compare(comp), name(name) {}

  std::chrono::microseconds test(T *arr, size_t size) {
    // std::cout << "Size: " << size << std::endl;
    std::cout << info() << std::endl;

    auto start = std::chrono::high_resolution_clock::now();
    sorter(arr, size);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Result: " << (isOrdered(arr, size) ? "Pass" : "Fail");
    std::cout << "\nTime: " << duration.count() << " (micro sec)" << std::endl
              << "==" << std::endl;

    return duration;
  }

 protected:
  void swap(T &a, T &b) {
    T temp = a;
    a = b;
    b = temp;
  }

  bool isOrdered(T *arr, size_t size) {
    if (!arr || size <= 1) return true;
    for (size_t i = 1; i < size; i++)
      if (compare(arr[i - 1], arr[i]) > 0) return false;

    return true;
  }

  void insertionSort(T *arr, size_t l, size_t r) {
    for (size_t i = l + 1; i <= r; i++) {
      T key = arr[i];
      size_t j = i;
      while (j > l && this->compare(arr[j - 1], key) > 0) {
        arr[j] = arr[j - 1];
        j--;
      }
      arr[j] = key;
    }
  }
};
/* BASIC */

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
  MergeSort(std::string name, Edge edge, Comparator comp, bool rusArr)
      : SortAlg<T>(edge, comp, name), reuseArr(rusArr) {}

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