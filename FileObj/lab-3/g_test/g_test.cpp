#include "./gmock/gmock.h"
#include "./gtest/gtest.h"
#include "../include/source/container.cc"
#include "../include/source/item.cc"

TEST(TEST__I, operator_and_swap)
{
    file a("123", 123, 123 ,123);
    cataloge b("1234", 1234, 1234, 1234);
    cataloge c("1234", 1234, 1234, 1234);
    
    std::unique_ptr<item> d = a.clone();

    ASSERT_EQ(d->get_bytes(), 123);
    ASSERT_EQ(d->get_id(), 123);
    ASSERT_EQ(d->get_id_p(), 123);
    ASSERT_STREQ(d->get_name().c_str(), "123");
    ASSERT_EQ(d->is_file(), 1);

    a.swap(b);
    ASSERT_EQ(b.get_bytes(), 123);
    ASSERT_EQ(b.get_id(), 123);
    ASSERT_EQ(b.get_id_p(), 123);
    ASSERT_STREQ(b.get_name().c_str(), "123");

    ASSERT_EQ(a.get_bytes(), 1234);
    ASSERT_EQ(a.get_id(), 1234);
    ASSERT_EQ(a.get_id_p(), 1234);
    ASSERT_STREQ(a.get_name().c_str(), "1234");

    a.swap(b);

    ASSERT_TRUE(a != b);
    ASSERT_FALSE(a == b);

    ASSERT_TRUE(b == c);
    ASSERT_FALSE(b != c);
}

TEST(TEST_C, index)
{
    container a;
    ASSERT_ANY_THROW(a[0]);
    ASSERT_ANY_THROW(a[1]);
    ASSERT_ANY_THROW(a[-1]);
    
    ASSERT_ANY_THROW(a[-1]);
    ASSERT_ANY_THROW(a[0]);
    ASSERT_ANY_THROW(a[1]);
    
    ASSERT_ANY_THROW(a.create_cataloge(1, "123", 123, 12));
    ASSERT_ANY_THROW(a.create_file(1, "123", 123, 12, 12));
    ASSERT_ANY_THROW(a.create_cataloge(-1, "123", 123, 12));
    ASSERT_ANY_THROW(a.create_file(-1, "123", 123, 12, 12));

    ASSERT_NO_THROW(a.create_file(0, "123", 123, 12, 123));
    ASSERT_NO_THROW(a.create_cataloge(0, "123", 1234, 12));

    ASSERT_EQ(a.get_size(), 2);

    ASSERT_ANY_THROW(a.remove_all(2));
    ASSERT_ANY_THROW(a.remove_all(-1));
    
    ASSERT_NO_THROW(a.remove_all(0));
    ASSERT_NO_THROW(a.remove_all(0));

    ASSERT_EQ(a.get_size(), 0);

    ASSERT_ANY_THROW(a.get_bytes(0));
    ASSERT_ANY_THROW(a.remove_all(-1));
    ASSERT_ANY_THROW(a.get_bytes(1));

    ASSERT_NO_THROW(a.create_file(0, "123", 123, 12, 123));
    ASSERT_NO_THROW(a.create_cataloge(0, "123", 1234, 12));

    ASSERT_EQ(a.get_size(), 2);

    ASSERT_EQ(a[0]->get_bytes(), 0);
    ASSERT_EQ(a[0]->get_id(), 1234);
    ASSERT_EQ(a[0]->get_id_p(),12);
    ASSERT_EQ(a[0]->is_file(), 0);
    ASSERT_STREQ(a[0]->get_name().c_str(), "123");

    ASSERT_EQ(a[1]->get_bytes(), 123);
    ASSERT_EQ(a[1]->get_id(), 123);
    ASSERT_EQ(a[1]->get_id_p(),12);
    ASSERT_EQ(a[1]->is_file(), 1);
    ASSERT_STREQ(a[1]->get_name().c_str(), "123");

    ASSERT_NO_THROW(a.get_bytes(0));
    
    ASSERT_NO_THROW(a.remove_all(0));
    ASSERT_EQ(a[0]->get_bytes(), 123);
    ASSERT_EQ(a[0]->get_id(), 123);
    ASSERT_EQ(a[0]->get_id_p(),12);
    ASSERT_EQ(a[0]->is_file(), 1);
    ASSERT_STREQ(a[0]->get_name().c_str(), "123");

    ASSERT_NO_THROW(a.create_file(1, "123", 12345, 0, 123));
    ASSERT_EQ(a[1]->get_bytes(), 123);
    ASSERT_EQ(a[1]->get_id(), 12345);
    ASSERT_EQ(a[1]->get_id_p(),0);
    ASSERT_EQ(a[1]->is_file(), 1);
    ASSERT_STREQ(a[1]->get_name().c_str(), "123");
}

TEST(TEST_C, Input)
{
    container cont;

    ASSERT_ANY_THROW(cont.create_cataloge(0, "123", 123, 123));
    ASSERT_ANY_THROW(cont.create_file(0, "123", 123, 123, 20));

    ASSERT_NO_THROW(cont.create_cataloge(0, "123", 1, 0));
    ASSERT_ANY_THROW(cont.create_cataloge(0, "123", 2, 0));
    ASSERT_ANY_THROW(cont.create_cataloge(0, "1234", 1, 0));

    ASSERT_ANY_THROW(cont.create_file(0, "123", 1, 0, 12));

    ASSERT_NO_THROW(cont.create_file(0, "123", 2, 0, 12));
    ASSERT_ANY_THROW(cont.create_file(0, "123", 2, 0, 12));
    ASSERT_ANY_THROW(cont.create_file(0, "1234", 1, 0, 12));
    
    ASSERT_ANY_THROW(cont.search_id(3));
    ASSERT_NO_THROW(cont.search_id(1));
    ASSERT_NO_THROW(cont.search_id(2));

    ASSERT_TRUE(cont.path(1) == "~/123");
    ASSERT_TRUE(cont.path(2) == "~/123");

    ASSERT_NO_THROW(cont.create_file(0, "1234", 3, 1, 20));
    ASSERT_TRUE(cont.path(3) == "~/123/1234");

    ASSERT_ANY_THROW(cont.create_cataloge(0, "12356", 100, 2));
    ASSERT_ANY_THROW(cont.create_file(0, "12356", 100, 2, 20));
}

TEST(TEST_C, REMOVE)
{
    container cont;
    cont.create_file(0, "Nikita", 100, 0, 20);
    cont.create_cataloge(0, "Photo", 1, 0);
    cont.create_file(1, "program.cpp", 11, 1, 20);
    cont.create_file(2, "Pictures", 12, 1, 20);
    cont.create_cataloge(3, "Pictures", 2, 1);
    cont.create_file(4, "file", 21, 2, 20);

    cont.remove_all(0);

    ASSERT_EQ(cont.get_size(), 1);
    
    ASSERT_TRUE(*cont[0]->clone() == file("Nikita", 100, 0, 20));
}