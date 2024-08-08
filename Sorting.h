#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

// Quicksort using the last element as pivot
template<typename T>
int partition(T array[], int indexStart, int indexEnd) {
    int pivot = array[indexEnd];
    int i = indexStart - 1;
    for (int j = indexStart; j <= indexEnd - 1; ++j) {
        if (array[j] <= pivot) {
            i++;
            std::swap(array[i], array[j]);
        }
    }
    std::swap(array[i + 1], array[indexEnd]);
    return i + 1;
}

template<typename T>
void quicksortLast(T array[], int indexStart, int indexEnd) {
    if (indexStart < indexEnd) {
        
        // Partition the array, and get the index of the pivot
        int pivot = partition(array, indexStart, indexEnd);

        // Recursively sort the subarrays on either side of the pivot
        quicksortLast(array, indexStart, pivot - 1);
        quicksortLast(array, pivot + 1, indexEnd);
    
    }
}

// using the last element as pivot
template<typename T>
void quicksortPivotLast(T arr[], int n) { 

    quicksortLast(arr, 0, n - 1);

}

// Quicksort using the median of three as pivot
template<typename T>
int partition_Median(T array[], int left, int right) {
    int middle = left + (right - left) / 2;
    int pivotIndex = right;

    if (array[left] > array[middle]) {

        if (array[left] < array[right]) {

            pivotIndex = left;

        }
        else if (array[middle] > array[right]) {

            pivotIndex = middle;

        }
    }
    else {

        if (array[middle] < array[right]) {

            pivotIndex = middle;

        }
        else if (array[left] > array[right]) {

            pivotIndex = left;

        }
    }

    std::swap(array[pivotIndex], array[right]);
    return partition(array, left, right);
}

template<typename T>
void quicksortMedian(T array[], int indexStart, int indexEnd)
{
    if (indexStart >= indexEnd)//f�r att inte f� stack overflow f�r fuck ded�r
        return;
    if (indexStart >= 0) {
        // Partition the array, and get the index of the pivot
        int pivot = partition_Median(array, indexStart, indexEnd);

        // Recursively sort the subarrays on either side of the pivot
        quicksortMedian(array, indexStart, pivot - 1);
        quicksortMedian(array, pivot + 1, indexEnd);
    }
    // No need to handle the case when indexStart >= indexEnd, which will act as the exit condition.
}

// median of first, middle and last element as 
template<typename T>
void quicksortPivotMedian(T arr[], int n) {
    quicksortMedian(arr, 0, n - 1);
}

// Heapsort with d-ary heap
template<typename T>
void heapify(T arr[], int n, int i, int d)
{
    int largest = i;

    for (int j = 1; j <= d; j++)
    {
        int childIndex = d * i + j;
        if (childIndex < n && arr[childIndex] > arr[largest])
            largest = childIndex;
    }
    if (arr[largest] != arr[i]) {
        int temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        heapify(arr, n, largest, d);
    }
}

template<typename T>
void heapsort(T arr[], int n, int d) { // d represents he number of children in the maxheap 
    for (int i = (n - 1) / d; i >= 0; i--) {
        heapify(arr, n, i, d);
    }
    for (int i = n - 1; i >= 0; i--) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0, d);
    }
}
