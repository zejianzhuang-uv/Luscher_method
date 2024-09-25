#!/bin/bash

# 编译 C++ 文件
clang++ 1D_energy_level.cpp -o a -lgsl -lgslcblas -std=c++20


time ./a


