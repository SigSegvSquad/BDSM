cmake_minimum_required(VERSION 3.17)
project(BDSM)

set(CMAKE_CXX_STANDARD 11)

add_executable(BDSM main.cpp Utility.h "B Tree/BNode.cpp" "B Tree/BNode.h" "B Tree/BTree.cpp" "B Tree/BTree.h" "B+ Tree/BPlusTree.cpp" "B+ Tree/BPlusTree.h")
