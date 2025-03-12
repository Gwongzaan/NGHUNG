/**
 * @file optimization_utils.inl
 * @author Guangzhuan Mo (gwongzaanmok@gmail.com)
 * @brief utilities for optimization. such as for timing execution. number formatting, etc.
 * @version 0.1.0
 * @date 2025-03-09
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef HGHUNG_OPTIMIZATION_UTIL_INL
#define HGHUNG_OPTIMIZATION_UTIL_INL

#include <x86intrin.h>
#include <iostream>
#include <chrono>
#include <string>
#include "utils.h"
#include <sys/types.h>

namespace NGHUNG
{
    using timestamp_counter_type = u_int64_t;
    using loop_counter_type = u_int64_t;
    using perf_clock = std::chrono::high_resolution_clock;

    constexpr loop_counter_type LOOPCOUNT{100000000};

    /**
     * @brief
     *
     *  ReaD Time Stamp Counter
     *
     *  \ref reasoning/chosing-rdtsc-vs-system-clock.md "choosing rdtsc or system clock"
     *
     * @return timestamp_counter_type
     */
    inline timestamp_counter_type
    rdtsc()
    {
        return __rdtsc();
    }
    /**
     * @brief print the time elapse of a piece of code
     *
     * @tparam T
     * @param start
     * @param end
     * @param before
     */
    template <class T>
    inline void print_elapse(const T &start, const T &end, bool before = true)
    {
        std::cout << std::endl
                  << (before ? "BEFORE optimization: " : "After Optimization: ") << std::endl
                  << " CPU timestamp counter Cycles: " << format_number(end - start) << std::endl
                  << "LOOPCOUNT : " << format_number(LOOPCOUNT) << std::endl
                  << std::endl;
    }

    /**
     * @brief
     *      specialized template for using std::chrono::high_resolution in timing execution
     *
     *  \ref reasoning/chosing-rdtsc-vs-system-clock.md "choosing rdtsc or system clock"
     *
     * @tparam T
     * @param start
     * @param end
     * @param before
     */
    template <>
    inline void print_elapse(const std::chrono::time_point<perf_clock> &start, const std::chrono::time_point<perf_clock> &end, bool before)
    {
        std::cout << std::endl
                  << (before ? "BEFORE optimization: " : "After Optimization: ") << std::endl
                  << " Time: " << format_number(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()) << " nanoseconds" << std::endl
                  << "LOOPCOUNT : " << format_number(LOOPCOUNT) << std::endl
                  << std::endl;
    }
} // namespace NGHUNG

#endif