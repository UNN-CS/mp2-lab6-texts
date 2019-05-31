#include  "gtest.h"
//#include "TText.h"
#include "TTextLink.h"

TEST(TTextLink, can_create_without_arguments) {
    ASSERT_NO_THROW(TTextLink tl());
}

TEST(TTextLink, can_init_mem) {
    ASSERT_NO_THROW(TTextLink::InitMemSystem());
}

TEST(TTextLink, can_create_with_one_argument) {
    TStr s = "my text";
    ASSERT_NO_THROW(TTextLink tl(s));
}


