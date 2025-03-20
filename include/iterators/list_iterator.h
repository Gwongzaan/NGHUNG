#ifndef NGHUNG_ITERATORS_LIST_H
#define NGHUNG_ITERATORS_LIST_H

namespace nghung
{
    template <typename T>
    class list_const_iterator;

    template <typename T>
    class list_iterator
    {
        friend list_const_iterator<T>;

    public:
        using value_type = T;
        using reference = T &;
        using const_reference = const T &;
        using pointer = T *;
        using const_pointer = const T *;
        using difference_type = std::ptrdiff_t;
        using size_type = std::size_t;
        using iterator_category = std::bidirectional_iterator_tag;

        list_iterator() noexcept;
        explicit list_iterator(pointer node) noexcept;
        list_iterator(const list_iterator &other) noexcept = default;
        list_iterator(list_iterator &&other) noexcept = default;

        ~list_iterator() noexcept = default;

        explicit operator bool() const noexcept;

        list_iterator &operator=(const list_iterator &other) noexcept = default;
        list_iterator &operator=(list_iterator &&other) noexcept = default;

        template <typename U>
        friend bool operator==(const list_iterator<U> &lhs, const list_iterator<U> &rhs) noexcept;
        template <typename U>
        friend bool operator!=(const list_iterator<U> &lhs, const list_iterator<U> &rhs) noexcept;

        list_iterator &operator++() noexcept;
        list_iterator operator++(int) noexcept;

        reference operator*() noexcept;
        pointer operator->() noexcept;

        void swap(list_iterator &other) noexcept;
        template <typename U>
        friend void swap(list_iterator<U> &lhs, list_iterator<U> &rhs) noexcept;

    private:
        pointer node__;
    };

} // namespace nghung

#include "iterators/list_iterator.inl"

#endif // NGHUNG_ITERATORS_LIST_H