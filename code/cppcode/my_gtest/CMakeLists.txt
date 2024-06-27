# 整个项目的cmake (clion内置cmake等，系统不需要任何下载，除非要用命令行)
cmake_minimum_required(VERSION 3.27) #cmake最小版本
project(my_gtest) #项目名
set(CMAKE_CXX_STANDARD 17) #cpp版本

# 添加子目录
add_subdirectory(src)
add_subdirectory(lib)
