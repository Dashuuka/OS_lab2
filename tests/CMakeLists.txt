add_executable(UnitTests test_array_processor.cpp)
target_link_libraries(UnitTests 
    PRIVATE 
        array_processor
        gtest_main
)

add_test(NAME ArrayProcessorTests COMMAND UnitTests)