#include <iostream>
#include <fstream>
#include <iomanip>
#include "sort.h"
#include "help.h"
#include <chrono>

using namespace std;

struct FileArray {
    int* data = nullptr;  
    int size = 0;         
};

int main() {
    ofstream resultFile("results.txt");
    
    initializeTestFiles();

    FileArray arrays[12];
    
    string filenames[12] = {
        "a1000.txt", "a50000.txt", "a100000.txt",
        "c1000.txt", "c50000.txt", "c100000.txt",
        "d1000.txt", "d50000.txt", "d100000.txt",
        "e1000.txt", "e50000.txt", "e100000.txt"
    };
    
    for (int i = 0; i < 12; i++) {
        arrays[i].data = loadToDynamicArray(filenames[i], arrays[i].size);
    }
    cout << endl;
    
    // ТЕСТ 1: Равномерное распределение (массивы 'a')
    cout << "=== Testing Uniform Distribution ===" << endl;
    vector<int> smallVec(arrays[0].data, arrays[0].data + arrays[0].size);
    vector<int> mediumVec(arrays[1].data, arrays[1].data + arrays[1].size);
    vector<int> largeVec(arrays[2].data, arrays[2].data + arrays[2].size);
    
    SizeResults smallUniform = runMultipleTests(smallVec);
    SizeResults mediumUniform = runMultipleTests(mediumVec);
    SizeResults largeUniform = runMultipleTests(largeVec);
    
    printResultsToFile(resultFile, SMALL, "равномерное распределение", smallUniform);
    printResultsToFile(resultFile, MEDIUM, "равномерное распределение", mediumUniform);
    printResultsToFile(resultFile, LARGE, "равномерное распределение", largeUniform);
    
    printResultsToConsole(SMALL, "равномерное распределение", smallUniform);
    printResultsToConsole(MEDIUM, "равномерное распределение", mediumUniform);
    printResultsToConsole(LARGE, "равномерное распределение", largeUniform);
    
   
    cout << "=== Testing Same Array but Sort DESCENDING ===" << endl;

    vector<int> smallReverse(arrays[0].data, arrays[0].data + arrays[0].size);   // a1000.txt
    vector<int> mediumReverse(arrays[1].data, arrays[1].data + arrays[1].size);  // a50000.txt
    vector<int> largeReverse(arrays[2].data, arrays[2].data + arrays[2].size);   // a100000.txt

    SizeResults smallReverseResults = runMultipleTests(smallReverse, 10, true);
    SizeResults mediumReverseResults = runMultipleTests(mediumReverse, 10, true);
    SizeResults largeReverseResults = runMultipleTests(largeReverse, 10, true);

    
    printResultsToFile(resultFile, SMALL, "равномерное распределение, сортировка по убыванию", smallReverseResults);
    printResultsToFile(resultFile, MEDIUM, "равномерное распределение, сортировка по убыванию", mediumReverseResults);
    printResultsToFile(resultFile, LARGE, "равномерное распределение, сортировка по убыванию", largeReverseResults);

    printResultsToConsole(SMALL, "равномерное распределение, сортировка по убыванию", smallReverseResults);
    printResultsToConsole(MEDIUM, "равномерное распределение, сортировка по убыванию", mediumReverseResults);
    printResultsToConsole(LARGE, "равномерное распределение, сортировка по убыванию", largeReverseResults);
    
    // ТЕСТ 3: Частично отсортированные (массивы 'd')
    cout << "=== Testing Partially Sorted (95%) ===" << endl;
    vector<int> smallPartial(arrays[6].data, arrays[6].data + arrays[6].size);
    vector<int> mediumPartial(arrays[7].data, arrays[7].data + arrays[7].size);
    vector<int> largePartial(arrays[8].data, arrays[8].data + arrays[8].size);
    
    SizeResults smallPartialResults = runMultipleTests(smallPartial);
    SizeResults mediumPartialResults = runMultipleTests(mediumPartial);
    SizeResults largePartialResults = runMultipleTests(largePartial);
    
    printResultsToFile(resultFile, SMALL, "частично отсортированные (95%)", smallPartialResults);
    printResultsToFile(resultFile, MEDIUM, "частично отсортированные (95%)", mediumPartialResults);
    printResultsToFile(resultFile, LARGE, "частично отсортированные (95%)", largePartialResults);
    
    printResultsToConsole(SMALL, "частично отсортированные (95%)", smallPartialResults);
    printResultsToConsole(MEDIUM, "частично отсортированные (95%)", mediumPartialResults);
    printResultsToConsole(LARGE, "частично отсортированные (95%)", largePartialResults);
    
    // ТЕСТ 4: Отсортированные блоки (массивы 'e')
    cout << "=== Testing Sorted Blocks ===" << endl;
    vector<int> smallBlocks(arrays[9].data, arrays[9].data + arrays[9].size);
    vector<int> mediumBlocks(arrays[10].data, arrays[10].data + arrays[10].size);
    vector<int> largeBlocks(arrays[11].data, arrays[11].data + arrays[11].size);
    
    SizeResults smallBlocksResults = runMultipleTests(smallBlocks);
    SizeResults mediumBlocksResults = runMultipleTests(mediumBlocks);
    SizeResults largeBlocksResults = runMultipleTests(largeBlocks);
    
    printResultsToFile(resultFile, SMALL, "отсортированные блоки", smallBlocksResults);
    printResultsToFile(resultFile, MEDIUM, "отсортированные блоки", mediumBlocksResults);
    printResultsToFile(resultFile, LARGE, "отсортированные блоки", largeBlocksResults);
    
    printResultsToConsole(SMALL, "отсортированные блоки", smallBlocksResults);
    printResultsToConsole(MEDIUM, "отсортированные блоки", mediumBlocksResults);
    printResultsToConsole(LARGE, "отсортированные блоки", largeBlocksResults);
    
    
    for (int i = 0; i < 12; i++) {
        if (arrays[i].data != nullptr) {
            delete[] arrays[i].data;
            arrays[i].data = nullptr;
            arrays[i].size = 0;
        }
    }
    
    resultFile.close();
    cout << "All tests completed successfully! Memory cleaned." << endl;
    
    return 0;
}







