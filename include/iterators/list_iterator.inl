#include <cassert>

namespace nghung
{
    template <typename T>
    list_iterator<T>::list_iterator() noexcept : node__(nullptr) {}

    template <typename T>
    list_iterator<T>::list_iterator(pointer node) noexcept : node__(node) {}

    template <typename T>
    list_iterator<T>::operator bool() const noexcept
    {
        return node__ != nullptr;
    }

    template <typename T>
    bool operator==(const list_iterator<T> &lhs, const list_iterator<T> &rhs) noexcept
    {
        return lhs.node__ == rhs.node__;
    }

    template <typename T>
    bool operator!=(const list_iterator<T> &lhs, const list_iterator<T> &rhs) noexcept
    {
        return lhs.node__ != rhs.node__;
    }

    template <typename T>
    list_iterator<T> &list_iterator<T>::operator++() noexcept
    {
        if (nullptr == node__)
        {
            node__ = node__->next;
        }

        return *this;
    }

    template <typename T>
    list_iterator<T> list_iterator<T>::operator++(int) noexcept
    {
        list_iterator<T> temp(*this);
        operator++();
        return temp;
    }

    template <typename T>
    typename list_iterator<T>::reference list_iterator<T>::operator*() noexcept
    {
        assert((nullptr != node__) && "Iterator must be valid");
        return *node__;
    }

    template <typename T>
    typename list_iterator<T>::pointer list_iterator<T>::operator->() noexcept
    {
        return node__;
    }

    template <typename T>
    void list_iterator<T>::swap(list_iterator<T> &other) noexcept
    {
        using std::swap;
        swap(node__, other.node__);
    }

    template <typename T>
    void swap(list_iterator<T> &lhs, list_iterator<T> &rhs) noexcept
    {
        lhs.swap(rhs);
    }

} // namespace nghung
