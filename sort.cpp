#include "sort.h"
#include <cmath>

void selectionsort(vector<int> &arr, long long &comparisons, long long &swaps){
    comparisons = 0;
    swaps = 0;
    int n=arr.size();
    for (int i=0;i<n-1;i++){
        int index=i;
        for (int k=i+1;k<n;k++){
            comparisons++;
            if (arr[k]<arr[index]){
                index=k;   
            }
        }
        if (index!=i){
            swaps++;
            swap(arr[i],arr[index]);
        }
    }
}   

void insertionsort(vector<int> &arr, long long &comparisons, long long &swaps){
    comparisons = 0;
    swaps = 0;
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0) {
            comparisons++;
            if (arr[j] > key) {
                swaps++;
                arr[j + 1] = arr[j];
                j--;
            } else {
                break;
            }
        }
        arr[j + 1] = key;
    }
}

void bubblesort(vector<int> &arr, long long &comparisons, long long &swaps){
    comparisons = 0;
    swaps = 0;
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {
                swaps++;
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

void mergeSort(vector<int>& arr, int left, int right, long long &comparisons, long long &swaps) {
    if (left >= right) return;
    
    int mid = left + (right - left) / 2;
    
    mergeSort(arr, left, mid, comparisons, swaps);
    mergeSort(arr, mid + 1, right, comparisons, swaps);
    
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    vector<int> leftArr(n1), rightArr(n2);
    
    for (int i = 0; i < n1; i++) {
        swaps++;
        leftArr[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        swaps++;
        rightArr[j] = arr[mid + 1 + j];
    }
    
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        comparisons++;
        if (leftArr[i] <= rightArr[j]) {
            swaps++;
            arr[k] = leftArr[i];
            i++;
        } else {
            swaps++;
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        swaps++;
        arr[k] = leftArr[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        swaps++;
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

void shell(vector<int>& arr, long long &comparisons, long long &swaps) {
    comparisons = 0;
    swaps = 0;
    int n = arr.size();
    
    static const vector<int> gaps = {
        29524, 9841, 3280, 1093, 364, 121, 40, 13, 4, 1
    };
    
    for (int d : gaps) {
        if (d < n) {
            for (int i = d; i < n; i++) {
                int temp = arr[i];
                int j = i;
                while (j >= d) {
                    comparisons++;
                    if (arr[j - d] > temp) {
                        swaps++;
                        arr[j] = arr[j - d];
                        j -= d;
                    } else {
                        break;
                    }
                }
                swaps++;
                arr[j] = temp;
            }
        }
    }
}

void reverseselectionsort(vector<int> &arr, long long &comparisons, long long &swaps){
    comparisons = 0;
    swaps = 0;
    int n=arr.size();
    for (int i=0;i<n-1;i++){
        int index=i;
        for (int k=i+1;k<n;k++){
            comparisons++;
            if (arr[k]>arr[index]){
                index=k;   
            }
        }
        if (index!=i){
            swaps++;
            swap(arr[i],arr[index]);
        }
    }
}

void reverseinsertionsort(vector<int> &arr, long long &comparisons, long long &swaps){
    comparisons = 0;
    swaps = 0;
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0) {
            comparisons++;
            if (arr[j] < key) {
                swaps++;
                arr[j + 1] = arr[j];
                j--;
            } else {
                break;
            }
        }
        arr[j + 1] = key;
    }
}

void reversebubblesort(vector<int> &arr, long long &comparisons, long long &swaps){
    comparisons = 0;
    swaps = 0;
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            comparisons++;
            if (arr[j] < arr[j + 1]) {
                swaps++;
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

void reversemergeSort(vector<int>& arr, int left, int right, long long &comparisons, long long &swaps) {
    if (left >= right) return;
    
    int mid = left + (right - left) / 2;
    
    reversemergeSort(arr, left, mid, comparisons, swaps);
    reversemergeSort(arr, mid + 1, right, comparisons, swaps);
    
    int n1 = mid - left + 1; 
    int n2 = right - mid;
    
    vector<int> leftArr(n1), rightArr(n2);
    
    for (int i = 0; i < n1; i++) {
        swaps++;
        leftArr[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        swaps++;
        rightArr[j] = arr[mid + 1 + j];
    }
    
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        comparisons++;
        if (leftArr[i] >= rightArr[j]) {
            swaps++;
            arr[k] = leftArr[i];
            i++;
        } else {
            swaps++;
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        swaps++;
        arr[k] = leftArr[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        swaps++;
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

void reverseshell(vector<int>& arr, long long &comparisons, long long &swaps) {
    comparisons = 0;
    swaps = 0;
    int n = arr.size();

    static const vector<int> gaps = {
        8929, 3905, 2161, 929, 505, 209, 109, 41, 19, 5, 1
    };
    
    for (int d : gaps) {
        if (d < n) {
            for (int i = d; i < n; i++) {
                int temp = arr[i];
                int j = i;
                while (j >= d) {
                    comparisons++;
                    if (arr[j - d] < temp) {  
                        swaps++;
                        arr[j] = arr[j - d];
                        j -= d;
                    } else {
                        break;
                    }
                }
                swaps++;
                arr[j] = temp;
            }
        }
    }
    
}














































































































