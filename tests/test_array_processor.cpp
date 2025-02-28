#include <gtest/gtest.h>
#include "array_processor.h"
#include <vector>
#include <stdexcept>

TEST(ArrayProcessorTest, ThrowsOnEmptyArrayForMinMax) {
    std::vector<int> empty;
    int min, max;
    EXPECT_THROW(ArrayProcessor::FindMinMax(empty, min, max),
        ArrayProcessor::EmptyArrayException);
}

TEST(ArrayProcessorTest, ThrowsOnEmptyArrayForAverage) {
    std::vector<int> empty;
    EXPECT_THROW(ArrayProcessor::CalculateAverage(empty),
        ArrayProcessor::EmptyArrayException);
}

TEST(ArrayProcessorTest, SingleElementArray) {
    std::vector<int> arr = { 5 };
    int min, max;
    ArrayProcessor::FindMinMax(arr, min, max);
    EXPECT_EQ(min, 5);
    EXPECT_EQ(max, 5);
    EXPECT_DOUBLE_EQ(ArrayProcessor::CalculateAverage(arr), 5.0);
}

TEST(ArrayProcessorTest, NegativeNumbersHandling) {
    std::vector<int> arr = { -5, -3, -7 };
    int min, max;
    ArrayProcessor::FindMinMax(arr, min, max);
    EXPECT_EQ(min, -7);
    EXPECT_EQ(max, -3);
    EXPECT_DOUBLE_EQ(ArrayProcessor::CalculateAverage(arr), (-5 - 3 - 7) / 3.0);
}

TEST(ArrayProcessorTest, DuplicateElements) {
    std::vector<int> arr = { 5, 5, 5, 5 };
    int min, max;
    ArrayProcessor::FindMinMax(arr, min, max);
    EXPECT_EQ(min, 5);
    EXPECT_EQ(max, 5);
    EXPECT_DOUBLE_EQ(ArrayProcessor::CalculateAverage(arr), 5.0);
}

TEST(ArrayProcessorTest, ReplaceAllMinMax) {
    std::vector<int> arr = { 1, 5, 3, 5, 1 };
    const double avg = 3.0;
    ArrayProcessor::ReplaceMinMax(arr, avg);
    EXPECT_EQ(arr, std::vector<int>(5, 3));
}

TEST(ArrayProcessorTest, PartialReplacement) {
    std::vector<int> arr = { 2, 4, 6, 8, 4 };
    const double avg = 4.8;
    ArrayProcessor::ReplaceMinMax(arr, avg);
    std::vector<int> expected = { 4, 4, 6, 4, 4 };
    EXPECT_EQ(arr, expected);
}

TEST(ArrayProcessorTest, AllElementsSameAfterReplace) {
    std::vector<int> arr = { 3, 3, 3 };
    ArrayProcessor::ReplaceMinMax(arr, 3.0);
    EXPECT_EQ(arr, std::vector<int>(3, 3));
}

TEST(ArrayProcessorTest, MixedPositiveNegative) {
    std::vector<int> arr = { -2, 4, -6, 8 };
    int min, max;
    ArrayProcessor::FindMinMax(arr, min, max);
    EXPECT_EQ(min, -6);
    EXPECT_EQ(max, 8);
    EXPECT_DOUBLE_EQ(ArrayProcessor::CalculateAverage(arr), (-2 + 4 - 6 + 8) / 4.0);
}

TEST(ArrayProcessorTest, LargeNumbersHandling) {
    std::vector<int> arr = { INT_MAX, INT_MIN, 0 };
    int min, max;
    ArrayProcessor::FindMinMax(arr, min, max);
    EXPECT_EQ(min, INT_MIN);
    EXPECT_EQ(max, INT_MAX);
    EXPECT_DOUBLE_EQ(ArrayProcessor::CalculateAverage(arr),
        (double(INT_MAX) + double(INT_MIN)) / 3.0);
}

TEST(ArrayProcessorTest, EmptyArrayReplaceNoOp) {
    std::vector<int> empty;
    EXPECT_NO_THROW(ArrayProcessor::ReplaceMinMax(empty, 0.0));
}