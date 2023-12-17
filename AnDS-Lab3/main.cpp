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

void insertionSort(std::vector<int>& array, stats& statistics) {
    for (size_t i = 1; i < array.size(); ++i) {
        int key = array[i];
        size_t j = i;

        while (j > 0 && array[j - 1] > key) {
            ++statistics.comparison_count;
            array[j] = array[j - 1];
            ++statistics.copy_count;
            --j;
        }

        if (j > 0) {
            ++statistics.comparison_count;
        }

        array[j] = key;
        ++statistics.copy_count;
    }
}

void shellSort(std::vector<int>& array, stats& statistics) {
    for (size_t gap = array.size() / 2; gap > 0; gap /= 2) {
        for (size_t i = gap; i < array.size(); ++i) {
            int temp = array[i];
            size_t j = i;
            size_t comparisons = 0;

            while (j >= gap && array[j - gap] > temp) {
                comparisons += 2; // Учитываем сравнение и условие внутри while
                array[j] = array[j - gap];
                j -= gap;
            }

            if (j >= gap) {
                comparisons += 1; // Учитываем сравнение с последним элементом в интервале
            }

            statistics.comparison_count += comparisons;
            array[j] = temp;
            ++statistics.copy_count;
        }
    }
}



