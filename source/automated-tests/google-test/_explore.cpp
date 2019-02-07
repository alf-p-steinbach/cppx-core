#pragma once    // Source encoding: UTF-8 with BOM (π is a lowercase Greek "pi").

#include <cppx-core/testing/google-test-framework.hpp>

namespace foo{
class MyTest : public ::testing::Test
{
protected:
    void SetUp() override {}
};

TEST_F( MyTest, UNGOOD_TEST_EXPLORER )
{
}

}
