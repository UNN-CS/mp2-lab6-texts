#include <gtest.h>
#include "ttext.h"
#include "textlink.h"
#include <iostream>

TEST(TTextLink, can_create_link)
{
    TTextLink::InitMemSystem(120);
    ASSERT_NO_THROW(TTextLink a("priv"));
}

TEST(TText, can_create_ttext)
{
    TTextLink::InitMemSystem(120);
    ASSERT_NO_THROW(TText a);
}

TEST(TText, can_insert_down_line)
{
    TTextLink::InitMemSystem(120);
    TText a;
    ASSERT_NO_THROW(a.InsDownLine("privet"));
}

TEST(TText, can_insert_down_section)
{
    TTextLink::InitMemSystem(120);
    TText a;
    ASSERT_NO_THROW(a.InsDownSection("Mister Starrk I dont feel so good"));
}

TEST(TText, can_insert_next_line)
{
    TTextLink::InitMemSystem(120);
    TText a;
    ASSERT_NO_THROW(a.InsNextLine("privet"));
}

TEST(TText, can_insert_next_section)
{
    TTextLink::InitMemSystem(120);
    TText a;
    ASSERT_NO_THROW(a.InsNextSection("privet"));
}

TEST(TText, can_delete_down_line)
{
    TTextLink::InitMemSystem(120);
    TText a;
    a.InsDownLine("help");
    ASSERT_NO_THROW(a.DelDownLine());
}

TEST(TText, can_delete_down_section)
{
    TTextLink::InitMemSystem(120);
    TText a;
    a.InsDownSection("me");
    ASSERT_NO_THROW(a.DelDownSection());
}

TEST(TText, can_delete_next_line)
{
    TTextLink::InitMemSystem(120);
    TText a;
    a.InsNextLine("i'm");
    ASSERT_NO_THROW(a.DelNextLine());
}

TEST(TText, can_delete_next_section)
{
    TTextLink::InitMemSystem(120);
    TText a;
    a.InsDownLine("hungry");
    ASSERT_NO_THROW(a.DelNextSection());
}
