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
#include <string>
#include "utility/utils.h"

namespace nghung
{

    inline timestamp_counter_type
    rdtsc()
    {
        return __rdtsc();
    }

    template <class T>
    inline void print_elapse(const T &start, const T &end, bool before)
    {
        std::cout << std::endl
                  << (before ? "BEFORE optimization: " : "After Optimization: ") << std::endl
                  << " CPU timestamp counter Cycles: " << format_number(end - start) << std::endl
                  << "LOOPCOUNT : " << format_number(LOOPCOUNT) << std::endl
                  << std::endl;
    }

    template <>
    inline void print_elapse(const std::chrono::time_point<perf_clock> &start, const std::chrono::time_point<perf_clock> &end, bool before)
    {
        std::cout << std::endl
                  << (before ? "BEFORE optimization: " : "After Optimization: ") << std::endl
                  << " Time: " << format_number(std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count()) << " nanoseconds" << std::endl
                  << "LOOPCOUNT : " << format_number(LOOPCOUNT) << std::endl
                  << std::endl;
    }
} // namespace nghung

#endif