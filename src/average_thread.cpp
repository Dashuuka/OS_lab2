#include <windows.h>
#include <iostream>
#include "thread_data.h"

#ifndef UNIT_TESTING
#define SLEEP(ms) Sleep(ms)
#else
#define SLEEP(ms)
#endif

DWORD WINAPI AverageThreadProc(LPVOID lpParam) {
    AverageData* data = static_cast<AverageData*>(lpParam);
    if (!data || !data->array || data->size <= 0) {
        std::cerr << "Invalid Average thread data." << std::endl;
        return 1;
    }

    double sum = 0.0;
    for (int i = 0; i < data->size; ++i) {
        sum += data->array[i];
        Sleep(12);
    }

    data->average = sum / data->size;
    std::cout << "Average: " << data->average << std::endl;
    return 0;
}