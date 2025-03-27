#include <cassert>
namespace nghung
{

    template <typename T>
    list<T>::node::node() : next(nullptr), prev(nullptr) {}

    template <typename T>
    list<T>::list() noexcept : size__(0), front__(nullptr), back__(nullptr) {}

    template <typename T>
    template <typename InputIterator>
    list<T>::list(InputIterator first, InputIterator last) noexcept : size__(0), front__(nullptr), back__(nullptr)
    {
        for (auto it = first; it != last; ++it)
        {
            push_back(*it);
        }
    }

    template <typename T>
    inline list<T>::operator bool() const noexcept
    {
        return !empty();
    }

    template <typename T>
    inline typename list<T>::pointer list<T>::front() noexcept
    {
        return front__;
    }

    template <typename T>
    inline typename list<T>::const_pointer list<T>::front() const noexcept
    {
        return front__;
    }

    template <typename T>
    inline typename list<T>::pointer list<T>::back() noexcept
    {
        return back__;
    }

    template <typename T>
    inline typename list<T>::const_pointer list<T>::back() const noexcept
    {
        return back__;
    }

    template <typename T>
    inline typename list<T>::size_type list<T>::size() const noexcept
    {
        return size__;
    }

    template <typename T>
    inline bool list<T>::empty() const noexcept
    {
        return 0 == size__;
    }

    template <typename T>
    inline void list<T>::clear() noexcept
    {
        /*
            for intrusive container, ownerships of nodes are not
            belong to the container, therefore, when clearing the
            list, simply reset the data member
        */
        size__ = 0;
        front__ = nullptr;
        back__ = nullptr;
    }

    template <typename T>
    inline void list<T>::push_front(reference item) noexcept
    {
        /*
            TODO if determining empty() avoidable?
         */
        if (empty())
        {
            back__ = &item;
            item.next = nullptr;
            item.prev = nullptr;
        }
        else
        {
            item.next = front__;
            item.prev = nullptr;
            front__->prev = &item;
        }
        front__ = &item;
        ++size__;
    }

    template <typename T>
    inline void list<T>::push_back(reference item) noexcept
    {
        /*
            TODO if determining empty() avoidable?
        */
        if (empty())
        {
            front__ = &item;
            item.prev = nullptr;
            item.next = nullptr;
        }
        else
        {
            item.prev = back__;
            item.next = nullptr;
            back__->next = &item;
        }
        back__ = &item;
        ++size__;
    }

    template <typename T>
    inline void list<T>::push_next(reference base, reference item) noexcept
    {
#ifdef DEBUG
        /*
                it is assumed non-empty list and &base != nullptr for better performance,
                therefore, need carefullly debug,
        */
        assert(nullptr != &base);
        assert(!empty());
#endif
        item.next = base.next;
        item.prev = &base;

        // if item is added to the end of the list
        if (back__ == &base)
        {
            back__ = &item;
        }
        // if item is added to any position other then the end of the list
        if (nullptr != base.next)
        {
            base.next->prev = &item;
        }

        base.next = &item;
        ++size__;
    }

    template <typename T>
    inline void list<T>::push_prev(reference base, reference item) noexcept
    {
#ifdef DEBUG
        /*
                it is assumed non-empty list and &base != nullptr for better performance,
                therefore, need carefullly debug,
        */
        assert(nullptr != &base);
        assert(!empty());
#endif
        item.next = &base;
        item.prev = base.prev;
        // if item is added to the beginning of the list
        if (front__ == &base)
        {
            front__ = &item;
        }
        // if item is added to any position other than the beginning of the list
        if (nullptr != base.prev)
        {
            base.prev->next = &item;
        }
        base.prev = &item;
        ++size__;
    }

    template <typename T>
    inline typename list<T>::pointer list<T>::pop(reference item) noexcept
    {
        pointer res{&item};

        if (res == front__)
        {
            front__ = res->next;
        }
        else
        {
            res->next->prev = res->prev;
        }

        if (res == back__)
        {
            back__ = res->prev;
        }
        else
        {
            res->prev->next = res->next;
        }

        res->next = nullptr;
        res->prev = nullptr;
        --size__;
        return res;
    }

    // TODO why not assume non-empty list?
    template <typename T>
    inline typename list<T>::pointer list<T>::pop_front() noexcept
    {
        if (empty())
        {
            return nullptr;
        }

        pointer res{front__};
        front__ = front__->next;
        res->next = nullptr;
        res->prev = nullptr;
        if (nullptr == front__)
        {
            back__ = nullptr;
        }
        else
        {
            front__->prev = nullptr;
        }
        --size__;

        return res;
    }

    template <typename T>
    inline typename list<T>::pointer list<T>::pop_back() noexcept
    {
        if (empty())
        {
            return nullptr;
        }
        pointer res{back__};
        back__ = res->prev;
        res->prev = nullptr;
        res->next = nullptr;

        if (nullptr == back__)
        {
            front__ = nullptr;
        }
        else
        {
            back__->next = nullptr;
        }
        --size__;
        return res;
    }

    template <typename T>
    inline typename list<T>::pointer list<T>::pop_next(reference base) noexcept
    {
#ifdef DEBUG
        /*
                it is assumed non-empty list and &base != nullptr for better performance,
                therefore, need carefullly debug,
        */
        assert(nullptr != &base);
        assert(!empty());
#endif
        // if given item is at the end of the list
        if (&base == back__)
        {
            return nullptr;
        }

        pointer res{base.next};
        // if item being removed is at the end of the list
        if (back__ == res)
        {
            back__ = &base;
        }
        else
        {
            res->next->prev = &base;
        }
        base.next = res->next;

        res->next = nullptr;
        res->prev = nullptr;
        --size__;
        return res;
    }

    template <typename T>
    inline typename list<T>::pointer list<T>::pop_prev(reference base) noexcept
    {
#ifdef DEBUG
        /*
                it is assumed non-empty list and &base != nullptr for better performance,
                therefore, need carefullly debug,
        */
        assert(nullptr != &base);
        assert(!empty());
#endif
        // if given item is at the beginning of the list
        if (front__ == &base)
        {
            return nullptr;
        }

        pointer res{base.prev};
        // if item being remove is at the beginning of the list
        if (front__ == res)
        {
            front__ = &base;
        }
        else
        {
            res->prev->next = &base;
        }
        base.prev = res->prev;

        res->next = nullptr;
        res->prev = nullptr;
        --size__;
        return res;
    }

    template <typename T>
    inline void list<T>::swap(list<T> &other) noexcept
    {
        std::swap(size__, other.size__);
        std::swap(front__, other.front__);
        std::swap(back__, other.back__);
    }

    template <typename U>
    inline void swap(list<U> &lhs, list<U> &rhs) noexcept
    {
        lhs.swap(rhs);
    }

    template <typename T>
    inline typename list<T>::iterator list<T>::begin() noexcept
    {
        return iterator(front__);
    }

    template <typename T>
    inline typename list<T>::iterator list<T>::end() noexcept
    {
        // TODO what should an end iterator usually be? a nullptr?
        return iterator();
    }

    template <typename T>
    list<T>::iterator::iterator() noexcept : ptr__(nullptr) {}

    template <typename T>
    list<T>::iterator::iterator(pointer ptr) noexcept : ptr__(ptr) {}

    template <typename T>
    inline typename list<T>::iterator &list<T>::iterator::operator++() noexcept
    {
        if (nullptr != ptr__)
        {
            ptr__ = ptr__->next;
        }
        return *this;
    }

    template <typename T>
    inline typename list<T>::iterator list<T>::iterator::operator++(int) noexcept
    {
        iterator tmp{*this};
        operator++();
        return tmp;
    }

    template <typename T>
    inline typename list<T>::pointer list<T>::iterator::operator->() noexcept
    {
        return ptr__;
    }

    template <typename T>
    inline typename list<T>::reference list<T>::iterator::operator*() noexcept
    {
        assert((nullptr != ptr__) && "iterator must be valid");
        return *ptr__;
    }

    template <typename T>
    inline list<T>::iterator::operator bool() const noexcept
    {
        return ptr__ != nullptr;
    }

} // namespace nghung
