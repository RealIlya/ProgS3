#include "sort.h"

int partition(std::vector<int> &array, int left, int right) {
  int x = array[right];
  int i = left - 1;
  int j;
  for (j = left; j < right; j++)
    if (array[j] <= x) std::swap(array[++i], array[j]);
  std::swap(array[right], array[i + 1]);
  return i + 1;
}

void quicksort(std::vector<int> &array, int left, int right) {
  int pivot;
  if (left < right) {
    pivot = partition(array, left, right);
    quicksort(array, left, pivot - 1);
    quicksort(array, pivot + 1, right);
  }
}

/// @brief quick sort
/// @param data
void sort(std::vector<int> &data) { quicksort(data, 0, data.size() - 1); }