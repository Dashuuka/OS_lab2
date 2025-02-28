#include "array_processor.h"
#include <iostream>
#include <vector>

int main() {
    std::vector<int> arr;
    int size;

    std::cout << "Enter array size: ";
    std::cin >> size;

    arr.resize(size);
    for (auto& item : arr) {
        std::cout << "Enter number: ";
        std::cin >> item;
    }

    int min, max;
    double average;

    std::thread minmax_thread([&] {
        ArrayProcessor::FindMinMax(arr, min, max);
        std::cout << "Min: " << min << "\nMax: " << max << std::endl;
        });

    std::thread average_thread([&] {
        average = ArrayProcessor::CalculateAverage(arr);
        std::cout << "Average: " << average << std::endl;
        });

    minmax_thread.join();
    average_thread.join();

    ArrayProcessor::ReplaceMinMax(arr, average);

    std::cout << "Result array: ";
    for (auto num : arr) std::cout << num << " ";

    return 0;
}