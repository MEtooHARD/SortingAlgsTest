#include <vector>
#ifndef SORT_H
#define SORT_H

/* BASIC */
void swap(long &a, long &b);
bool isOrdered(long *arr, long size);
/* BASIC */

/* Quick Sort */
long partition(long *arr, long low, long high);
void QuickSort(long *arr, long size);
// void quickSort(long *arr, long low, long high);
/* Quick Sort */

/* Merge Sort */
void merge(long *arr, long l, long m, long r);
void MergeSort(long *arr, long size);
// void mergeSort(long *arr, long l, long r);
/* Merge Sort */
#endif
