#include <gtest/gtest.h>

// 一运行就报错？？？
int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
