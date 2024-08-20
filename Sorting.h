#include "Sorting.h"
#include <string>
#include <chrono>
#include <crtdbg.h>
#include <fstream>
#include <iostream>
using namespace std;
using namespace std::chrono;

template<typename T>
bool checkIfSorted(T arr[], int n) {
    for (int i = 0; i < n - 1; ++i) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }
    return true;
}

void generateRandomNumbers(int*& arrPtr, int n, int lowerBound, int upperBound, unsigned int seed) {
    srand(seed);
    arrPtr = new int[n];
    for (int i = 0; i < n; ++i) {
        arrPtr[i] = rand() % (upperBound - lowerBound + 1) + lowerBound;
    }
}

template<typename T>
void reverseTheOrder(T arr[], int n) {
    for (int i = 0; i < n / 2; ++i) {
        std::swap(arr[i], arr[n - 1 - i]);
    }
}

void testSortingAlgorithms(int* arr, int* arrCopy1, int* arrCopy2, int numElements, int d) {
    // Random array
    auto start = high_resolution_clock::now();
    heapsort(arr, numElements, d);
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Heapsort with D=" << d << " (random) took " << duration.count() << " ms\n";
    if (!checkIfSorted(arr, numElements)) {
        cout << "Heapsort failed to sort the random array\n";
    }

    // Quicksort with pivot as last element
    start = high_resolution_clock::now();
    quicksortPivotLast(arrCopy1, numElements);
    end = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(end - start);
    cout << "Quicksort with pivot as last element (random) took " << duration.count() << " ms\n";
    if (!checkIfSorted(arrCopy1, numElements)) {
        cout << "Quicksort with pivot as last element failed to sort the random array\n";
    }

    // Quicksort with pivot as median element
    start = high_resolution_clock::now();
    quicksortPivotMedian(arrCopy2, numElements);
    end = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(end - start);
    cout << "Quicksort with pivot as median element (random) took " << duration.count() << " ms\n";
    if (!checkIfSorted(arrCopy2, numElements)) {
        cout << "Quicksort with pivot as median element failed to sort the random array\n";
    }

    // Testing sorted array
    std::copy(arr, arr + numElements, arrCopy1);
    std::copy(arr, arr + numElements, arrCopy2);
    auto sortedStart = high_resolution_clock::now();
    heapsort(arr, numElements, d);
    auto sortedEnd = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(sortedEnd - sortedStart);
    cout << "Heapsort with D=" << d << " (sorted) took " << duration.count() << " ms\n";
    if (!checkIfSorted(arr, numElements)) {
        cout << "Heapsort failed to sort the sorted array\n";
    }

    // Quicksort with pivot as last element (sorted)
    sortedStart = high_resolution_clock::now();
    quicksortPivotLast(arrCopy1, numElements);
    sortedEnd = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(sortedEnd - sortedStart);
    cout << "Quicksort with pivot as last element (sorted) took " << duration.count() << " ms\n";
    if (!checkIfSorted(arrCopy1, numElements)) {
        cout << "Quicksort with pivot as last element failed to sort the sorted array\n";
    }

    // Quicksort with pivot as median element (sorted)
    sortedStart = high_resolution_clock::now();
    quicksortPivotMedian(arrCopy2, numElements);
    sortedEnd = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(sortedEnd - sortedStart);
    cout << "Quicksort with pivot as median element (sorted) took " << duration.count() << " ms\n";
    if (!checkIfSorted(arrCopy2, numElements)) {
        cout << "Quicksort with pivot as median element failed to sort the sorted array\n";
    }

    // Testing reversed array
    reverseTheOrder(arr, numElements);
    std::copy(arr, arr + numElements, arrCopy1);
    std::copy(arr, arr + numElements, arrCopy2);
    auto reversedStart = high_resolution_clock::now();
    heapsort(arr, numElements, d);
    auto reversedEnd = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(reversedEnd - reversedStart);
    cout << "Heapsort with D=" << d << " (reversed) took " << duration.count() << " ms\n";
    if (!checkIfSorted(arr, numElements)) {
        cout << "Heapsort failed to sort the reversed array\n";
    }

    // Quicksort with pivot as last element (reversed)
    reversedStart = high_resolution_clock::now();
    quicksortPivotLast(arrCopy1, numElements);
    reversedEnd = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(reversedEnd - reversedStart);
    cout << "Quicksort with pivot as last element (reversed) took " << duration.count() << " ms\n";
    if (!checkIfSorted(arrCopy1, numElements)) {
        cout << "Quicksort with pivot as last element failed to sort the reversed array\n";
    }

    // Quicksort with pivot as median element (reversed)
    reversedStart = high_resolution_clock::now();
    quicksortPivotMedian(arrCopy2, numElements);
    reversedEnd = high_resolution_clock::now();
    duration = duration_cast<milliseconds>(reversedEnd - reversedStart);
    cout << "Quicksort with pivot as median element (reversed) took " << duration.count() << " ms\n";
    if (!checkIfSorted(arrCopy2, numElements)) {
        cout << "Quicksort with pivot as median element failed to sort the reversed array\n";
    }
}

int main() {
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    const int CAP = 3;
    const int capacities[CAP] = { 100000 }; 
    int randSeed = 0;
    int numElements = 0;
    int* arr = nullptr;
    int* arrCopy1 = nullptr;
    int* arrCopy2 = nullptr;

    for (int i = 0; i < CAP; ++i) {
        numElements = capacities[i];

        // Allocate memory for arrays
        arr = new int[numElements];
        // Copy the original array to arrCopy1 and arrCopy2
        std::copy(arr, arr + numElements, arrCopy1);
        std::copy(arr, arr + numElements, arrCopy2);
        // Seed the random number generator and generate random numbers
        randSeed = rand() % numElements;
        std::cout << "Testing with " << numElements << " elements...\n";
        generateRandomNumbers(arr, numElements, 0, numElements * 2, randSeed);

        // Test sorting algorithms with different numbers of threads
        testSortingAlgorithms(arr, arrCopy1, arrCopy2, numElements, 2);
        testSortingAlgorithms(arr, arrCopy1, arrCopy2, numElements, 4);
        testSortingAlgorithms(arr, arrCopy1, arrCopy2, numElements, 8);

        // Deallocate memory after each test
        delete[] arr;
        delete[] arrCopy1;
        delete[] arrCopy2;
    }

    return 0;
}
