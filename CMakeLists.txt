cmake_minimum_required(VERSION 3.17)
project(BDSM)

set(CMAKE_CXX_STANDARD 14)

add_executable(BDSM BTree.cpp BPlusTree.cpp main.cpp Utility.h)
