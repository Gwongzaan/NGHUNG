#include <gtest/gtest.h>
#include <sstream>
#include "errors/errno.h"

TEST(errors_errno_ErrorCodeOperatorTest, OutputStream)
{
    using namespace nghung;
    std::stringstream ss;
    ss << ERROR_CODE::OK;
    EXPECT_EQ(ss.str(), "OK");

    ss.str(""); // Clear the stringstream
    ss << ERROR_CODE::SYMBOL_DUPLICATE;
    EXPECT_EQ(ss.str(), "SYMBOL_DUPLICATE");

    ss.str("");
    ss << ERROR_CODE::SYMBOL_NOT_FOUND;
    EXPECT_EQ(ss.str(), "SYMBOL_NOT_FOUND");

    ss.str("");
    ss << ERROR_CODE::ORDER_BOOK_DUPLICATE;
    EXPECT_EQ(ss.str(), "ORDER_BOOK_DUPLICATE");

    ss.str("");
    ss << ERROR_CODE::ORDER_BOOK_NOT_FOUND;
    EXPECT_EQ(ss.str(), "ORDER_BOOK_NOT_FOUND");

    ss.str("");
    ss << ERROR_CODE::ORDER_DUPLICATE;
    EXPECT_EQ(ss.str(), "ORDER_DUPLICATE");

    ss.str("");
    ss << ERROR_CODE::ORDER_NOT_FOUND;
    EXPECT_EQ(ss.str(), "ORDER_NOT_FOUND");

    ss.str("");
    ss << ERROR_CODE::ORDER_ID_INVALID;
    EXPECT_EQ(ss.str(), "ORDER_ID_INVALID");

    ss.str("");
    ss << ERROR_CODE::ORDER_TYPE_INVALID;
    EXPECT_EQ(ss.str(), "ORDER_TYPE_INVALID");

    ss.str("");
    ss << ERROR_CODE::ORDER_PARAMETER_INVALID;
    EXPECT_EQ(ss.str(), "ORDER_PARAMETER_INVALID");

    ss.str("");
    ss << ERROR_CODE::ORDER_QUANTITY_INVALID;
    EXPECT_EQ(ss.str(), "ORDER_QUANTITY_INVALID");

    ss.str("");
    ss << static_cast<ERROR_CODE>(999); // Assuming 999 is not defined in ERROR_CODE, testing default case
    EXPECT_EQ(ss.str(), "UNKNOWN");
}
