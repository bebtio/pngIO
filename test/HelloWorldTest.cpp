#include <gtest/gtest.h>
#include <string>

TEST( HelloWorldTest, FirstTest )
{
    std::string str("Hello World!");

    ASSERT_EQ(str, "Hello World!");
}