#ifndef NGHUNG_ITERATORS_LIST_REVERSE_H
#define NGHUNG_ITERATORS_LIST_REVERSE_H

namespace nghung
{

    template <typename T>
    class list_const_reverse_iterator;

    template <typename T>
    class list_reverse_iterator
    {
        friend list_const_reverse_iterator<T>;

    public:
        using value_type = T;
        using reference = T &;
        using const_reference = const T &;
        using pointer = T *;
        using const_pointer = const T *;
        using difference_type = std::ptrdiff_t;
        using size_type = std::size_t;
        using iterator_category = std::bidirectional_iterator_tag;

        list_reverse_iterator() noexcept;
        explicit list_reverse_iterator(pointer node) noexcept;
        list_reverse_iterator(const list_reverse_iterator &other) noexcept = default;
        list_reverse_iterator(list_reverse_iterator &&other) noexcept = default;
        ~list_reverse_iterator() noexcept = default;

        explicit operator bool() const noexcept;

        list_reverse_iterator &operator=(const list_reverse_iterator &other) noexcept = default;
        list_reverse_iterator &operator=(list_reverse_iterator &&other) noexcept = default;

        friend bool operator==(const list_reverse_iterator &lhs, const list_reverse_iterator &rhs) noexcept;
        friend bool operator!=(const list_reverse_iterator &lhs, const list_reverse_iterator &rhs) noexcept;

        list_reverse_iterator &operator++() noexcept;
        list_reverse_iterator operator++(int) noexcept;

        reference operator*() noexcept;
        pointer operator->() noexcept;

        void swap(list_reverse_iterator &other) noexcept;
        template <typename U>
        friend void swap(list_reverse_iterator<U> &lhs, list_reverse_iterator<U> &rhs) noexcept;

    private:
        pointer node__;
    };
} // namespace nghung

#endif // NGHUNG_ITERATORS_LIST_REVERSE_H
