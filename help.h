#ifndef SUPPORT_H
#define SUPPORT_H

#include <vector>
#include <iostream>
#include <chrono>
#include <fstream>
#include <string>
#include <functional>  

using namespace std;


using SortFunction = function<void(vector<int>&, long long&, long long&)>;

enum ArraySize { SMALL = 1000, MEDIUM = 50000, LARGE = 100000 };


struct SortResult {
    chrono::microseconds duration;
    long long comparisons;
    long long swaps;
};


struct SizeResults {
    SortResult selection;
    SortResult insertion;
    SortResult bubble;
    SortResult merge;
    SortResult shell;
};


void printArray(const vector<int>& arr);
vector<int> generateRandomArray(int size);
void makePartiallyDisordered(vector<int>& arr, double disorderPercent = 5.0);
void sortBlocks(vector<int>& arr, int blockSize);
bool isSorted(const vector<int>& arr, bool ascending = true);  // ИЗМЕНИТЬ эту строку!

void saveArrayToFile(const vector<int>& arr, const string& filename);
vector<int> loadArrayFromFile(const string& filename);
void initializeTestFiles();
void generateAllTestFiles(); 

SizeResults testSortingAlgorithms(vector<int>& arr, bool reverse = false);
SizeResults runMultipleTests(vector<int>& arr, int numTests = 10, bool reverse = false);

void printResultsToFile(ofstream& file, int arraySize, const string& dataset, 
                       const SizeResults& results);
void printResultsToConsole(int arraySize, const string& dataset, 
                          const SizeResults& results);


int* loadToDynamicArray(const string& filename, int& size);

#endif
