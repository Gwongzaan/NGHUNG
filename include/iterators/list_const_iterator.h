#ifndef NGHUNG_LIST_CONST_ITERATOR_H
#define NGHUNG_LIST_CONST_ITERATOR_H

namespace nghung
{

    template <typename T>
    class list_const_iterator
    {
    public:
        using value_type = T;
        using reference = T &;
        using const_reference = const T &;
        using pointer = T *;
        using const_pointer = const T *;
        using difference_type = std::ptrdiff_t;
        using size_type = std::size_t;
        using iterator_category = std::bidirectional_iterator_tag;

        list_const_iterator() noexcept;
        explicit list_const_iterator(const_pointer node) noexcept;
        list_const_iterator(const list_iterator<value_type> &other) noexcept;
        list_const_iterator(const list_const_iterator &other) noexcept = default;
        list_const_iterator(list_const_iterator &&other) noexcept = default;

        ~list_const_iterator() noexcept = default;

        explicit operator bool() const noexcept;

        list_const_iterator &operator=(const list_const_iterator &other) noexcept = default;
        list_const_iterator &operator=(list_const_iterator &&other) noexcept = default;

        friend bool operator==(const list_const_iterator &lhs, const list_const_iterator &rhs) noexcept;
        friend bool operator!=(const list_const_iterator &lhs, const list_const_iterator &rhs) noexcept;

        list_const_iterator &operator++() noexcept;
        list_const_iterator operator++(int) noexcept;

        const_reference operator*() const noexcept;
        const_pointer operator->() const noexcept;

        void swap(list_const_iterator &other) noexcept;
        template <typename U>
        friend void swap(list_const_iterator<U> &lhs, list_const_iterator<U> &rhs) noexcept;

    private:
        pointer node__;
    };
} // namespace nghung

#include "iterators/list_const_iterator.inl"
#endif // NGHUNG_LIST_CONST_ITERATOR_H