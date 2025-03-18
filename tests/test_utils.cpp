#include <gtest/gtest.h>
#include <ctime>
#include <sys/mman.h> // for mprotect()
#include <unistd.h>   // for sysconf
#include <dlfcn.h>    // for dlsym
#include <cstdlib>
#include "utility/utils.h"

TEST(utility_utils_FormatNumberTest, IntegerTest)
{
    using namespace nghung;
    EXPECT_EQ(format_number(1230), "1,230");
    EXPECT_EQ(format_number(-456), "-456");
    EXPECT_EQ(format_number(0), "0");
    EXPECT_EQ(format_number(std::numeric_limits<int>::max()), "2,147,483,647");
    EXPECT_EQ(format_number(std::numeric_limits<int>::min()), "-2,147,483,648");
}

TEST(utility_utils_FormatNumberTest, DoubleTest)
{
    using namespace nghung;
    EXPECT_EQ(format_number(3.14), "3.140000");
    EXPECT_EQ(format_number(2345.23), "2,345.230000");
    EXPECT_EQ(format_number(-2.718), "-2.718000");
    EXPECT_EQ(format_number(0.0), "0.000000");
    EXPECT_EQ(format_number(std::numeric_limits<double>::max()), "179,769,313,486,231,570,814,527,423,731,704,356,798,070,567,525,844,996,598,917,476,803,157,260,780,028,538,760,589,558,632,766,878,171,540,458,953,514,382,464,234,321,326,889,464,182,768,467,546,703,537,516,986,049,910,576,551,282,076,245,490,090,389,328,944,075,868,508,455,133,942,304,583,236,903,222,948,165,808,559,332,123,348,274,797,826,204,144,723,168,738,177,180,919,299,881,250,404,026,184,124,858,368.000000");
    EXPECT_EQ(format_number(std::numeric_limits<double>::min()), "0.000000");
    EXPECT_EQ(format_number(std::numeric_limits<double>::quiet_NaN()), "nan");
    EXPECT_EQ(format_number(std::numeric_limits<double>::infinity()), "inf");
    EXPECT_EQ(format_number(-std::numeric_limits<double>::infinity()), "-inf");
}

TEST(utility_utils_FormatNumberTest, FloatTest)
{
    using namespace nghung;
    EXPECT_EQ(format_number(1.5f), "1.500000");
    EXPECT_EQ(format_number(-2.25f), "-2.250000");
    EXPECT_EQ(format_number(0.0f), "0.000000");
    EXPECT_EQ(format_number(std::numeric_limits<float>::max()), "340,282,346,638,528,859,811,704,183,484,516,925,440.000000");
    EXPECT_EQ(format_number(std::numeric_limits<float>::min()), "0.000000");
    EXPECT_EQ(format_number(std::numeric_limits<float>::quiet_NaN()), "nan");
    EXPECT_EQ(format_number(std::numeric_limits<float>::infinity()), "inf");
    EXPECT_EQ(format_number(-std::numeric_limits<float>::infinity()), "-inf");
}

TEST(utility_utils_TimestampTest, BasicFunctionality)
{
    using namespace nghung;
    Timestamp timestamp = get_hft_timestamp_ns();
    EXPECT_NE(timestamp, 0); // Timestamp should not be zero
}

TEST(utility_utils_TimestampTest, ReasonableValue)
{
    using namespace nghung;
    Timestamp timestamp = get_hft_timestamp_ns();
    time_t current_time_sec;
    time(&current_time_sec);
    Timestamp expected_lower_bound = static_cast<Timestamp>(current_time_sec) * SEC_2_NS_FACTOR;
    // adding 10 seconds worth of nanoseconds to create an upper bound.
    Timestamp expected_upper_bound = expected_lower_bound + (10 * SEC_2_NS_FACTOR);
    EXPECT_GE(timestamp, expected_lower_bound);
    EXPECT_LE(timestamp, expected_upper_bound);
}
// Regular C-style function for mocking clock_gettime
int mock_clock_gettime(clockid_t clk_id, struct timespec *tp)
{
    return -1;
}
// TODO continue debuging the issues,
// this is a miscellaneous function, and the issue is in the test code,
// focus on developeing core component first
// https://gemini.google.com/app/f08ccdedf4607eb6

/*
TEST(TimestampTest, ClockFailureHandling)
{
    using namespace nghung;
    std::stringstream buffer;
    std::streambuf *oldcerr = std::cerr.rdbuf(buffer.rdbuf());

    auto original_clock_gettime = reinterpret_cast<decltype(clock_gettime) *>(dlsym(RTLD_NEXT, "clock_gettime"));
    if (original_clock_gettime == nullptr)
    {
        std::cerr << "Error: dlsym failed to find clock_gettime" << std::endl;
        std::cerr.rdbuf(oldcerr);
        return;
    }

    void *clock_gettime_ptr = reinterpret_cast<void *>(original_clock_gettime);
    void *mock_ptr = reinterpret_cast<void *>(mock_clock_gettime);

    size_t page_size = sysconf(_SC_PAGE_SIZE);
    void *page_aligned_ptr = (void *)((uintptr_t)clock_gettime_ptr & ~(page_size - 1));

    if (mprotect(page_aligned_ptr, page_size, PROT_READ | PROT_WRITE | PROT_EXEC) != 0)
    {
        std::cerr << "Error: mprotect failed" << std::endl;
        std::cerr.rdbuf(oldcerr);
        return;
    }

    *(void **)clock_gettime_ptr = mock_ptr;
    std::cout << "Original clock_gettime address: " << clock_gettime_ptr << std::endl;

    testing::FLAGS_gtest_death_test_style = "threadsafe";
    ASSERT_EXIT(get_hft_timestamp_ns(), testing::ExitedWithCode(EXIT_FAILURE), "Error getting timestamp");
    if (testing::UnitTest::GetInstance()->current_test_info()->result()->Passed())
    {

        *(void **)clock_gettime_ptr = clock_gettime_ptr;

        if (mprotect(page_aligned_ptr, page_size, PROT_READ | PROT_EXEC) != 0)
        {
            std::cerr << "Error: mprotect restore failed" << std::endl;
        }
    }
    std::cerr.rdbuf(oldcerr);
}

*/

// this test will only run if CLOCK_REALTIME fails.
// TODO read and understanding it better, genemi generated this test case

/*
TEST(TimestampTest, ClockFailureHandling)
{
    using namespace nghung;
    // Redirect cerr to a string stream to capture the error message
    std::stringstream buffer;
    std::streambuf *oldcerr = std::cerr.rdbuf(buffer.rdbuf());

    // Mock clock_gettime to always fail
    auto original_clock_gettime = reinterpret_cast<decltype(clock_gettime) *>(dlsym(RTLD_NEXT, "clock_gettime"));

    //
    // when trying to cast a lambda function to a void*,
    // it is not directly convertible to function pointers in the same way
    // as regular c-style functions
    //
    // auto mock_clock_gettime = [](clockid_t clk_id, struct timespec *tp) -> int
    // {
    //     return -1;
    // };

    // Replace clock_gettime with the mock
    void *clock_gettime_ptr = reinterpret_cast<void *>(original_clock_gettime);
    void *mock_ptr = reinterpret_cast<void *>(mock_clock_gettime);

    mprotect((void *)((uintptr_t)clock_gettime_ptr & ~(sysconf(_SC_PAGE_SIZE) - 1)), sysconf(_SC_PAGE_SIZE), PROT_READ | PROT_WRITE | PROT_EXEC);

    *(void **)clock_gettime_ptr = mock_ptr;

    // Capture the exit call.
    // TODO segamentaion fault occurs here,
    testing::FLAGS_gtest_death_test_style = "threadsafe";
    ASSERT_EXIT(get_hft_timestamp_ns(), testing::ExitedWithCode(EXIT_FAILURE), "Error getting timestamp");

    // Restore original clock_gettime
    *(void **)clock_gettime_ptr = clock_gettime_ptr;
    mprotect((void *)((uintptr_t)clock_gettime_ptr & ~(sysconf(_SC_PAGE_SIZE) - 1)), sysconf(_SC_PAGE_SIZE), PROT_READ | PROT_EXEC);

    // Restore cerr
    std::cerr.rdbuf(oldcerr);
}
    */

TEST(utility_utils_NanosecondsToTimeTest, BasicTest)
{
    using namespace nghung;
    Timestamp nanoseconds = 1678886400000000000; // March 15, 2023 13:20:00 UTC
    std::string expected = "2023-03-15 13:20:00.000000000 UTC";
    ASSERT_EQ(nanoseconds_to_time(nanoseconds), expected);
}

TEST(utility_utils_NanosecondsToTimeTest, WithNanoseconds)
{
    using namespace nghung;
    Timestamp nanoseconds = 1678886400123456789;
    std::string expected = "2023-03-15 13:20:00.123456789 UTC";
    ASSERT_EQ(nanoseconds_to_time(nanoseconds), expected);
}

TEST(utility_utils_NanosecondsToTimeTest, DifferentFormat)
{
    using namespace nghung;
    Timestamp nanoseconds = 1678886400123456789;
    std::string expected = "03/15/2023 13:20:00.123456789 UTC";
    ASSERT_EQ(nanoseconds_to_time(nanoseconds, "%m/%d/%Y %H:%M:%S"), expected);
}

TEST(utility_utils_NanosecondsToTimeTest, ZeroNanoseconds)
{
    using namespace nghung;
    Timestamp nanoseconds = 0;
    std::string expected = "1970-01-01 00:00:00.000000000 UTC";
    ASSERT_EQ(nanoseconds_to_time(nanoseconds), expected);
}

TEST(utility_utils_NanosecondsToTimeTest, NearOverflow)
{
    using namespace nghung;
    // Test a time near the max u_int64_t value.
    Timestamp nanoseconds = 18446744073709551615ULL; // max u_int64_t value
    // This test is hard to make exact because the max time_t is implementation dependent.
    // So we test that it does not crash, and that the function returns a string.

    std::string result = nanoseconds_to_time(nanoseconds);
    ASSERT_FALSE(result.empty());
}

TEST(utility_utils_NanosecondsToTimeTest, VerySmallNanoseconds)
{
    using namespace nghung;
    Timestamp nanoseconds = 1ULL;
    std::string expected = "1970-01-01 00:00:00.000000001 UTC";
    ASSERT_EQ(nanoseconds_to_time(nanoseconds), expected);
}