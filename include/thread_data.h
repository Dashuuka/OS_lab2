#ifndef THREAD_DATA_H
#define THREAD_DATA_H

#include <windows.h>
#include <iostream>

struct MinMaxData {
    int* array;
    int size;
    int min;
    int max;
};

struct AverageData {
    int* array;
    int size;
    double average;
};

DWORD WINAPI MinMaxThreadProc(LPVOID lpParam);
DWORD WINAPI AverageThreadProc(LPVOID lpParam);

#endif // THREAD_DATA_H