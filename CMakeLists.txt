cmake_minimum_required(VERSION 3.3)
project(assignment2)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp TrainingData.cpp TrainingData.h Net.h Net.cpp neuron.h TrainingData.h)
add_executable(assignment2 ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(assignment2 ${LIBSTDCXX})