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
    ASSERT_NO_THROW(TTextLink t("wow"));
}


TEST(TTextLink, can_get_copy)
{
    TTextLink::InitMemSystem();
    TTextLink t("Wooow");
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
    ASSERT_NO_THROW(t.SetLine("WoW"));
}


TEST(TText, can_get_line)
{
    TTextLink::InitMemSystem();
    TText t;
    t.SetLine("wow");
    ASSERT_NO_THROW(t.GetLine());
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
    t.SetLine("wow");
    EXPECT_EQ("wow", t.GetLine());
}

TEST(TText, insdownline_and_godownlink_work_correct)
{
    TTextLink::InitMemSystem();
    TText t;
    t.InsDownLine("wow");
    t.GoDownLink();
    EXPECT_EQ("wow", t.GetLine());
}

TEST(TText, insnextline_and_gonextlink_work_correct)
{
    TTextLink::InitMemSystem();
    TText t;
    t.InsNextLine("wow");
    t.GoNextLink();
    EXPECT_EQ("wow", t.GetLine());
}

TEST(TText, insdownsection_works_correct)
{
    TTextLink::InitMemSystem();
    TText t;
    t.InsDownSection("wow");
    t.GoDownLink();
    EXPECT_EQ("wow", t.GetLine());
}

TEST(TText, insnextsection_works_correct)
{
    TTextLink::InitMemSystem();
    TText t;
    t.InsNextLine("wow");
    t.GoNextLink();
    EXPECT_EQ("wow", t.GetLine());
}

TEST(TText, gofirstlink_works_correct)
{
    TTextLink::InitMemSystem();
    TText t;
    t.SetLine("owo");
    t.InsNextLine("wow");
    t.GoNextLink();
    t.GoFirstLink();
    EXPECT_EQ("owo", t.GetLine());
}

TEST(TText, goprevlink_works_correct)
{
    TTextLink::InitMemSystem();
    TText t;
    t.SetLine("owo");
    t.InsNextLine("wow");
    t.GoNextLink();
    t.GoPrevLink();
    EXPECT_EQ("owo", t.GetLine());
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
    t.InsDownLine("wow");
    ASSERT_NO_THROW(t.DelDownLine());
    ASSERT_ANY_THROW(t.GoDownLink());
}

TEST(TText, can_del_down_section)
{
    TTextLink::InitMemSystem();
    TText t;
    t.InsDownSection("wow");
    ASSERT_NO_THROW(t.DelDownSection());
    ASSERT_ANY_THROW(t.GoDownLink());
}

TEST(TText, can_del_next_line)
{
    TTextLink::InitMemSystem();
    TText t;
    t.InsNextLine("wow");
    ASSERT_NO_THROW(t.DelNextLine());
    ASSERT_ANY_THROW(t.GoNextLink());
}

TEST(TText, can_del_next_section)
{
    TTextLink::InitMemSystem();
    TText t;
    t.InsNextSection("wow");
    ASSERT_NO_THROW(t.DelNextSection());
    ASSERT_ANY_THROW(t.GoNextLink());
}

TEST(TText, can_get_copy)
{
    TTextLink::InitMemSystem();
    TText txt;
    txt.SetLine("walrus");
    txt.InsDownLine("aba");
    txt.InsDownLine("caba");
    txt.InsDownLine("lul");
    txt.InsNextLine("lul2");
    txt.InsNextLine("lul4");
    PTText txt2;
    ASSERT_NO_THROW(txt2 = txt.GetCopy());
}

TEST(TText, copied_text_has_its_own_memory)
{
    TTextLink::InitMemSystem();
    TText txt;
    txt.SetLine("wow");
    txt.InsDownLine("aba");
    txt.InsNextLine("caba");
    PTText txt2 = txt.GetCopy();
    txt.InsDownLine("wal");
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
    txt.SetLine("wow");
    txt.InsDownLine("aba");
    txt.InsNextLine("caba");
    txt.Reset();
    EXPECT_EQ("wow", txt.GetLine());
}

TEST(TText, gonext_function_works_correct)
{
    TTextLink::InitMemSystem();
    TText txt;
    txt.SetLine("wow");
    txt.InsDownLine("aba");
    txt.InsNextLine("caba");
    txt.Reset();
    txt.GoNext();
    EXPECT_EQ("aba", txt.GetLine());
    txt.GoNext();
    EXPECT_EQ("caba", txt.GetLine());
    txt.GoNext();
    EXPECT_EQ("wow", txt.GetLine());
}

TEST(TText, istextended_function_works_correct)
{
    TTextLink::InitMemSystem();
    TText txt;
    txt.SetLine("wow");
    txt.InsDownLine("aba");
    txt.InsNextLine("caba");
    txt.Reset();
    txt.GoNext();
    txt.GoNext();
    txt.GoNext();
    txt.GoNext();
    EXPECT_EQ(1, txt.IsTextEnded());
}


