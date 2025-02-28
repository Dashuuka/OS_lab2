cmake_minimum_required(VERSION 3.8)

add_library(lab_lib STATIC min_max_thread.cpp average_thread.cpp)
target_include_directories(lab_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(Lab2_Operating_systems main.cpp)
target_link_libraries(Lab2_Operating_systems lab_lib)