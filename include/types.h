/**
 * @file types.h
 * @author Guangzhuan Mo (gwongzaanmok@gmail.com)
 * @brief  type alias
 * @version 0.1.0
 * @date 2025-03-09
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef NGHUNG_TYPES_H
#define NGHUNG_TYPES_H

#include <cstdint>
#include <boost/intrusive/list.hpp>

namespace NGHUNG
{
    /**
     * @brief
     *  use u_int64_t over long long
     *
     *  \ref reasoning/why-u_int64_t-for-timestamp.md "detailed reasoning of choosing u_int64_t"
     */
    using Timestamp = uint64_t;
    using OrderID = uint64_t;
    using Quantity = uint32_t;
    using Price = uint64_t;
    using SymbolID = uint32_t;
    using Volume = uint64_t;

    template <typename T, typename... Options>
    using List = boost::intrusive::list<T, Options...>;

} // namespace NGHUNG

#endif