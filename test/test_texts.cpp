#include "ttext.h"
#include "ttextlink.h"
#include <gtest.h>

TEST(TText, can_ins_down_line)
{
    TTextLink::InitMemSystem();
    TText txt;
    txt.InsDownLine("check");
    txt.GoDownLink();

    EXPECT_EQ("check", txt.GetLine());
}

TEST(TText, can_ins_down_section)
{
    TTextLink::InitMemSystem();
    TText txt;
    txt.InsDownLine("check1");
    txt.InsDownSection("check2");
    txt.GoDownLink();

    EXPECT_EQ("check2", txt.GetLine());
}

TEST(TText, can_ins_next_line)
{
    TTextLink::InitMemSystem();
    TText txt;
    txt.InsNextLine("check");
    txt.GoNextLink();

    EXPECT_EQ("check", txt.GetLine());
}

TEST(TText, can_ins_next_section)
{
    TTextLink::InitMemSystem();
    TText txt;
    txt.InsNextLine("check1");
    txt.InsNextSection("check2");
    txt.GoNextLink();

    EXPECT_EQ("check2", txt.GetLine());
}

TEST(TText, can_del_down_line)
{
    TTextLink::InitMemSystem();
    TText txt;
    txt.InsDownLine("check");
    txt.DelDownLine();

    ASSERT_ANY_THROW(txt.GoDownLink());
}

TEST(TText, can_del_down_section)
{
    TTextLink::InitMemSystem();
    TText txt;
    txt.InsDownLine("check1");
    txt.InsDownSection("check2");
    txt.DelDownSection();

    ASSERT_ANY_THROW(txt.GoDownLink());
}

TEST(TText, can_del_next_line)
{
    TTextLink::InitMemSystem();
    TText txt;
    txt.InsNextLine("check");
    txt.DelNextLine();

    ASSERT_ANY_THROW(txt.GoNextLink());
}

TEST(TText, can_del_next_section)
{
    TTextLink::InitMemSystem();
    TText txt;
    txt.InsNextLine("check1");
    txt.InsNextSection("check2");
    txt.DelNextSection();

    ASSERT_ANY_THROW(txt.GoNextLink());
}

TEST(TText, can_go_first_link)
{
    TTextLink::InitMemSystem();
    TText txt;
    txt.SetLine("check1");
    txt.InsNextLine("check2");
    txt.InsDownLine("check3");
    txt.GoNext();
    txt.GoNext();
    txt.GoFirstLink();

    EXPECT_EQ("check1", txt.GetLine());
}
