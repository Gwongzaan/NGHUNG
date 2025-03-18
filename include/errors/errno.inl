namespace nghung
{
    template <typename OUTSTREAM>
    OUTSTREAM &operator<<(OUTSTREAM &os, ERROR_CODE code)
    {
        switch (code)
        {
        case ERROR_CODE::OK:
            os << "OK";
            break;
        case ERROR_CODE::SYMBOL_DUPLICATE:
            os << "SYMBOL_DUPLICATE";
            break;
        case ERROR_CODE::SYMBOL_NOT_FOUND:
            os << "SYMBOL_NOT_FOUND";
            break;
        case ERROR_CODE::ORDER_BOOK_DUPLICATE:
            os << "ORDER_BOOK_DUPLICATE";
            break;
        case ERROR_CODE::ORDER_BOOK_NOT_FOUND:
            os << "ORDER_BOOK_NOT_FOUND";
            break;
        case ERROR_CODE::ORDER_DUPLICATE:
            os << "ORDER_DUPLICATE";
            break;
        case ERROR_CODE::ORDER_NOT_FOUND:
            os << "ORDER_NOT_FOUND";
            break;
        case ERROR_CODE::ORDER_ID_INVALID:
            os << "ORDER_ID_INVALID";
            break;
        case ERROR_CODE::ORDER_TYPE_INVALID:
            os << "ORDER_TYPE_INVALID";
            break;
        case ERROR_CODE::ORDER_PARAMETER_INVALID:
            os << "ORDER_PARAMETER_INVALID";
            break;
        case ERROR_CODE::ORDER_QUANTITY_INVALID:
            os << "ORDER_QUANTITY_INVALID";
            break;
        default:
            os << "UNKNOWN";
            break;
        }
        return os;
    }

} // namespace nghung
