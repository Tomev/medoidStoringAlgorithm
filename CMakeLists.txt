cmake_minimum_required(VERSION 3.7)
project(medoidStoringAlgorithm)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES main.cpp textDataReader.cpp textDataParser.cpp medoidStoringAlgorithm.cpp medoidStoringAlgorithm.h sample.h textDataSample.cpp textDataSample.h)
add_executable(medoidStoringAlgorithm ${SOURCE_FILES})