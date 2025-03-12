/**
 * @file utils.inl
 * @author Guangzhuan Mo (gwongzaanmok@gmail.com)
 * @brief a set of inline utility functions
 * @version 0.1.0
 * @date 2025-03-09
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef NGHUNG_UTIL_INL
#define NGHUNG_UTIL_INL

#include "types.h"

#include <string>
#include <chrono>
#include <ctime>
#include <sys/time.h> // for clock_gettime
#include <iostream>
#include <iomanip>

namespace NGHUNG
{
    constexpr Timestamp SEC_2_NS_FACTOR{1000000000};

    /**
     * @brief
     *  convert number to numeric format
     *
     *  for example:
     *
     *      100000 -> 100,000
     *
     * @param num
     * @return std::string
     */
    template <typename T>
    inline std::string format_number(T num)
    {
        std::stringstream ss;
        ss.imbue(std::locale(""));
        ss << std::fixed << num;
        return ss.str();
    }

    /**
     * @brief Get the hft timestamp in nanoseconds
     *
     * @return Timestamp
     */
    inline Timestamp get_hft_timestamp_ns()
    {
        timespec ts;
        // TODO change CLOCK_REALTIME for a faster and more precise realtime clock when available
        if (-1 == clock_gettime(CLOCK_REALTIME, &ts))
        {
            std::cerr << "Error getting timestamp" << std::endl;
            // TODO ? should exit with failure or return??
            exit(EXIT_FAILURE);
        }

        return (ts.tv_sec * SEC_2_NS_FACTOR) + ts.tv_nsec;
    }

    /**
     * @brief convert nanoseconds timestamp to human readable format
     *
     * @param nanoseconds
     * @param format
     * @return std::string
     */
    inline std::string nanoseconds_to_time(Timestamp nanoseconds, const char format[] = "%Y-%m-%d %H:%M:%S")
    {
        using namespace std::chrono;
        Timestamp seconds{nanoseconds / SEC_2_NS_FACTOR};
        nanoseconds %= SEC_2_NS_FACTOR;

        auto time_point{system_clock::from_time_t(seconds)};
        std::time_t time_t_value{system_clock::to_time_t(time_point)};
        std::tm utc_tm_value{*std::gmtime(&time_t_value)};

        std::stringstream ss;
        ss << std::put_time(&utc_tm_value, format)
           << "." << std::setfill('0') << std::setw(9) << nanoseconds
           << " UTC";

        return ss.str();
    }
} // namespace NGHUNG

#endif