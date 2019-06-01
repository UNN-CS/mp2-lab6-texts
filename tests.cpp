#include <gtest.h>

#include "TTextLink.h"
#include "TText.h"

TEST(TTextLink, can_init_memory)
{
    ASSERT_NO_THROW(TTextLink::InitMemSystem());
}

TEST(TTextLink, can_create_textlink)
{
    TTextLink::InitMemSystem();
    ASSERT_NO_THROW(TTextLink t("hello"));
}


TEST(TTextLink, can_get_copy)
{
    TTextLink::InitMemSystem();
    TTextLink t("hello");
    ASSERT_NO_THROW(PTTextLink t2 = (PTTextLink)t.GetCopy());
}

TEST(TText, can_create_ttext)
{
    TTextLink::InitMemSystem();
    ASSERT_NO_THROW(TText t);
}

TEST(TText, can_get_line)
{
    TTextLink::InitMemSystem();
    TText t;
    t.SetLine("hello");
    ASSERT_NO_THROW(t.GetLine());
}

TEST(TText, can_set_line)
{
    TTextLink::InitMemSystem();
    TText t;
    ASSERT_NO_THROW(t.SetLine("hello"));
}

TEST(TText, getline_returns_correct_str_from_empty_text)
{
    TTextLink::InitMemSystem();
    TText t;
    EXPECT_EQ("", t.GetLine());
}

TEST(TText, getline_returns_correct_elem)
{
    TTextLink::InitMemSystem();
    TText t;
    t.SetLine("hello");
    EXPECT_EQ("hello", t.GetLine());
}

TEST(TText, insdownline_and_godownlink_work_correct)
{
    TTextLink::InitMemSystem();
    TText t;
    t.InsDownLine("hello");
    t.GoDownLink();
    EXPECT_EQ("hello", t.GetLine());
}

TEST(TText, insnextline_and_gonextlink_work_correct)
{
    TTextLink::InitMemSystem();
    TText t;
    t.InsNextLine("hello");
    t.GoNextLink();
    EXPECT_EQ("hello", t.GetLine());
}

TEST(TText, insdownsection_works_correct)
{
    TTextLink::InitMemSystem();
    TText t;
    t.InsDownSection("hello");
    t.GoDownLink();
    EXPECT_EQ("hello", t.GetLine());
}

TEST(TText, insnextsection_works_correct)
{
    TTextLink::InitMemSystem();
    TText t;
    t.InsNextLine("hello");
    t.GoNextLink();
    EXPECT_EQ("hello", t.GetLine());
}

TEST(TText, gofirstlink_works_correct)
{
    TTextLink::InitMemSystem();
    TText t;
    t.SetLine("dear");
    t.InsNextLine("hello");
    t.GoNextLink();
    t.GoFirstLink();
    EXPECT_EQ("dear", t.GetLine());
}

TEST(TText, goprevlink_works_correct)
{
    TTextLink::InitMemSystem();
    TText t;
    t.SetLine("dear");
    t.InsNextLine("hello");
    t.GoNextLink();
    t.GoPrevLink();
    EXPECT_EQ("dear", t.GetLine());
}

TEST(TText, cant_go_prev_if_path_is_empty)
{
    TTextLink::InitMemSystem();
    TText t;
    ASSERT_ANY_THROW(t.GoPrevLink());
}

TEST(TText, can_del_down_line)
{
    TTextLink::InitMemSystem();
    TText t;
    t.InsDownLine("hello");
    ASSERT_NO_THROW(t.DelDownLine());
    ASSERT_ANY_THROW(t.GoDownLink());
}

TEST(TText, can_del_down_section)
{
    TTextLink::InitMemSystem();
    TText t;
    t.InsDownSection("hello");
    ASSERT_NO_THROW(t.DelDownSection());
    ASSERT_ANY_THROW(t.GoDownLink());
}

TEST(TText, can_del_next_line)
{
    TTextLink::InitMemSystem();
    TText t;
    t.InsNextLine("hello");
    ASSERT_NO_THROW(t.DelNextLine());
    ASSERT_ANY_THROW(t.GoNextLink());
}

TEST(TText, can_del_next_section)
{
    TTextLink::InitMemSystem();
    TText t;
    t.InsNextSection("hello");
    ASSERT_NO_THROW(t.DelNextSection());
    ASSERT_ANY_THROW(t.GoNextLink());
}

TEST(TText, can_get_copy)
{
    TTextLink::InitMemSystem();
    TText txt;
    txt.SetLine("hello");
    txt.InsDownLine("a");
    txt.InsDownLine("b");
    txt.InsDownLine("c");
    txt.InsNextLine("d");
    txt.InsNextLine("e");
    PTText txt2;
    ASSERT_NO_THROW(txt2 = txt.GetCopy());
}

TEST(TText, copied_text_has_its_own_memory)
{
    TTextLink::InitMemSystem();
    TText txt;
    txt.SetLine("hello");
    txt.InsDownLine("a");
    txt.InsNextLine("b");
    PTText txt2 = txt.GetCopy();
    txt.InsDownLine("c");
    txt.Reset();
    txt.GoDownLink();
    txt2->Reset();
    txt2->GoDownLink();
    EXPECT_NE(txt.GetLine(), txt2->GetLine());
}

TEST(TText, reset_function_works_correct)
{
    TTextLink::InitMemSystem();
    TText txt;
    txt.SetLine("hello");
    txt.InsDownLine("a");
    txt.InsNextLine("b");
    txt.Reset();
    EXPECT_EQ("hello", txt.GetLine());
}

TEST(TText, gonext_function_works_correct)
{
    TTextLink::InitMemSystem();
    TText txt;
    txt.SetLine("hello");
    txt.InsDownLine("a");
    txt.InsNextLine("b");
    txt.Reset();
    txt.GoNext();
    EXPECT_EQ("a", txt.GetLine());
    txt.GoNext();
    EXPECT_EQ("b", txt.GetLine());
    txt.GoNext();
    EXPECT_EQ("hello", txt.GetLine());
}

TEST(TText, istextended_function_works_correct)
{
    TTextLink::InitMemSystem();
    TText txt;
    txt.SetLine("hello");
    txt.InsDownLine("a");
    txt.InsNextLine("b");
    txt.Reset();
    txt.GoNext();
    txt.GoNext();
    txt.GoNext();
    txt.GoNext();

    EXPECT_EQ(1, txt.IsTextEnded());
}


