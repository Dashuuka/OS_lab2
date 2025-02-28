cmake_minimum_required(VERSION 3.8)

add_executable(UnitTests test_main.cpp)
target_compile_definitions(UnitTests PRIVATE UNIT_TESTING)
target_include_directories(UnitTests PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(UnitTests lab_lib gtest_main)

add_test(NAME UnitTests COMMAND UnitTests)