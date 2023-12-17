#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

struct stats {
    size_t comparison_count = 0;
    size_t copy_count = 0;
};

void generateRandomArray(std::vector<int>& array) {
    for (int& num : array) {
        num = rand();
    }
}

void generateSortedArray(std::vector<int>& array) {
    for (int i = 0; i < array.size(); ++i) {
        array[i] = i;
    }
}

void generateReverseSortedArray(std::vector<int>& array) {
    for (int i = array.size() - 1, j = 0; i >= 0; --i, ++j) {
        array[j] = i;
    }
}

void printStats(const std::string& label, const stats& s, size_t num_trials) {
    std::cout << label << " Comparison Count = " << s.comparison_count / num_trials
        << ", Copy Count = " << s.copy_count / num_trials << std::endl;
}

