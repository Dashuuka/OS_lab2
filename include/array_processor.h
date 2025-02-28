#pragma once
#include <vector>
#include <windows.h>
#include <stdexcept>
#include <string>
#include <mutex>
#include <cmath> // For std::round
#include <iomanip> // For std::fixed and std::setprecision

class ArrayProcessor {
public:
    // Constants for timeouts
    static constexpr DWORD kMinMaxSleepMs = 7;
    static constexpr DWORD kAverageSleepMs = 12;

    // Exception classes
    class EmptyArrayException : public std::runtime_error {
    public:
        EmptyArrayException() : runtime_error("Operation on empty array") {}
    };

    class InvalidInputException : public std::runtime_error {
    public:
        InvalidInputException(const std::string& message) : runtime_error(message) {}
    };

    // Thread functions
    static DWORD WINAPI FindMinMaxThread(LPVOID lpParam);
    static DWORD WINAPI CalculateAverageThread(LPVOID lpParam);

    // Main functionality
    static void ProcessArray(std::vector<int>& arr);

private:
    // Helper methods
    static void ValidateArray(const std::vector<int>& arr);

    // Mutex for console output synchronization
    static std::mutex console_mutex;

    // Structure to store thread results
    struct ThreadResults {
        int min = 0;
        int max = 0;
        int average = 0; // Store rounded average
    };

    // Static instance to store results
    static ThreadResults results;
};