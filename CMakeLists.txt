cmake_minimum_required(VERSION 3.19)
project(segment_tree_realization)

set(CMAKE_CXX_STANDARD 14)

include_directories(src/tree)
include_directories(src/utils)

add_executable(segment_tree_realization
        src/u-tests/main.py
        src/tree/SegmentTree.cpp
        src/tree/SegmentTree.h
        src/utils/ArraysFunctions.cpp
        src/utils/ArraysFunctions.h
        src/main.cpp src/tree/persistent/PersistentSegmentTree.cpp src/u-tests/tests.cpp)
