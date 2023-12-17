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
                comparisons += 2;
                array[j] = array[j - gap];
                j -= gap;
            }

            if (j >= gap) {
                comparisons += 1;
            }

            statistics.comparison_count += comparisons;
            array[j] = temp;
            ++statistics.copy_count;
        }
    }
}




void heapify(std::vector<int>& array, size_t n, size_t i, stats& statistics) {
    size_t largest = i;
    size_t left = 2 * i + 1;
    size_t right = 2 * i + 2;

    if (left < n && array[left] > array[largest]) {
        ++statistics.comparison_count;
        largest = left;
    }

    if (right < n && array[right] > array[largest]) {
        ++statistics.comparison_count;
        largest = right;
    }

    if (largest != i) {
        int temp = array[i];
        array[i] = array[largest];
        array[largest] = temp;
        statistics.copy_count += 3;
        heapify(array, n, largest, statistics);
    }
}

void heapSort(std::vector<int>& array, stats& statistics) {
    for (int i = array.size() / 2 - 1; i >= 0; --i) {
        heapify(array, array.size(), i, statistics);
    }

    for (int i = array.size() - 1; i > 0; --i) {
        int temp = array[0];
        array[0] = array[i];
        array[i] = temp;
        statistics.copy_count += 3;
        heapify(array, i, 0, statistics);
    }
}

int main() {
    srand(static_cast<unsigned int>(time(0)));

    size_t array_lengths[] = { 1000, 2000, 3000, 10000, 25000, 50000 };
    size_t num_trials = 100;

    for (size_t i = 0; i < sizeof(array_lengths) / sizeof(array_lengths[0]); ++i) {
        size_t length = array_lengths[i];

        std::cout << "Array Length: " << length << std::endl;

        // Random Array
        std::vector<int> random_array(length);

        stats insertion_stats_random, shell_stats_random, heap_stats_random;
        for (size_t trial = 0; trial < num_trials; ++trial) {
            generateRandomArray(random_array);
            insertionSort(random_array, insertion_stats_random);
            shellSort(random_array, shell_stats_random);
            heapSort(random_array, heap_stats_random);
        }

        printStats("Random Array - Insertion Sort", insertion_stats_random, num_trials);
        printStats("Random Array - Shell Sort", shell_stats_random, num_trials);
        printStats("Random Array - Heap Sort", heap_stats_random, num_trials);

        // Sorted Array
        std::vector<int> sorted_array(length);

        stats insertion_stats_sorted, shell_stats_sorted, heap_stats_sorted;
        for (size_t trial = 0; trial < num_trials; ++trial) {
            generateSortedArray(sorted_array);
            insertionSort(sorted_array, insertion_stats_sorted);
            shellSort(sorted_array, shell_stats_sorted);
            heapSort(sorted_array, heap_stats_sorted);
        }

        printStats("Sorted Array - Insertion Sort", insertion_stats_sorted, num_trials);
        printStats("Sorted Array - Shell Sort", shell_stats_sorted, num_trials);
        printStats("Sorted Array - Heap Sort", heap_stats_sorted, num_trials);

        // Reverse Sorted Array
        std::vector<int> reverse_sorted_array(length);

        stats insertion_stats_reverse_sorted, shell_stats_reverse_sorted, heap_stats_reverse_sorted;
        for (size_t trial = 0; trial < num_trials; ++trial) {
            generateReverseSortedArray(reverse_sorted_array);
            insertionSort(reverse_sorted_array, insertion_stats_reverse_sorted);
            shellSort(reverse_sorted_array, shell_stats_reverse_sorted);
            heapSort(reverse_sorted_array, heap_stats_reverse_sorted);
        }

        printStats("Reverse Sorted Array - Insertion Sort", insertion_stats_reverse_sorted, num_trials);
        printStats("Reverse Sorted Array - Shell Sort", shell_stats_reverse_sorted, num_trials);
        printStats("Reverse Sorted Array - Heap Sort", heap_stats_reverse_sorted, num_trials);

        std::cout << std::endl;
    }

    return 0;
}