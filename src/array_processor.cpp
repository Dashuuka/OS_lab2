#include "array_processor.h"
#include <algorithm>
#include <numeric>
#include <iostream>
#include <cmath> // For std::round
#include <iomanip> // For std::fixed and std::setprecision

// Initialize static mutex
std::mutex ArrayProcessor::console_mutex;

// Initialize static results
ArrayProcessor::ThreadResults ArrayProcessor::results;

void ArrayProcessor::ValidateArray(const std::vector<int>& arr) {
    if (arr.empty()) {
        throw EmptyArrayException();
    }
}

DWORD WINAPI ArrayProcessor::FindMinMaxThread(LPVOID lpParam) {
    auto* arr = reinterpret_cast<std::vector<int>*>(lpParam);
    int min = (*arr)[0], max = (*arr)[0];

    for (int num : *arr) {
        if (num < min) min = num;
        if (num > max) max = num;
        Sleep(kMinMaxSleepMs);
    }

    {
        std::lock_guard<std::mutex> lock(console_mutex);
        std::cout << "Min: " << min << "\nMax: " << max << std::endl;
    }

    // Save results
    results.min = min;
    results.max = max;
    return 0;
}

DWORD WINAPI ArrayProcessor::CalculateAverageThread(LPVOID lpParam) {
    auto* arr = reinterpret_cast<std::vector<int>*>(lpParam);
    double sum = 0;

    for (int num : *arr) {
        sum += num;
        Sleep(kAverageSleepMs);
    }

    double average = sum / arr->size();
    int roundedAverage = static_cast<int>(std::round(average)); // Round to nearest integer

    {
        std::lock_guard<std::mutex> lock(console_mutex);
        // Print average with 2 decimal places
        std::cout << "Average: " << std::fixed << std::setprecision(2) << average
            << " (rounded to " << roundedAverage << ")" << std::endl;
    }

    // Save results
    results.average = roundedAverage; // Save rounded average
    return 0;
}

void ArrayProcessor::ProcessArray(std::vector<int>& arr) {
    ValidateArray(arr);

    HANDLE hMinMax = CreateThread(nullptr, 0, FindMinMaxThread, &arr, 0, nullptr);
    HANDLE hAverage = CreateThread(nullptr, 0, CalculateAverageThread, &arr, 0, nullptr);

    if (hMinMax == nullptr || hAverage == nullptr) {
        throw std::runtime_error("Failed to create threads");
    }

    WaitForSingleObject(hMinMax, INFINITE);
    WaitForSingleObject(hAverage, INFINITE);

    CloseHandle(hMinMax);
    CloseHandle(hAverage);

    // Replace ALL min and max elements with the rounded average
    for (int& num : arr) {
        if (num == results.min || num == results.max) {
            num = results.average; // Use rounded average
        }
    }
}