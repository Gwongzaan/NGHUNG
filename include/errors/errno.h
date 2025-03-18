/**
 * @file errors/errno.h
 * @author Guangzhuan Mo (gwongzaanmok@gmail.com)
 * @brief error definitions
 * @version 0.1.0
 * @date 2025-03-18
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef NGHUNG_ERRORS_H
#define NGHUNG_ERRORS_H

#include <cstdint>

namespace nghung
{
    enum class ERROR_CODE : uint8_t
    {
        OK,
        SYMBOL_DUPLICATE,
        SYMBOL_NOT_FOUND,
        ORDER_BOOK_DUPLICATE,
        ORDER_BOOK_NOT_FOUND,
        ORDER_DUPLICATE,
        ORDER_NOT_FOUND,
        ORDER_ID_INVALID,
        ORDER_TYPE_INVALID,
        ORDER_PARAMETER_INVALID,
        ORDER_QUANTITY_INVALID
    };

    template <typename OUTSTREAM>
    OUTSTREAM &operator<<(OUTSTREAM &os, ERROR_CODE err);

} // namespace nghung

#include "errors/errno.inl"
#endif