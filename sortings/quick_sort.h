#include <stack>

#include "sort.h"

template <typename T>
class QuickSort : public SortAlg<T> {
  const bool medianOf3;
  const bool recursive = false;
  size_t RCR_LIMIT = 10'000'000;  // 10M
  using Base = SortAlg<T>;

  void sorter(T *arr, size_t size) override {
    if (recursive)
      if (size > RCR_LIMIT)
        std::cout << "Recursion limit hit. Sort skipped." << std::endl;
      else
        sort_Recursive(arr, 0, size - 1);
    else
      sort_Iterative(arr, 0, size - 1);
  }

  std::string info() {
    return Base::info() + "\nRecursion: " + (recursive ? "Yes" : "No") +
           "\nMedian of 3: " + (medianOf3 ? "Yes" : "No") +
           "\nRecursion limit: " + std::to_string(RCR_LIMIT);
  }

 public:
  using typename Base::Comparator;
  using typename Base::Edge;

  QuickSort(bool medOf3, bool rec, Edge e, size_t RCR_LIM, Comparator comp)
      : SortAlg<T>(e, comp, "Quick Sort"),
        medianOf3(medOf3),
        recursive(rec),
        RCR_LIMIT(RCR_LIM) {}

 protected:
  void sort_Recursive(T *arr, size_t low, size_t high) {
    if (low < high) {
      size_t p = this->partition(arr, low, high);
      sort_Recursive(arr, low, p - 1);
      sort_Recursive(arr, p + 1, high);
    }
  }

  void sort_Iterative(T *arr, size_t low, size_t high) {
    std::stack<std::pair<size_t, size_t>> stk;
    stk.push({low, high});

    while (!stk.empty()) {
      auto [l, h] = stk.top();
      stk.pop();

      if (l >= h) continue;

      if (h - l + 1 <= this->edge) {
        this->insertionSort(arr, l, h);
      } else {
        size_t p = this->partition(arr, l, h);
        if (p > l) stk.push({l, p - 1});
        if (p < h) stk.push({p + 1, h});
      }
    }
  }

  size_t partition(T *arr, size_t low, size_t high) {
    if (medianOf3) {
      size_t mid = low + (high - low) / 2;
      if (this->compare(arr[low], arr[mid]) > 0) this->swap(arr[low], arr[mid]);
      if (this->compare(arr[mid], arr[high]) > 0)
        this->swap(arr[mid], arr[high]);
      if (this->compare(arr[low], arr[mid]) > 0) this->swap(arr[low], arr[mid]);
      this->swap(arr[mid], arr[high]);
    }

    size_t i = low;
    size_t j = high - 1;

    while (true) {
      while (i <= j && this->compare(arr[i], arr[high]) <= 0) i++;
      while (j >= i && this->compare(arr[j], arr[high]) > 0) j--;
      if (i >= j) break;
      this->swap(arr[i], arr[j]);
    }

    this->swap(arr[i], arr[high]);
    return i;
  }
};
