#include "array_processor.h"
#include <chrono>
#include <algorithm>

void ArrayProcessor::FindMinMax(const std::vector<int>& arr, int& min, int& max) {
    if (arr.empty()) return;
    auto result = std::minmax_element(arr.begin(), arr.end());
    min = *result.first;
    max = *result.second;
    std::this_thread::sleep_for(std::chrono::milliseconds(7 * (arr.size() - 1)));
}

double ArrayProcessor::CalculateAverage(const std::vector<int>& arr) {
    if (arr.empty()) return 0.0;
    double sum = 0;
    for (int num : arr) {
        sum += num;
        std::this_thread::sleep_for(std::chrono::milliseconds(12));
    }
    return sum / arr.size();
}

void ArrayProcessor::ReplaceMinMax(std::vector<int>& arr, double average) {
    int min, max;
    FindMinMax(arr, min, max);
    for (int& num : arr) {
        if (num == min || num == max) num = static_cast<int>(average);
    }
}