#include "gtest.h"

#include "textlink.h"
#include "text.h"

TEST(TTextLink, can_init_memory)
{
    ASSERT_NO_THROW(TTextLink::InitMemSystem());
}

TEST(TTextLink, can_create_ttextlink)
{
    TTextLink::InitMemSystem();
    ASSERT_NO_THROW(TTextLink t("Line"));
}

TEST(TTextLink, can_get_copy)
{
    TTextLink::InitMemSystem();
    TTextLink t("Line");
    ASSERT_NO_THROW(PTTextLink t2 = (PTTextLink)t.GetCopy());
}



TEST(TText, can_creat_ttext)
{
    TTextLink::InitMemSystem();
    ASSERT_NO_THROW(TText t);
}

TEST(TText, can_set_line)
{
    TTextLink::InitMemSystem();
    TText t;
    ASSERT_NO_THROW(t.SetLine("Line"));
}

TEST(TText, can_get_line)
{
    TTextLink::InitMemSystem();
    TText t;
    t.SetLine("Line");
    ASSERT_NO_THROW(t.GetLine());
}

TEST(TText, set_line_is_correct)
{
    TTextLink::InitMemSystem();
    TText t;
    t.SetLine("Line");
    ASSERT_EQ(t.GetLine(), "Line");
}

TEST(TText, getline_return_correct_str_from_empty_text)
{
    TTextLink::InitMemSystem();
    TText t;
    EXPECT_EQ("", t.GetLine());
}

TEST(TText, getline_return_correct_elem)
{
    TTextLink::InitMemSystem();
    TText t;
    t.SetLine("Line");
    EXPECT_EQ("Line", t.GetLine());
}

TEST(TText, insdownline_is_correct)
{
    TTextLink::InitMemSystem();
    TText t;
    t.InsDownLine("Line");
    t.GoDownLink();
    EXPECT_EQ("Line", t.GetLine());
}

TEST(TText, insdownsection_works_correct)
{
    TTextLink::InitMemSystem();
    TText t;
    t.InsDownSection("Line");
    t.GoDownLink();
    EXPECT_EQ("Line", t.GetLine());
}

TEST(TText, insnextsection_works_correct)
{
    TTextLink::InitMemSystem();
    TText t;
    t.InsNextLine("Line");
    t.GoNextLink();
    EXPECT_EQ("Line", t.GetLine());
}

TEST(TText, reset_is_correct)
{
	TTextLink::InitMemSystem();
	TText t;
	t.SetLine("1");
	t.InsDownLine("2");
	t.InsNextLine("3");
	t.Reset();
	EXPECT_EQ("1", t.GetLine());
}

TEST(TText, gofirstlink_works_correct)
{
    TTextLink::InitMemSystem();
    TText t;
    t.SetLine("Line1");
    t.InsNextLine("Line2");
    t.GoNextLink();
    t.GoFirstLink();
    EXPECT_EQ("Line1", t.GetLine());
}

TEST(TText, goprevlink_works_correct)
{
    TTextLink::InitMemSystem();
    TText t;
    t.SetLine("Line1");
    t.InsNextLine("Line2");
    t.GoNextLink();
    t.GoPrevLink();
    EXPECT_EQ("Line1", t.GetLine());
}

TEST(TText, can_get_copy)
{
    TTextLink::InitMemSystem();
    TText t;
    t.SetLine("1");
    t.InsDownLine("2");
    t.InsDownLine("3");
    t.InsDownLine("4");
    t.InsNextLine("5");
    t.InsNextLine("6");
    PTText t2;
    ASSERT_NO_THROW(t2 = t.GetCopy());
}

TEST(TText, copied_text_and_origin_text_is_two_dif_txt)
{
    TTextLink::InitMemSystem();
    TText t1;
    t1.SetLine("Line");
    PTText t2 = t1.GetCopy();
    EXPECT_NE(&t1, t2);
}
