#include <gtest/gtest.h>
#include "thread_data.h"

// Mock Sleep to avoid delays in tests
void Sleep(DWORD) {}

TEST(MinMaxTest, BasicTest) {
    int arr[] = { 3, 1, 4, 1, 5 };
    MinMaxData data = { arr, 5, 0, 0 };
    EXPECT_EQ(0, MinMaxThreadProc(&data));
    EXPECT_EQ(1, data.min);
    EXPECT_EQ(5, data.max);
}

TEST(AverageTest, BasicTest) {
    int arr[] = { 1, 2, 3, 4, 5 };
    AverageData data = { arr, 5, 0.0 };
    EXPECT_EQ(0, AverageThreadProc(&data));
    EXPECT_DOUBLE_EQ(3.0, data.average);
}

TEST(MinMaxTest, SingleElement) {
    int arr[] = { 42 };
    MinMaxData data = { arr, 1, 0, 0 };
    EXPECT_EQ(0, MinMaxThreadProc(&data));
    EXPECT_EQ(42, data.min);
    EXPECT_EQ(42, data.max);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}