/**
 * @file containers/list.h
 * @author Guangzhuan Mo (gwongzaanmok@gmail.com)
 * @brief intrusive list container designed specifically for HFT system, especialy for order book, not a general intrusive list container
 * @version 0.1.0
 * @date 2025-03-18
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef NGHUNG_CONTAINERS_LIST_H
#define NGHUNG_CONTAINERS_LIST_H

namespace nghung
{
    /**
     * @brief definition of intrusive list container
     *
     *  - Double linked list
     *  - not thread safe
     *
     *  - dev-log
     *
     *      - REFACTOR:
     *          change implementation of iterator to nested class,
     *          and keep it minimal.
     *
     *          iterators was implemented as separated class, iterators/list_iterators.h ...
     *
     * \ref data_structures/linked_list.md "linked list"
     *
     * \ref data_structures/double_linked_list.md "double linked list"
     *
     * \ref data_structures/intrusive_list.md "intrusive list"
     *
     * \ref reasoning/why_intrusive_list.md "reasons for intrusive list"
     *
     * \ref reasoning/why_nested_iterator_class_over_seperated_iterator_class.md "nested iterator class or seperated iterator class"
     *
     * \ref reasoning/why_simple_clear_member_function.md "why only reset size__, front__, back__ to clear the intrusive list"
     *
     * \ref reasoning/why_assume_non_empty_list.md "why and why not check emptyness and nullptr in push_next()"
     *
     * @tparam T
     */
    template <typename T>
    class list
    {

    public:
        class iterator;
        class const_iterator;

        using value_type = T;
        using reference = T &;
        using const_reference = const T &;
        using pointer = T *;
        using const_pointer = const T *;
        using size_type = std::size_t;
        using difference_type = std::ptrdiff_t;

        struct node
        {
            pointer next;
            pointer prev;

            node();
        };

        list() noexcept;
        template <typename InputIterator>
        list(InputIterator first, InputIterator last) noexcept;
        list(const list &) noexcept = default;
        list(list &&) noexcept = default;
        ~list() noexcept = default;

        list &operator=(const list &) noexcept = default;
        list &operator=(list &&) noexcept = default;

        /**
         * @brief check if the list is not empty
         *
         * @return true
         * @return false
         */
        explicit operator bool() const noexcept;

        /**
         * @brief get the pointer to the first item of the list
         *
         * @return pointer
         */
        pointer front() noexcept;

        /**
         * @brief get the const pointer to the first item of the list
         *
         * @return const_pointer
         */
        const_pointer front() const noexcept;

        /**
         * @brief get the pointer to the last item of the list
         *
         * @return pointer
         */
        pointer back() noexcept;

        /**
         * @brief get the const pointer to the last item of the list
         *
         * @return const_pointer
         */
        const_pointer back() const noexcept;

        /**
         * @brief get the number of items of the list
         *
         * @return size_type
         */
        size_type size() const noexcept;

        /**
         * @brief  check if the list is empty
         *
         * @return true
         * @return false
         */
        bool empty() const noexcept;

        /**
         * @brief reset the list to an empty list
         *
         */
        void clear() noexcept;

        /**
         * @brief add a new item named 'item' to the front of the list
         *
         * @param item
         */
        void push_front(reference item) noexcept;

        /**
         * @brief add a new item named 'item' to the end of the list
         *
         * @param item
         */
        void push_back(reference item) noexcept;

        /**
         * @brief add an new item, which is 'item',
         *          to the next of the given item, which is 'base'.
         *
         *  CRITICAL ASSUMPTIONS: for performance.
         *      - list is not empty
         *      -  &base != nullptr
         *
         * @param base
         * @param item
         */
        void push_next(reference base, reference item) noexcept;

        /**
         * @brief  add a new item, which is 'item',
         *          to the next of the given item, which is 'base'.
         *
         * CRITICAL ASSUMPTIONS: for performance.
         *      - list is not empty
         *      - &base != nullptr
         *
         * @param base
         * @param item
         */
        void push_prev(reference base, reference item) noexcept;

        /**
         * @brief remove the given item from the list,
         *      and get the pointer to the item
         *
         * CRITICAL ASSUMPTIONS:
         *      - item exists in the list
         *
         * @param item
         * @return pointer
         */
        pointer pop(reference item) noexcept;

        /**
         * @brief remove the first item from the list.
         *      and return the pointer to the item
         *
         * @return pointer
         */
        pointer pop_front() noexcept;

        /**
         * @brief remove the last item from the list.
         *      and return the pointer to the item
         *
         * @return pointer
         */
        pointer pop_back() noexcept;

        /**
         * @brief remove the next item of the given item named 'base'
         *      and return the pointer to the removed item
         *
         * @param base
         * @return pointer
         */
        pointer pop_next(reference base) noexcept;

        /**
         * @brief remove the previous item of the given item named 'base',
         *      and return the pointer to the removed item
         *
         * CRITICAL ASSUMPTIONS:
         *      - non-empty list
         *      - &base != nullptr
         *
         * @param base
         * @return pointer
         */
        pointer pop_prev(reference base) noexcept;

        /**
         * @brief swap two list instance
         *
         * @param other
         */
        void swap(list &other) noexcept;
        /**
         * @brief friend function to swap two list instance
         *
         * @tparam U
         * @param lhs
         * @param rhs
         */
        template <typename U>
        friend void swap(list<U> &lhs, list<U> &rhs) noexcept;

        /**
         * @brief get the iterator to the first item of the list
         *
         * @return iterator
         */
        iterator begin() noexcept;
        /**
         * @brief get the iterator to the last item of the list
         *
         * @return iterator
         */
        iterator end() noexcept;

        /**
         * @brief minimal impleemntation of iterator,
         *      for least overhead to the list instance.
         *
         */
        class iterator
        {
            friend const_iterator;

        private:
            pointer ptr__;

        public:
            iterator() noexcept;
            explicit iterator(pointer ptr) noexcept;

            iterator &operator++() noexcept;
            iterator operator++(int) noexcept;

            pointer operator->() noexcept;
            reference operator*() noexcept;

            explicit operator bool() const noexcept;

            // TODO delcare friend function in header file and define in inl file,
            // failed, because it is a nested template class, it is tricky.
            // but is there a way to implement it?

            friend inline bool operator==(const iterator &a, const iterator &b) noexcept
            {
                return a.ptr__ == b.ptr__;
            }

            // TODO it looks like it would cause segmentation fault if implemented as " return a != b "
            // why ?
            friend inline bool operator!=(const iterator &a, const iterator &b) noexcept
            {
                return a.ptr__ != b.ptr__;
            }

        }; // class iterator

    private:
        size_type size__;
        pointer front__;
        pointer back__;
    }; // class list

} // namespace nghung

#include "containers/list.inl"

#endif // NGHUNG_CONTAINERS_LIST_H