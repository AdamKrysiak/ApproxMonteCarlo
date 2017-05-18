cmake_minimum_required(VERSION 3.6)
project(ApproxMonteCarlo)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(SOURCE_FILES main.cpp Score.cpp Score.h)
add_executable(ApproxMonteCarlo ${SOURCE_FILES})