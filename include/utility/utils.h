/**
 * @file utility/utils.h
 * @author Guangzhuan Mo (gwongzaanmok@gmail.com)
 * @brief  a set of utility functions
 * @version 0.1.0
 * @date 2025-03-09
 *
 * @copyright Copyright (c) 2025
 *
 */

#ifndef NGHUNG_UTILS_H
#define NGHUNG_UTILS_H

#include "common/types.h"

namespace nghung
{
    /**
     * @brief seconds to nanoseconds factor
     *
     */
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
    std::string format_number(T num);

    /**
     * @brief Get the hft timestamp in nanoseconds
     *
     * @return Timestamp
     */
    Timestamp get_hft_timestamp_ns();

    /**
     * @brief convert nanoseconds timestamp to human readable format
     *
     * @param nanoseconds
     * @param format
     * @return std::string
     */
    std::string nanoseconds_to_time(Timestamp nanoseconds, const char format[] = "%Y-%m-%d %H:%M:%S");

} // namespace nghung

#include "utility/utils.inl"

#endif