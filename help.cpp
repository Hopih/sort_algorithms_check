#include "help.h"
#include "sort.h"
#include <iostream>
#include <random>
#include <fstream>
#include <string>
#include <sstream>
#include <chrono>
#include <iomanip>
#include <algorithm>

using namespace std;

void printArray(const vector<int>& arr) {
    for (int value : arr) {
        cout << value << " ";
    }
    cout << endl;
}

vector<int> generateRandomArray(int size) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, 99);
    
    vector<int> result(size);
    for (int i = 0; i < size; i++) {
        result[i] = dist(gen);
    }
    return result;
}

void makePartiallyDisordered(vector<int>& arr, double disorderPercent) {
    int n = arr.size();
    int numSwaps = static_cast<int>(n * disorderPercent / 100.0);
    
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, n - 1);
    
    for (int i = 0; i < numSwaps; i++) {
        swap(arr[dist(gen)], arr[dist(gen)]);
    }
}

void sortBlocks(vector<int>& arr, int blockSize) {
    int n = arr.size();
    int numBlocks = n / blockSize;
    
    for (int i = 0; i < numBlocks; i++) {
        int start = i * blockSize;
        int end = start + blockSize;
        
        vector<int> block(arr.begin() + start, arr.begin() + end);
        long long comp, swp;
        insertionsort(block, comp, swp);
        
        copy(block.begin(), block.end(), arr.begin() + start);
    }
}


bool isSorted(const vector<int>& arr, bool ascending) {
    if (ascending) {
        
        for (size_t i = 0; i < arr.size() - 1; i++) {
            if (arr[i] > arr[i + 1]) {
                return false;
            }
        }
    } else {
        
        for (size_t i = 0; i < arr.size() - 1; i++) {
            if (arr[i] < arr[i + 1]) {
                return false;
            }
        }
    }
    return true;
}

void saveArrayToFile(const vector<int>& arr, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (int value : arr) {
            file << value << "\n"; 
        }
        file.close();
    }
}

vector<int> loadArrayFromFile(const string& filename) {
    ifstream file(filename);
    vector<int> result;
    
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            if (!line.empty()) {
                result.push_back(stoi(line)); 
            }
        }
        file.close();
    }
    return result;
}


void generateAllTestFiles() {
    const int a = 0;
    const int b = 10000;
    
    vector<int> sizes = {100, 1000, 10000, 50000, 100000};
    vector<int> blockSizes = {20, 50, 1000, 2000, 5000};
    
    cout << "Генерация тестовых файлов..." << endl;
    
    // Генерация случайных массивов для типа 'a'
    for (int n : sizes) {
        vector<int> arr = generateRandomArray(n);
        saveArrayToFile(arr, "a" + to_string(n) + ".txt");
    }
    
    // Создание отсортированных версий
    for (int n : sizes) {
        vector<int> arr = loadArrayFromFile("a" + to_string(n) + ".txt");
        
        // b) Отсортированные по возрастанию
        vector<int> b_arr = arr;
        sort(b_arr.begin(), b_arr.end());
        saveArrayToFile(b_arr, "b" + to_string(n) + ".txt");
        
        // c) Отсортированные по убыванию  
        vector<int> c_arr = arr;
        sort(c_arr.rbegin(), c_arr.rend());
        saveArrayToFile(c_arr, "c" + to_string(n) + ".txt");
        
        // d) Частично отсортированные
        vector<int> d_arr = b_arr; 
        makePartiallyDisordered(d_arr, 5.0);
        saveArrayToFile(d_arr, "d" + to_string(n) + ".txt");
        
        // e) Отсортированные блоки
        vector<int> e_arr = arr;
        int blockSize = blockSizes[distance(sizes.begin(), find(sizes.begin(), sizes.end(), n))];
        sortBlocks(e_arr, blockSize);
        saveArrayToFile(e_arr, "e" + to_string(n) + ".txt");
    }
    
    cout << "Все тестовые файлы созданы!" << endl;
}

void initializeTestFiles() {
    generateAllTestFiles();
}


int* loadToDynamicArray(const string& filename, int& size) {
    vector<int> vec = loadArrayFromFile(filename);
    size = vec.size();
    int* arr = new int[size];
    for (int i = 0; i < size; i++) {
        arr[i] = vec[i];
    }
    vec.clear();
    vector<int>().swap(vec);
    return arr;
}



SizeResults testSortingAlgorithms(vector<int>& arr, bool reverse) {
    SizeResults results;
    const int MAX_ATTEMPTS = 100;
    
    
    struct AlgorithmTest {
        string name;
        SortResult* resultPtr;
        function<void(vector<int>&, long long&, long long&)> sortFunc;
    };
    
    // Создаем массив алгоритмов для тестирования
    vector<AlgorithmTest> algorithms = {
        {
            "Selection Sort",
            &results.selection,
            [reverse](vector<int>& a, long long& comp, long long& swaps) {
                if (reverse) {
                    reverseselectionsort(a, comp, swaps);
                } else {
                    selectionsort(a, comp, swaps);
                }
            }
        },
        {
            "Insertion Sort",
            &results.insertion,
            [reverse](vector<int>& a, long long& comp, long long& swaps) {
                if (reverse) {
                    reverseinsertionsort(a, comp, swaps);
                } else {
                    insertionsort(a, comp, swaps);
                }
            }
        },
        {
            "Bubble Sort",
            &results.bubble,
            [reverse](vector<int>& a, long long& comp, long long& swaps) {
                if (reverse) {
                    reversebubblesort(a, comp, swaps);
                } else {
                    bubblesort(a, comp, swaps);
                }
            }
        },
        {
            "Shell Sort",
            &results.shell,
            [reverse](vector<int>& a, long long& comp, long long& swaps) {
                if (reverse) {
                    reverseshell(a, comp, swaps);
                } else {
                    shell(a, comp, swaps);
                }
            }
        }
    };
    
    
    for (auto& algo : algorithms) {
        int attempt = 0;
        bool sorted = false;
        
        while (!sorted && attempt < MAX_ATTEMPTS) {
            attempt++;
            
            
            vector<int> copyArr = arr;
            
            
            algo.resultPtr->comparisons = 0;
            algo.resultPtr->swaps = 0;
            
            
            auto start = chrono::high_resolution_clock::now();
            algo.sortFunc(copyArr, algo.resultPtr->comparisons, algo.resultPtr->swaps);
            auto end = chrono::high_resolution_clock::now();
            
            algo.resultPtr->duration = chrono::duration_cast<chrono::microseconds>(end - start);
            
            
            sorted = isSorted(copyArr, !reverse);
            
            if (!sorted && attempt >= MAX_ATTEMPTS) {
                cout << "ОШИБКА: " << algo.name 
                     << " не отсортировал массив правильно после " 
                     << MAX_ATTEMPTS << " попыток!" << endl;
                algo.resultPtr->comparisons = 0;
                algo.resultPtr->swaps = 0;
                algo.resultPtr->duration = chrono::microseconds(0);
            }
        }
    }
    
   
    int mergeAttempt = 0;
    bool mergeSorted = false;
    
    while (!mergeSorted && mergeAttempt < MAX_ATTEMPTS) {
        mergeAttempt++;
        
        vector<int> copyArr = arr;
        results.merge.comparisons = 0;
        results.merge.swaps = 0;
        
        auto start = chrono::high_resolution_clock::now();
        
        if (reverse) {
            reversemergeSort(copyArr, 0, copyArr.size()-1, 
                           results.merge.comparisons, results.merge.swaps);
        } else {
            mergeSort(copyArr, 0, copyArr.size()-1, 
                     results.merge.comparisons, results.merge.swaps);
        }
        
        auto end = chrono::high_resolution_clock::now();
        results.merge.duration = chrono::duration_cast<chrono::microseconds>(end - start);
        
        mergeSorted = isSorted(copyArr, !reverse);
        
        if (!mergeSorted && mergeAttempt >= MAX_ATTEMPTS) {
            cout << "ОШИБКА: Merge Sort не отсортировал массив правильно после " 
                 << MAX_ATTEMPTS << " попыток!" << endl;
            results.merge.comparisons = 0;
            results.merge.swaps = 0;
            results.merge.duration = chrono::microseconds(0);
        }
    }
    
    return results;
}



SizeResults runMultipleTests(vector<int>& arr, int numTests, bool reverse) {
    SizeResults totalResults;
    vector<SizeResults> allResults(numTests);
    

    for (int i = 0; i < numTests; i++) {
        allResults[i] = testSortingAlgorithms(arr, reverse);
    }
    
    
    auto averageLongLong = [numTests](const vector<long long>& values) { 
        long long sum = 0;
        for (long long value : values) {
            sum += value;
        }
        return sum / numTests;
    };
    
    
    vector<long long> selectionTimes, insertionTimes, bubbleTimes, mergeTimes, shellTimes;
    vector<long long> selectionComps, insertionComps, bubbleComps, mergeComps, shellComps;
    vector<long long> selectionSwaps, insertionSwaps, bubbleSwaps, mergeSwaps, shellSwaps;
    
    for (size_t i = 0; i < allResults.size(); i++) {
        selectionTimes.push_back(allResults[i].selection.duration.count());
        insertionTimes.push_back(allResults[i].insertion.duration.count());
        bubbleTimes.push_back(allResults[i].bubble.duration.count());
        mergeTimes.push_back(allResults[i].merge.duration.count());
        shellTimes.push_back(allResults[i].shell.duration.count());
        
        selectionComps.push_back(allResults[i].selection.comparisons);
        insertionComps.push_back(allResults[i].insertion.comparisons);
        bubbleComps.push_back(allResults[i].bubble.comparisons);
        mergeComps.push_back(allResults[i].merge.comparisons);
        shellComps.push_back(allResults[i].shell.comparisons);
        
        selectionSwaps.push_back(allResults[i].selection.swaps);
        insertionSwaps.push_back(allResults[i].insertion.swaps);
        bubbleSwaps.push_back(allResults[i].bubble.swaps);
        mergeSwaps.push_back(allResults[i].merge.swaps);
        shellSwaps.push_back(allResults[i].shell.swaps);
    }
    
    
    totalResults.selection.duration = chrono::microseconds(averageLongLong(selectionTimes));
    totalResults.insertion.duration = chrono::microseconds(averageLongLong(insertionTimes));
    totalResults.bubble.duration = chrono::microseconds(averageLongLong(bubbleTimes));
    totalResults.merge.duration = chrono::microseconds(averageLongLong(mergeTimes));
    totalResults.shell.duration = chrono::microseconds(averageLongLong(shellTimes));
    
    totalResults.selection.comparisons = averageLongLong(selectionComps);
    totalResults.insertion.comparisons = averageLongLong(insertionComps);
    totalResults.bubble.comparisons = averageLongLong(bubbleComps);
    totalResults.merge.comparisons = averageLongLong(mergeComps);
    totalResults.shell.comparisons = averageLongLong(shellComps);
    
    totalResults.selection.swaps = averageLongLong(selectionSwaps);
    totalResults.insertion.swaps = averageLongLong(insertionSwaps);
    totalResults.bubble.swaps = averageLongLong(bubbleSwaps);
    totalResults.merge.swaps = averageLongLong(mergeSwaps);
    totalResults.shell.swaps = averageLongLong(shellSwaps);
    
    return totalResults;
}

void printResultsToFile(ofstream& file, int arraySize, const string& dataset, 
                       const SizeResults& results) {
    file << "N = " << arraySize << endl;
    file << "Dataset: " << dataset << endl;
    file << "                     Bubble      Insertion      Selection          Shell          Merge " << endl;
    file << "---------------------------------------------------------------------------------------" << endl;
    
    file << "       Время";
    file << "         " << setw(6) << results.bubble.duration.count();
    file << "         " << setw(6) << results.insertion.duration.count();
    file << "         " << setw(6) << results.selection.duration.count();
    file << "         " << setw(6) << results.shell.duration.count();
    file << "         " << setw(6) << results.merge.duration.count();
    file << endl;
    
    file << "   Сравнений";
    file << "     " << setw(10) << results.bubble.comparisons;
    file << "     " << setw(10) << results.insertion.comparisons;
    file << "     " << setw(10) << results.selection.comparisons;
    file << "     " << setw(10) << results.shell.comparisons;
    file << "     " << setw(10) << results.merge.comparisons;
    file << endl;
    
    file << "     Обменов";
    file << "     " << setw(10) << results.bubble.swaps;
    file << "     " << setw(10) << results.insertion.swaps;
    file << "     " << setw(10) << results.selection.swaps;
    file << "     " << setw(10) << results.shell.swaps;
    file << "     " << setw(10) << results.merge.swaps;
    file << endl;
    
    file << "----------------------------------------------------------------------------------------" << endl << endl;
}

void printResultsToConsole(int arraySize, const string& dataset, 
                          const SizeResults& results) {
    cout << "N = " << arraySize << endl;
    cout << "Dataset: " << dataset << endl;
    cout << "                     Bubble      Insertion      Selection          Shell          Merge " << endl;
    cout << "---------------------------------------------------------------------------------------" << endl;
    
    cout << "       Время";
    cout << "         " << setw(6) << results.bubble.duration.count();
    cout << "         " << setw(6) << results.insertion.duration.count();
    cout << "         " << setw(6) << results.selection.duration.count();
    cout << "         " << setw(6) << results.shell.duration.count();
    cout << "         " << setw(6) << results.merge.duration.count();
    cout << endl;
    
    cout << "   Сравнений";
    cout << "     " << setw(10) << results.bubble.comparisons;
    cout << "     " << setw(10) << results.insertion.comparisons;
    cout << "     " << setw(10) << results.selection.comparisons;
    cout << "     " << setw(10) << results.shell.comparisons;
    cout << "     " << setw(10) << results.merge.comparisons;
    cout << endl;
    
    cout << "     Обменов";
    cout << "     " << setw(10) << results.bubble.swaps;
    cout << "     " << setw(10) << results.insertion.swaps;
    cout << "     " << setw(10) << results.selection.swaps;
    cout << "     " << setw(10) << results.shell.swaps;
    cout << "     " << setw(10) << results.merge.swaps;
    cout << endl;
    
    cout << "----------------------------------------------------------------------------------------" << endl << endl;
}




