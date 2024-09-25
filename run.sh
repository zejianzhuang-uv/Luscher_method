#!/bin/bash

# 编译 C++ 文件
g++ 1D_energy_level.cpp -o a -lgsl -lgslcblas -std=c++20

# 检查编译是否成功
if [ $? -eq 0 ]; then
    echo "Compilation successful. Executing the program..."
    
    # 计算程序的执行时间
    time ./a  # 使用不带选项的 time 命令
else
    echo "Compilation failed."
fi


