#include <iostream>
#include <windows.h>
#include <limits>
#include "thread_data.h"

int main() {
    int n = 0;
    std::cout << "Enter array size: ";
    while (!(std::cin >> n) || n <= 0) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter a positive integer: ";
    }

    int* arr = new(std::nothrow) int[n];
    if (!arr) {
        std::cerr << "Memory allocation failed." << std::endl;
        return 1;
    }

    for (int i = 0; i < n; ++i) {
        std::cout << "Enter element " << i << ": ";
        while (!(std::cin >> arr[i])) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter an integer: ";
        }
    }

    MinMaxData mmData = { arr, n, 0, 0 };
    AverageData avgData = { arr, n, 0.0 };

    HANDLE hMinMax = CreateThread(NULL, 0, MinMaxThreadProc, &mmData, 0, NULL);
    if (!hMinMax) {
        std::cerr << "Failed to create MinMax thread. Error: " << GetLastError() << std::endl;
        delete[] arr;
        return 1;
    }

    HANDLE hAverage = CreateThread(NULL, 0, AverageThreadProc, &avgData, 0, NULL);
    if (!hAverage) {
        std::cerr << "Failed to create Average thread. Error: " << GetLastError() << std::endl;
        CloseHandle(hMinMax);
        delete[] arr;
        return 1;
    }

    WaitForSingleObject(hMinMax, INFINITE);
    WaitForSingleObject(hAverage, INFINITE);

    CloseHandle(hMinMax);
    CloseHandle(hAverage);

    const int avgInt = static_cast<int>(avgData.average);
    for (int i = 0; i < n; ++i) {
        if (arr[i] == mmData.min || arr[i] == mmData.max) {
            arr[i] = avgInt;
        }
    }

    std::cout << "Modified array:";
    for (int i = 0; i < n; ++i) {
        std::cout << " " << arr[i];
    }
    std::cout << std::endl;

    delete[] arr;
    return 0;
}