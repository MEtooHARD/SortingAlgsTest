#include <stdexcept>
#include <unordered_map>
/*
as merge sort uses lots of arrays
and some of them are with same sizes that can be reused
this manager should largely enhance the performance overall
 */
template <typename T>
class ArrayManager {
 private:
  std::unordered_map<size_t, T*> arrays;

 public:
  ~ArrayManager() {
    for (auto& [size, arr] : arrays) delete[] arr;
  }

  T* getArray(size_t size) {
    if (size == 0) throw std::invalid_argument("Size must be positive");
    // find existing array
    auto it = arrays.find(size);
    if (it != arrays.end())  //
      return it->second;
    // no? create one
    T* newArr = new T[size];
    arrays[size] = newArr;
    return newArr;
  }
};