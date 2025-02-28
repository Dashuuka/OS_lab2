#include <gtest/gtest.h>
#include "array_processor.h"

TEST(ArrayProcessorTest, MinMaxCalculation) {
    std::vector<int> arr = { 5, 3, 7, 1, 9 };
    int min, max;
    ArrayProcessor::FindMinMax(arr, min, max);
    EXPECT_EQ(min, 1);
    EXPECT_EQ(max, 9);
}

TEST(ArrayProcessorTest, AverageCalculation) {
    std::vector<int> arr = { 2, 4, 6, 8 };
    EXPECT_DOUBLE_EQ(ArrayProcessor::CalculateAverage(arr), 5.0);
}

TEST(ArrayProcessorTest, ReplaceLogic) {
    std::vector<int> arr = { 1, 5, 3, 5, 1 };
    ArrayProcessor::ReplaceMinMax(arr, 3.0);
    std::vector<int> expected = { 3, 3, 3, 3, 3 };
    EXPECT_EQ(arr, expected);
}