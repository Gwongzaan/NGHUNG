#ifndef NGHUNG_LIST_CONST_REVERSE_ITERATOR_H
#define NGHUNG_LIST_CONST_REVERSE_ITERATOR_H

namespace nghung
{
    template <typename T>
    class list_const_reverse_iterator
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

        list_const_reverse_iterator() noexcept;
        explicit list_const_reverse_iterator(const_pointer node) noexcept;
        list_const_reverse_iterator(const list_const_reverse_iterator &other) noexcept = default;
        list_const_reverse_iterator(list_const_reverse_iterator &&other) noexcept = default;
        ~list_const_reverse_iterator() noexcept = default;

        explicit operator bool() const noexcept;

        list_const_reverse_iterator &operator=(const list_const_reverse_iterator &other) noexcept = default;
        list_const_reverse_iterator &operator=(list_const_reverse_iterator &&other) noexcept = default;

        friend bool operator==(const list_const_reverse_iterator &lhs, const list_const_reverse_iterator &rhs) noexcept;
        friend bool operator!=(const list_const_reverse_iterator &lhs, const list_const_reverse_iterator &rhs) noexcept;

        list_const_reverse_iterator &operator++() noexcept;
        list_const_reverse_iterator operator++(int) noexcept;

        const_reference operator*() const noexcept;
        const_pointer operator->() const noexcept;

        void swap(list_const_reverse_iterator &other) noexcept;
        template <typename U>
        friend void swap(list_const_reverse_iterator<U> &lhs, list_const_reverse_iterator<U> &rhs) noexcept;
    };

} // namespace nghung
#include "iterators/list_const_reverse_iterator.inl"
#endif // NGHUNG_LIST_CONST_REVERSE_ITERATOR_H