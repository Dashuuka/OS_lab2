#pragma once
#include <vector>
#include <thread>

class ArrayProcessor {
public:
    static void FindMinMax(const std::vector<int>& arr, int& min, int& max);
    static double CalculateAverage(const std::vector<int>& arr);
    static void ReplaceMinMax(std::vector<int>& arr, double average);
};