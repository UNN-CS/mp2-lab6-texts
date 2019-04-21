#include <gtest.h>
#include "ttext.h"
#include "textlink.h"
#include <iostream>

TEST(TTextLink, can_create_link)
{
    TTextLink::InitMemSystem(120);
    ASSERT_NO_THROW(TTextLink a("priv"));
}