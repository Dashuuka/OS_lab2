#include "array_processor.h"
#include <chrono>
#include <algorithm>
#include <numeric>

void ArrayProcessor::FindMinMax(const std::vector<int>& arr, int& min, int& max) {
    if (arr.empty())
        throw EmptyArrayException();

    auto [min_it, max_it] = std::minmax_element(arr.begin(), arr.end());
    min = *min_it;
    max = *max_it;

    std::this_thread::sleep_for(std::chrono::milliseconds(7 * (arr.size() - 1)));
}

double ArrayProcessor::CalculateAverage(const std::vector<int>& arr) {
    if (arr.empty())
        throw EmptyArrayException();

    double sum = std::accumulate(arr.begin(), arr.end(), 0.0,
        [](double acc, int val) {
            std::this_thread::sleep_for(std::chrono::milliseconds(12));
            return acc + val;
        });

    return sum / arr.size();
}

void ArrayProcessor::ReplaceMinMax(std::vector<int>& arr, double average) {
    if (arr.empty()) return;

    int min, max;
    FindMinMax(arr, min, max);

    for (auto& num : arr) {
        if (num == min || num == max)
            num = static_cast<int>(average);
    }
}