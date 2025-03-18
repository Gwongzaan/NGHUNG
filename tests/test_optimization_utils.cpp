#include <gtest/gtest.h>
#include "utility/optimization_utils.h"

TEST(utility_optimization_utils_TimestampCounterTest, rdtsc_returns_non_zero)
{
    using namespace nghung;
    timestamp_counter_type result = rdtsc();
    EXPECT_NE(result, 0);
}

TEST(utility_optimization_utils_PrintElapseTest, print_elapse_uint64_t_test)
{
    using namespace nghung;
    timestamp_counter_type start = rdtsc();
    timestamp_counter_type end = rdtsc() + 100;

    // Capture stdout
    std::stringstream buffer;
    std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());

    print_elapse(start, end, true);

    // Restore cout
    std::cout.rdbuf(old);

    std::string output = buffer.str();
    // TODO fix the test with specific cyles
    EXPECT_TRUE(output.find("BEFORE optimization:") != std::string::npos);
    EXPECT_TRUE(output.find("CPU timestamp counter Cycles: ") != std::string::npos);
    EXPECT_TRUE(output.find("LOOPCOUNT ") != std::string::npos);
}

TEST(utility_optimization_utils_PrintElapseTest, print_elapse_chrono_test)
{
    using namespace nghung;
    auto start = perf_clock::now();
    auto end = start + std::chrono::nanoseconds(5000);

    // Capture stdout
    std::stringstream buffer;
    std::streambuf *old = std::cout.rdbuf(buffer.rdbuf());

    print_elapse(start, end, false);

    // Restore cout
    std::cout.rdbuf(old);

    std::string output = buffer.str();

    // TODO fix the test with specific cyles
    EXPECT_TRUE(output.find("After Optimization:") != std::string::npos);
    EXPECT_TRUE(output.find("Time: ") != std::string::npos);
    EXPECT_TRUE(output.find("LOOPCOUNT ") != std::string::npos);
}