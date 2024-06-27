
add_subdirectory(compute)  # 子文件夹

add_executable(MAIN main.cpp)  # 将main.cpp生成可执行文件，命名为MAIN
add_executable(TEST test.cpp test_main.cpp)

target_link_libraries(MAIN COMPUTE)  # 在MAIN里面使用COMPUTE
target_link_libraries(TEST COMPUTE gtest_main)  # 在TEST引入gtest、COMPUTE