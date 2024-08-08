#include "Sorting.h"
#include <string>
#include <chrono> // kör dester för tidkomplexiteten
#include <crtdbg.h>
#include <fstream>
#include <iostream>
using namespace std;




template<typename T>
bool checkIfSorted(T arr[], int n)
{
	bool isSorted = true;
	int i;
	for (i = 0; (i < n - 1) && (arr[i] <= arr[i + 1]); i++);
	if (i < n - 1)
		isSorted = false;
	return isSorted;
}

void generateRandomNumbers(int*& arrPtr, int n, int lowerBound, int upperBound, unsigned int seed)
{
	srand(seed);
	arrPtr = new int[n];
	for (int i = 0; i < n; i++)
	{
		arrPtr[i] = rand() % (upperBound - lowerBound + 1) + lowerBound;
	}
}
template<typename T>
void reverseTheOrder(T arr[], int n)
{
	for (int i = 0; i < n / 2; i++)
	{
		std::swap(arr[i], arr[n - 1 - i]);
	}
}

const int CAP = 3;
const int capacity[CAP]{ 10, 100, 500 };

void testSortingZeroElements()
{
	std::string e;

	int oneElement[]{ 0 };
	try
	{
		quicksortPivotLast(oneElement, 0);
	}
	catch (std::exception ex)
	{
		e += "Quicksort with pivot as last element did not work for zero elements\n";
	}
	try
	{
		quicksortPivotMedian(oneElement, 0);
	}
	catch (std::exception ex)
	{
		e += "Quicksort with pivot as median element did not work for zero elements\n";
	}
	try
	{
		heapsort(oneElement, 0, 2);
		heapsort(oneElement, 0, 4);
	}
	catch (std::exception ex)
	{
		e += "Heapsort did not work for zero elements";
	}
	if (e != "")
	{
		throw e;
	}
}
void testOneElementList()
{
	std::string e;
	int oneElement[]{ 0 };
	try
	{
		quicksortPivotLast(oneElement, 1);

	}
	catch (std::exception ex)
	{
		e += "Quicksort with pivot as last element did not work one element\n";
	}
	try
	{
		quicksortPivotMedian(oneElement, 1);

	}
	catch (std::exception ex)
	{
		e += "Quicksort with pivot as median element did not work for one element";
	}
	try
	{
		heapsort(oneElement, 1, 2);
		heapsort(oneElement, 1, 4);

	}
	catch (std::exception ex)
	{
		e += "Heapsort did not work for one element";
	}
	if (e != "")
	{
		throw e;
	}
}
template<typename T>
void printArray(const T array[], int size) {
	for (int i = 0; i < size; ++i) {
		std::cout << array[i] << " ";
	}
	std::cout << std::endl;
}

void testingQuicksortPivotLAst(int randSeed)
{
	std::string e;
	int* arr = nullptr;
	for (int i = 0; i < CAP; i++)
	{
		generateRandomNumbers(arr, capacity[i], 0, capacity[i] * 2, randSeed);
		auto start = std::chrono::high_resolution_clock::now();
		quicksortPivotLast(arr, capacity[i]);
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed = end - start;
		std::cout << "Quicksort with pivot as last element (random, n=" << capacity[i] << ") took " << elapsed.count() << " seconds\n";

		if (!checkIfSorted(arr, capacity[i]))
		{
			e += "Quicksort with pivot as last element did not sort " + std::to_string(capacity[i]) + " random elements\n";
		}

		quicksortPivotLast(arr, capacity[i]);
		if (!checkIfSorted(arr, capacity[i]))
		{
			e += "Quicksort with pivot as last element did not sort " + std::to_string(capacity[i]) + " ordered elements\n";
		}

		reverseTheOrder(arr, capacity[i]);
		start = std::chrono::high_resolution_clock::now();
		quicksortPivotLast(arr, capacity[i]);
		end = std::chrono::high_resolution_clock::now();
		elapsed = end - start;
		std::cout << "Quicksort with pivot as last element (reversed, n=" << capacity[i] << ") took " << elapsed.count() << " seconds\n";

		if (!checkIfSorted(arr, capacity[i]))
		{
			e += "Quicksort with pivot as last element did not sort " + std::to_string(capacity[i]) + " reversed ordered elements";
		}

	}
	delete[] arr;
	if (e != "")
		throw e;
}

void testingQuicksortPivotMedian(int randSeed)
{
	std::string e;
	int* arr = nullptr;
	for (int i = 0; i < CAP; i++)
	{
		generateRandomNumbers(arr, capacity[i], 0, capacity[i] * 2, randSeed);
		auto start = std::chrono::high_resolution_clock::now();
		quicksortPivotMedian(arr, capacity[i]);
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed = end - start;
		std::cout << "Quicksort with pivot as median element (random, n=" << capacity[i] << ") took " << elapsed.count() << " seconds\n";

		if (!checkIfSorted(arr, capacity[i]))
		{
			e += "Quicksort with pivot as median element did not sort " + std::to_string(capacity[i]) + " random elements\n";
			printArray(arr, capacity[i]);
		}

		quicksortPivotMedian(arr, capacity[i]);
		if (!checkIfSorted(arr, capacity[i]))
		{
			e += "Quicksort with pivot as median element did not sort " + std::to_string(capacity[i]) + " ordered elements\n";
			printArray(arr, capacity[i]);
		}


		reverseTheOrder(arr, capacity[i]);
		start = std::chrono::high_resolution_clock::now();
		quicksortPivotMedian(arr, capacity[i]);
		end = std::chrono::high_resolution_clock::now();
		elapsed = end - start;
		std::cout << "Quicksort with pivot as median element (reversed, n=" << capacity[i] << ") took " << elapsed.count() << " seconds\n";

		if (!checkIfSorted(arr, capacity[i]))
		{
			e += "Quicksort with pivot as median element did not sort " + std::to_string(capacity[i]) + " reversed ordered elements";
			printArray(arr, capacity[i]);
		}
	}
	delete[] arr;
	if (e != "")
		throw e;
}

void testingHeapsort(int D, int randSeed)
{
	std::string e;
	int* arr = nullptr;
	const int numElements = 10; // Set the number of elements to 10

	generateRandomNumbers(arr, numElements, 0, numElements * 2, randSeed);

	auto start = std::chrono::high_resolution_clock::now();
	heapsort(arr, numElements, D);
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = end - start;
	std::cout << "Heapsort with D=" << D << " (random, n=" << numElements << ") took " << elapsed.count() << " seconds\n";

	if (!checkIfSorted(arr, numElements))
	{
		e += "Heapsort with D=" + std::to_string(D) + " did not sort " + std::to_string(numElements) + " random elements\n";
	}

	// Sorting an already sorted array
	heapsort(arr, numElements, D);
	if (!checkIfSorted(arr, numElements))
	{
		e += "Heapsort with D=" + std::to_string(D) + " did not sort " + std::to_string(numElements) + " ordered elements\n";
	}

	// Sorting a reversed array
	reverseTheOrder(arr, numElements);
	start = std::chrono::high_resolution_clock::now();
	heapsort(arr, numElements, D);
	end = std::chrono::high_resolution_clock::now();
	elapsed = end - start;
	std::cout << "Heapsort with D=" << D << " (reversed, n=" << numElements << ") took " << elapsed.count() << " seconds\n";

	if (!checkIfSorted(arr, numElements))
	{
		e += "Heapsort with D=" + std::to_string(D) + " did not sort " + std::to_string(numElements) + " reversed ordered elements\n";
	}

	delete[] arr;

	if (e != "")
	{
		throw e;
	}
}


int main()
{
	bool testOk = true;
	try
	{
		testSortingZeroElements();
	}
	catch (std::string e)
	{
		std::cout << "Exception: " << e << std::endl;
		testOk = false;
	}
	try
	{
		testOneElementList();
	}
	catch (std::string e)
	{
		std::cout << "Exception: " << e << std::endl;
		testOk = false;
	}
	int randSeed = 0;

	for (int i = 0; i < CAP; i++)
	{
		randSeed = rand() % 1000;
		try
		{
			testingQuicksortPivotLAst(randSeed);
			testingQuicksortPivotMedian(randSeed);
			testingHeapsort(2, randSeed);
			testingHeapsort(4, randSeed);
			testingHeapsort(3, randSeed);
			testingHeapsort(3, randSeed);

			testingHeapsort(5, randSeed);

			testingHeapsort(6, randSeed);

			testingHeapsort(11, randSeed);

			testingHeapsort(8, randSeed);

			testingHeapsort(9, randSeed);
			
			testingHeapsort(7, randSeed);
			
			testingHeapsort(13, randSeed);



		}
		catch (std::string e)
		{
			std::cout << "Exception: " << e << std::endl;
			testOk = false;
	}
	}
	int ok = 0;
	if (testOk)
		std::cout << "Test ok" << std::endl;
	else
	{
		ok = 1;
		std::cout << "Test NOT ok" << std::endl;
	}
	return ok;
}

// int main() {

// 	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
// 	int* arr1 = new int[1000];
// 	int* arr2 = new int[1000];

// 	int c = 0;
// 	// if (std::ifstream in{ "Testdata/1000(0,1000).txt" })
// 	// {
// 	// 	std::string word;
// 	// 	while (in >> word)
// 	// 	{
// 	// 		arr1[c] = stoi(word);

// 	// 		c++;
// 	// 	}
// 	// }
// 	// else
// 	// {
// 	// 	std::cout << "couldn't open file" << endl;
// 	// }
// 	for (int i = 1000; i > 0; i--) {
// 		arr1[c] = 1000 - c;
// 		arr2[c] = 1000 - i + 1;
// 		c++;
// 	}
// 	heapsort(arr1, c, 7);

// 	//quicksortPivotLast(arr2, c);
// 	//quicksortPivotMedian(arr3, c);

// 	// Check if the array is not null before accessing it
// 	if (arr1 != nullptr) {
// 		for (int i = 0; i < 1000; i++) {  // Note the change here to prevent accessing arr1 out of bounds
// 			if (arr1[i] != arr2[i])
// 				cout << arr1[i] << " " << arr2[i] << '\n';  // Corrected string concatenation
// 		}
// 	}
// 	else {
// 		cout << "Array is null" << endl;
// 	}

// 	delete[] arr1;

// 	return 0;
// }
