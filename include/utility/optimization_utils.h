/**
 * @file utility/optimization_utils.h
 * @author Guangzhuan Mo (gwongzaanmok@gmail.com)
 * @brief utilities for optimization. such as for timing execution. number formatting, etc.
 * @version 0.1.0
 * @date 2025-03-18
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef HGHUNG_OPTIMIZATION_UTIL_H
#define HGHUNG_OPTIMIZATION_UTIL_H

#include <cstdint>
#include <chrono>

namespace nghung
{

    using timestamp_counter_type = uint64_t;
    using loop_counter_type = uint64_t;
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
    timestamp_counter_type rdtsc();

    /**
     * @brief print the time elapse of a piece of code
     *
     * @tparam T
     * @param start
     * @param end
     * @param before
     */
    template <class T>
    void print_elapse(const T &start, const T &end, bool before = true);

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
    void print_elapse(const std::chrono::time_point<perf_clock> &start, const std::chrono::time_point<perf_clock> &end, bool before);
} // namespace nghung

#include "utility/optimization_utils.inl"
#endif // HGHUNG_OPTIMIZATION_UTIL_H
