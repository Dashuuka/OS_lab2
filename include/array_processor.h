#pragma once
#include <vector>
#include <thread>
#include <stdexcept>

class ArrayProcessor {
public:
    static void FindMinMax(const std::vector<int>& arr, int& min, int& max);
    static double CalculateAverage(const std::vector<int>& arr);
    static void ReplaceMinMax(std::vector<int>& arr, double average);

    class EmptyArrayException : public std::runtime_error {
    public:
        EmptyArrayException() : runtime_error("Operation on empty array") {}
    };
};