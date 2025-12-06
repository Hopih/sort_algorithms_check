#ifndef SORT_ALGORITHMS_H
#define SORT_ALGORITHMS_H

#include <vector>

using namespace std;

void insertionsort(vector<int>&arr,long long &comparisons, long long &swaps);

void selectionsort(vector<int> &arr,long long &comparisons, long long &swaps);

void bubblesort(vector<int> &arr,long long &comparisons, long long &swaps);

void mergeSort(vector<int> &arr,int left,int right,long long &comparisons, long long &swaps);

void shell(vector<int> &arr,long long &comparisons, long long &swaps);

void reverseinsertionsort(vector<int>&arr,long long &comparisons, long long &swaps);

void reverseselectionsort(vector<int> &arr,long long &comparisons, long long &swaps);

void reversebubblesort(vector<int> &arr,long long &comparisons, long long &swaps);

void reversemergeSort(vector<int> &arr,int left,int right,long long &comparisons, long long &swaps);

void reverseshell(vector<int> &arr,long long &comparisons, long long &swaps);


#endif






