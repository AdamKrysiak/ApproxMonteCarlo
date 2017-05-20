cmake_minimum_required(VERSION 3.6)
project(ApproxMonteCarlo)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -pthread")

set(SOURCE_FILES main.cpp ShootingBoard.cpp ShootingBoard.h)
add_executable(ApproxMonteCarlo ${SOURCE_FILES})