#include <gtest/gtest.h>
#include "containers/list.h"
#include <string>

namespace nghung_test
{
    // TODO refactor the test after the order book is implemented.

    // TODO refine the test cases

    // this is not a general intrusive list container,
    // it is designed specifically for HFT order book
    // it is used for specific scenario
    // therefore, test case is specific for handling order book

    // dummy data structure
    struct order
    {
        int price;
    };

    struct order_node : public order, public nghung::list<order_node>::node
    {
    };
    // fixture template for typed tests
    template <typename T>
    class intrusive_double_list_test : public ::testing::Test
    {
    protected:
        using list_type = nghung::list<T>;
    };
    // specify the type to test
    using list_types = ::testing::Types<order_node>;
    TYPED_TEST_SUITE(intrusive_double_list_test, list_types);

    TYPED_TEST(intrusive_double_list_test, internal_node_default_constructor)
    {
        using namespace nghung;
        using list_type = typename TestFixture::list_type;
        list_type l;
        typename list<TypeParam>::node n;
        EXPECT_TRUE(noexcept(n));
        EXPECT_EQ(nullptr, n.next);
        EXPECT_EQ(nullptr, n.prev);
    }

    TYPED_TEST(intrusive_double_list_test, list_default_constructor)
    {
        using namespace nghung;
        list<TypeParam> l;
        EXPECT_TRUE(noexcept(l));
        EXPECT_TRUE(l.empty());
        EXPECT_EQ(0, l.size());
        EXPECT_EQ(nullptr, l.front());
        EXPECT_EQ(nullptr, l.back());
    }

    TYPED_TEST(intrusive_double_list_test, iterator_range_constructor)
    {
        using namespace nghung;
        // TODO iterator_range_constructuor
    }

    TYPED_TEST(intrusive_double_list_test, bool_convertion)
    {
        using namespace nghung;
        list<TypeParam> l;
        EXPECT_FALSE(static_cast<bool>(l));
        TypeParam n;
        l.push_front(n);
        EXPECT_TRUE(static_cast<bool>(l));
        TypeParam n2;
        l.push_front(n2);
        EXPECT_TRUE(static_cast<bool>(l));
    }

    TYPED_TEST(intrusive_double_list_test, front)
    {
        using namespace nghung;
        list<TypeParam> l;
        // add the first item to the list,
        TypeParam n;
        l.push_back(n);
        EXPECT_EQ(&n, l.front());

        TypeParam *r{l.front()};
        EXPECT_EQ(&n, r);
        EXPECT_EQ(n.next, r->next);
        EXPECT_EQ(n.prev, r->prev);

        // add another node to the end,
        TypeParam n2;
        l.push_back(n2);
        EXPECT_EQ(&n, r);
        EXPECT_EQ(n.prev, nullptr);
        // n should be at the front
        EXPECT_EQ(n.next, &n2);
        EXPECT_EQ(&n, l.front());
    }

    TYPED_TEST(intrusive_double_list_test, front_const)
    {
        using namespace nghung;
        list<TypeParam> l;
        TypeParam n;
        l.push_front(n);
        const TypeParam *r{l.front()};
        EXPECT_NE(nullptr, r);
        EXPECT_EQ(&n, r);
    }

    TYPED_TEST(intrusive_double_list_test, back)
    {
        using namespace nghung;
        list<TypeParam> l;
        TypeParam n;
        l.push_back(n);
        TypeParam n2;
        l.push_back(n2);
        TypeParam *r(l.back());
        EXPECT_EQ(r, &n2);
        EXPECT_NE(r, &n);
    }

    TYPED_TEST(intrusive_double_list_test, back_const)
    {
        using namespace nghung;
        list<TypeParam> l;
        TypeParam n;
        l.push_back(n);
        const TypeParam *r(l.back());
        EXPECT_EQ(r, &n);
    }

    TYPED_TEST(intrusive_double_list_test, size)
    {
        using namespace nghung;
        list<TypeParam> l;
        TypeParam n;
        l.push_front(n);
        TypeParam n1;
        l.push_back(n1);
        TypeParam n2;
        l.push_back(n2);
        EXPECT_EQ(3, l.size());
    }

    TYPED_TEST(intrusive_double_list_test, empty)
    {
        using namespace nghung;
        list<TypeParam> l;
        EXPECT_TRUE(l.empty());
        TypeParam n;
        l.push_back(n);
        TypeParam n1;
        l.push_front(n1);
        EXPECT_FALSE(l.empty());
        l.pop_front();
        l.pop_back();
        EXPECT_TRUE(l.empty());
    }

    TYPED_TEST(intrusive_double_list_test, clear)
    {
        using namespace nghung;
        list<TypeParam> l;
        TypeParam n;
        TypeParam n1;
        TypeParam n2;
        l.push_back(n);
        l.push_front(n1);
        l.push_back(n2);
        EXPECT_EQ(3, l.size());
        EXPECT_NE(nullptr, l.front());
        EXPECT_NE(nullptr, l.back());
        l.clear();
        EXPECT_EQ(0, l.size());
        EXPECT_EQ(nullptr, l.front());
        EXPECT_EQ(nullptr, l.back());
    }

    TYPED_TEST(intrusive_double_list_test, push_front_empty_list)
    {
        using namespace nghung;
        list<TypeParam> l;
        EXPECT_EQ(0, l.size());
        TypeParam n;
        l.push_front(n);
        TypeParam *r{l.front()};
        EXPECT_EQ(r, &n);
        EXPECT_EQ(l.back(), &n);
    }

    TYPED_TEST(intrusive_double_list_test, push_front_non_empty_list)
    {
        using namespace nghung;
        list<TypeParam> l;
        TypeParam n;
        TypeParam n1;
        l.push_back(n);
        EXPECT_EQ(l.front(), &n);
        l.push_front(n1);
        EXPECT_EQ(l.front(), &n1);
    }

    TYPED_TEST(intrusive_double_list_test, push_front_invalid_item)
    {
        using namespace nghung;
        // TODO  push_front_invalid_item, ? what is an invalid item?
    }

    TYPED_TEST(intrusive_double_list_test, push_back_to_empty_list)
    {
        using namespace nghung;
        list<TypeParam> l;
        TypeParam n;
        l.push_back(n);
        EXPECT_EQ(&n, l.front());
        EXPECT_EQ(&n, l.back());
    }

    TYPED_TEST(intrusive_double_list_test, push_back_to_non_empty_list)
    {
        using namespace nghung;
        list<TypeParam> l;
        TypeParam n;
        l.push_front(n);
        TypeParam n1;
        l.push_back(n1);
        EXPECT_EQ(&n, l.front());
        EXPECT_EQ(&n1, l.back());
        EXPECT_EQ(n.next, &n1);
    }

    TYPED_TEST(intrusive_double_list_test, push_back_invalid_item)
    {
        using namespace nghung;
        // TODO  push_back_invalid_item,
    }

    TYPED_TEST(intrusive_double_list_test, push_next_to_empty_list)
    {
        using namespace nghung;
        // TODO push_next_to_empty_list, what is the expected behavior?
        list<TypeParam> l;
        TypeParam base;
        TypeParam n;
        l.push_next(base, n);
        // EXPECT_EQ(&base, l.front());
    }

    TYPED_TEST(intrusive_double_list_test, push_next_to_non_empty_list)
    {
        using namespace nghung;
        list<TypeParam> l;
        TypeParam n;
        l.push_back(n);
        TypeParam n1;
        l.push_next(n, n1);
        EXPECT_EQ(n.next, &n1);
        TypeParam n2;
        l.push_next(n, n2);
        EXPECT_EQ(n.next, &n2);
        EXPECT_NE(n.next, &n1);
        EXPECT_EQ(n.prev, nullptr);
        EXPECT_EQ(n1.prev, &n2);
    }

    TYPED_TEST(intrusive_double_list_test, push_next_invalid_item)
    {
        using namespace nghung;
        // TODO  push_next_invalid_item, what is an invalid item
    }

    TYPED_TEST(intrusive_double_list_test, push_next_invalid_base)
    {
        using namespace nghung;
        // TODO  push_next_invalid_base, what is an invalid item
    }

    TYPED_TEST(intrusive_double_list_test, push_prev_to_empty_list)
    {
        using namespace nghung;
        // TODO push_prev_to_empty_list, what is the expected behavior
    }

    TYPED_TEST(intrusive_double_list_test, push_prev_to_non_empty_list)
    {
        using namespace nghung;
        list<TypeParam> l;
        TypeParam n;
        l.push_back(n);
        TypeParam n1;
        l.push_prev(n, n1);
        EXPECT_EQ(n1.prev, nullptr);
        EXPECT_EQ(&n1, l.front());
        EXPECT_EQ(n1.next, &n);
        EXPECT_EQ(n.prev, &n1);
        EXPECT_NE(&n, l.front());
    }

    TYPED_TEST(intrusive_double_list_test, push_prev_invalid_item)
    {
        using namespace nghung;
        // TODO  push_prev_invalid_item,
    }

    TYPED_TEST(intrusive_double_list_test, push_prev_invalid_base)
    {
        using namespace nghung;
        // TODO  push_prev_invalid_base,
    }

    TYPED_TEST(intrusive_double_list_test, pop)
    {
        using namespace nghung;
        list<TypeParam> l;
        TypeParam n1, n2, n3, n4, n5;
        l.push_back(n1);
        l.push_back(n2);
        l.push_back(n3);
        l.push_back(n4);
        l.push_back(n5);

        TypeParam *r{l.pop(n3)};
        EXPECT_EQ(r, &n3);
        EXPECT_EQ(r->prev, nullptr);
        EXPECT_EQ(r->next, nullptr);
        EXPECT_EQ(n3.prev, nullptr);
        EXPECT_EQ(n3.next, nullptr);
        EXPECT_EQ(n2.next, &n4);
        EXPECT_EQ(n4.prev, &n2);
    }

    TYPED_TEST(intrusive_double_list_test, pop_invalid_item)
    {
        using namespace nghung;
        list<TypeParam> l;
        TypeParam n1, n2, n3, n4, n5;
        l.push_front(n1);
        l.push_front(n2);
        l.push_front(n4);
        l.push_front(n5);
        // TODO pop invalid item, but it was suppose not to check error
    }

    TYPED_TEST(intrusive_double_list_test, pop_front_empty_list)
    {
        using namespace nghung;
        list<TypeParam> l;
        TypeParam *r{l.pop_front()};
        EXPECT_EQ(r, nullptr);
    }

    TYPED_TEST(intrusive_double_list_test, pop_front_non_empty_list)
    {
        using namespace nghung;
        list<TypeParam> l;
        TypeParam n1, n2, n3, n4;
        l.push_back(n1);
        l.push_front(n2);
        l.push_back(n3);
        l.push_back(n4);
        TypeParam *r(l.pop_front());
        EXPECT_EQ(r, &n2);
    }

    TYPED_TEST(intrusive_double_list_test, pop_back_empty_list)
    {
        using namespace nghung;
        list<TypeParam> l;
        EXPECT_EQ(nullptr, l.pop_back());
    }

    TYPED_TEST(intrusive_double_list_test, pop_back_non_empty_list)
    {
        using namespace nghung;

        // TODO pop_back_non_empty_list
    }

    TYPED_TEST(intrusive_double_list_test, pop_next_to_empty_list)
    {
        using namespace nghung;
        list<TypeParam> l;
        TypeParam n1, n2, n3, n4;
        l.push_back(n1);
        l.push_front(n2);
        l.push_back(n3);
        l.push_back(n4);
        TypeParam *r(l.pop_back());
        EXPECT_EQ(r, &n4);
    }

    TYPED_TEST(intrusive_double_list_test, pop_next_to_non_empty_list)
    {
        using namespace nghung;
        list<TypeParam> l;
        TypeParam n1, n2, n3, n4;
        l.push_back(n1);
        l.push_front(n2);
        l.push_back(n3);
        l.push_back(n4);
        TypeParam *r(l.pop_next(n2));
        EXPECT_EQ(r, &n1);
    }

    TYPED_TEST(intrusive_double_list_test, pop_next_invalid_item)
    {
        using namespace nghung;
        // TODO  pop_next_invalid_item,
    }

    TYPED_TEST(intrusive_double_list_test, pop_next_invalid_base)
    {
        using namespace nghung;
        // TODO  pop_next_invalid_base,
    }

    TYPED_TEST(intrusive_double_list_test, pop_prev_to_empty_list)
    {
        using namespace nghung;
        // TODO pop_prev_to_empty_list
    }

    TYPED_TEST(intrusive_double_list_test, pop_prev_to_non_empty_list)
    {
        using namespace nghung;
        list<TypeParam> l;
        TypeParam n1, n2, n3, n4;
        l.push_back(n1);
        l.push_front(n2);
        l.push_back(n3);
        l.push_back(n4);
        TypeParam *r(l.pop_prev(n2));
        EXPECT_EQ(r, nullptr);
        EXPECT_EQ(4, l.size());
        EXPECT_EQ(&n1, l.pop_prev(n3));
        EXPECT_EQ(3, l.size());
    }

    TYPED_TEST(intrusive_double_list_test, pop_prev_invalid_item)
    {
        using namespace nghung;
        // TODO  pop_prev_invalid_item,
    }

    TYPED_TEST(intrusive_double_list_test, pop_prev_invalid_base)
    {
        using namespace nghung;
        // TODO  pop_prev_invalid_base,
    }

    TYPED_TEST(intrusive_double_list_test, swap)
    {
        using namespace nghung;
        list<TypeParam> l1;
        list<TypeParam> l2;
        TypeParam n1, n2, n3, n4;
        TypeParam m1, m2, m3, m4;
        l1.push_back(n1);
        l1.push_back(n2);
        l1.push_back(n3);
        l1.push_back(n4);
        l2.push_back(m1);
        l2.push_back(m2);
        l2.push_back(m3);
        l2.push_back(m4);
        l1.swap(l2);
        EXPECT_EQ(l1.front(), &m1);
        EXPECT_EQ(l2.front(), &n1);
    }

    TYPED_TEST(intrusive_double_list_test, swap_friend)
    {
        using namespace nghung;
        list<TypeParam> l1;
        list<TypeParam> l2;
        TypeParam n1, n2, n3, n4;
        TypeParam m1, m2, m3, m4;
        l1.push_back(n1);
        l1.push_back(n2);
        l1.push_back(n3);
        l1.push_back(n4);
        l2.push_back(m1);
        l2.push_back(m2);
        l2.push_back(m3);
        l2.push_back(m4);
        swap(l1, l2);
        EXPECT_EQ(l1.front(), &m1);
        EXPECT_EQ(l2.front(), &n1);
    }

    TYPED_TEST(intrusive_double_list_test, itr_begin)
    {
        using namespace nghung;
        list<TypeParam> l;
        TypeParam n1, n2, n3, n4;
        n1.price = 24;
        l.push_back(n1);
        l.push_back(n2);
        l.push_back(n3);
        l.push_back(n4);

        auto l_itr{l.begin()};
        EXPECT_EQ(l_itr->price, n1.price);
    }

    TYPED_TEST(intrusive_double_list_test, itr_end)
    {
        using namespace nghung;
        list<TypeParam> l;
        auto begin{l.begin()};
        TypeParam n1, n2, n3, n4;
        n4.price = 24;
        l.push_back(n1);
        l.push_back(n2);
        l.push_back(n3);
        l.push_back(n4);
        auto end{l.end()};
        EXPECT_EQ(begin, end);
        begin = l.begin();
        EXPECT_NE(begin, end);
    }

    TYPED_TEST(intrusive_double_list_test, iterator_default_contructor)
    {
        using namespace nghung;
        // TODO iterator(), necessary?
    }

    TYPED_TEST(intrusive_double_list_test, iterator_pointer_contructor)
    {
        using namespace nghung;
        // TODO iterator_pointer_constructor(), necessary?
    }

    TYPED_TEST(intrusive_double_list_test, iterator_pre_increament)
    {
        using namespace nghung;
        // TODO iterator ++()
        list<TypeParam> l;
        TypeParam n1, n2, n3, n4;
        n1.price = 34;
        n2.price = 56;
        n3.price = 78;
        n4.price = 90;
        l.push_back(n1);
        l.push_back(n2);
        l.push_back(n3);
        l.push_back(n4);
        auto begin{l.begin()};
        EXPECT_EQ(begin->price, n1.price);
        ++begin;
        EXPECT_EQ(begin->price, n2.price);
    }

    TYPED_TEST(intrusive_double_list_test, iterator_post_increament)
    {
        using namespace nghung;
        // TODO iterator ++(int)
        list<TypeParam> l;
        TypeParam n1, n2, n3, n4;
        n1.price = 34;
        n2.price = 56;
        n3.price = 78;
        n4.price = 90;
        l.push_back(n1);
        l.push_back(n2);
        l.push_back(n3);
        l.push_back(n4);
        auto begin{l.begin()};
        EXPECT_EQ(begin->price, n1.price);
        begin++;
        EXPECT_EQ(begin->price, n2.price);
    }

    TYPED_TEST(intrusive_double_list_test, iterator_pointer)
    {
        using namespace nghung;
        // TODO iterator ->
    }

    TYPED_TEST(intrusive_double_list_test, iterator_reference)
    {
        using namespace nghung;
        // TODO iterator *
    }
} // namespace nghung_test
