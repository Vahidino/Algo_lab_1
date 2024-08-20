#pragma once
#include <iostream>
#include <algorithm>
#include <stack>


// Quicksort using the last element as pivot
template<typename T>
int partition(T array[], int left, int right) {
    T pivot = array[right];
    int i = left - 1;
    for (int j = left; j < right; ++j) {
        if (array[j] <= pivot) {
            ++i;
            std::swap(array[i], array[j]);
        }
    }
    std::swap(array[i + 1], array[right]);
    return i + 1;
}

template<typename T>
void quicksortIterativeLast(T array[], int left, int right) {
    std::stack<std::pair<int, int>> stack;
    stack.push(std::make_pair(left, right));

    while (!stack.empty()) {
        std::pair<int, int> bounds = stack.top();
        stack.pop();

        int l = bounds.first;
        int r = bounds.second;

        if (l < r) {
            int pivot = partition(array, l, r);
            stack.push(std::make_pair(l, pivot - 1));
            stack.push(std::make_pair(pivot + 1, r));
        }
    }
}

template<typename T>
void quicksortPivotLast(T arr[], int n) {
    quicksortIterativeLast(arr, 0, n - 1);
}

template<typename T>
int partitionMedian(T array[], int left, int right) {
    int middle = (left + right) / 2;

    // Find the median of the first, middle, and last elements
    if (array[middle] < array[left])
        std::swap(array[left], array[middle]);
    if (array[right] < array[left])
        std::swap(array[left], array[right]);
    if (array[right] < array[middle])
        std::swap(array[middle], array[right]);

    std::swap(array[middle], array[right]); // Move pivot to the end

    return partition(array, left, right);
}

template<typename T>
void quicksortIterativeMedian(T array[], int left, int right) {
    std::stack<std::pair<int, int>> stack;
    stack.push(std::make_pair(left, right));

    while (!stack.empty()) {
        std::pair<int, int> bounds = stack.top();
        stack.pop();

        int l = bounds.first;
        int r = bounds.second;

        if (l < r) {
            int pivot = partitionMedian(array, l, r);
            stack.push(std::make_pair(l, pivot - 1));
            stack.push(std::make_pair(pivot + 1, r));
        }
    }
}

template<typename T>
void quicksortPivotMedian(T arr[], int n) {
    quicksortIterativeMedian(arr, 0, n - 1);
}

// Heapsort with d-ary heap
template<typename T>
void heapify(T arr[], int n, int i, int d) {
    int largest = i;
    for (int j = 1; j <= d; ++j) {
        int childIndex = d * i + j;
        if (childIndex < n && arr[childIndex] > arr[largest])
            largest = childIndex;
    }
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest, d);
    }
}

template<typename T>
void heapsort(T arr[], int n, int d) {
    for (int i = (n - 1) / d; i >= 0; --i) {
        heapify(arr, n, i, d);
    }
    for (int i = n - 1; i >= 0; --i) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0, d);
    }
}
