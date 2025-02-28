#include <windows.h>
#include <iostream>
#include "thread_data.h"

DWORD WINAPI MinMaxThreadProc(LPVOID lpParam) {
    MinMaxData* data = static_cast<MinMaxData*>(lpParam);
    if (!data || !data->array || data->size <= 0) {
        std::cerr << "Invalid MinMax thread data." << std::endl;
        return 1;
    }

    data->min = data->array[0];
    data->max = data->array[0];

    for (int i = 1; i < data->size; ++i) {
        if (data->array[i] < data->min) {
            data->min = data->array[i];
        }
        Sleep(7);

        if (data->array[i] > data->max) {
            data->max = data->array[i];
        }
        Sleep(7);
    }

    std::cout << "Min: " << data->min << ", Max: " << data->max << std::endl;
    return 0;
}