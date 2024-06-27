#include <gtest/gtest.h>
#include "compute/compute.h"
#include <future>
#include <chrono>

// 参数（可随意命名）：
//      套件：该名字一样的用例属于同一套件
//      用例：要求命名唯一



TEST(TestCompute, TestCompute_01) {
    EXPECT_EQ(compute(-5), "error");
}

TEST(TestCompute, TestCompute_02) {
    EXPECT_EQ(compute(0), "error");
}

TEST(TestCompute, TestCompute_03) {
    EXPECT_EQ(compute(1), "1*1*1=1");
}

TEST(TestCompute, TestCompute_04) {
    EXPECT_EQ(compute(5), "5*5*5=21+23+25+27+29");
}

TEST(TestCompute, TestCompute_05) {
    EXPECT_EQ(compute(5.123), "error");
}

TEST(TestCompute, TestCompute_06) {
    EXPECT_EQ(compute(50),
              "50*50*50=2451+2453+2455+2457+2459+2461+2463+2465+2467+2469+2471+2473+2475+2477+2479+2481+2483+2485+2487+2489+2491+2493+2495+2497+2499+2501+2503+2505+2507+2509+2511+2513+2515+2517+2519+2521+2523+2525+2527+2529+2531+2533+2535+2537+2539+2541+2543+2545+2547+2549");
}

TEST(TestCompute, TestCompute_07) {
    EXPECT_EQ(compute(1000000000000000000), "1000000000000000000*1000000000000000000*1000000000000000000=略");
}
