#include <gtest.h>
#include "TText.h"

TEST(TText, can_create_empty_text)
{
    TTextLink::InitMemSystem(1);
    ASSERT_NO_THROW(TText tmp);
}

TEST(TText, copy_has_its_own_memory)
{
    TTextLink::InitMemSystem(3);
    PTTextLink pl = new TTextLink((char *)"copy", NULL, NULL);
    TText t1(pl);
    PTText cpy = t1.getCopy();
    EXPECT_NE(&t1, cpy);
}

TEST(TText, can_getcopy)
{
    TTextLink::InitMemSystem(3);
    PTTextLink pl = new TTextLink((char *)"copy", NULL, NULL);
    TText t1(pl);
    PTText cpy = t1.getCopy();
    string s = t1.GetLine();
    s = cpy->GetLine();
    EXPECT_EQ(t1.GetLine(), cpy->GetLine());
}

TEST(TText, new_text_ret_code_OK)
{
    TTextLink::InitMemSystem(1);
    PTTextLink pLink = new TTextLink((char *)"str");
    TText tmp(pLink);
    EXPECT_EQ(TextOK, tmp.GetRetCode());
}

/* Access */

TEST(TText, can_get_set_line)
{
    TTextLink::InitMemSystem(1);
    PTTextLink pLink = new TTextLink((char *)"str");
    TText tmp(pLink);
    tmp.SetLine((char *)"fire");
    EXPECT_EQ("fire", tmp.GetLine());
}
/* Insertion */
TEST(TText, can_ins_next_line)
{
    TTextLink::InitMemSystem(2);
    PTTextLink pLink = new TTextLink((char *)"str");
    TText tmp(pLink);
    tmp.InsNextLine((char *)"str11");
    EXPECT_EQ(TextOK, tmp.GetRetCode());
}

TEST(TText, can_ins_next_section)
{
    TTextLink::InitMemSystem(2);
    PTTextLink pLink = new TTextLink((char *)"str");
    TText tmp(pLink);
    tmp.InsNextSection((char *)"str11");
    EXPECT_EQ(TextOK, tmp.GetRetCode());
}

TEST(TText, can_ins_down_line)
{
    TTextLink::InitMemSystem(2);
    PTTextLink pLink = new TTextLink((char *)"str");
    TText tmp(pLink);
    tmp.InsDownLine((char *)"str11");
    EXPECT_EQ(TextOK, tmp.GetRetCode());
}

TEST(TText, can_ins_down_section)
{
    TTextLink::InitMemSystem(2);
    PTTextLink pLink = new TTextLink((char *)"str");
    TText tmp(pLink);
    tmp.InsDownSection((char *)"str11");
    EXPECT_EQ(TextOK, tmp.GetRetCode());
}

/*Navigation*/

TEST(TText, can_go_frist_link)
{
    TTextLink::InitMemSystem(2);
    PTTextLink pNext = new TTextLink((char *)"strNext", NULL, NULL);
    PTTextLink pLink = new TTextLink((char *)"str", pNext, NULL);
    TText tmp(pLink);
    tmp.GoFirstLink();
    EXPECT_STREQ("str", tmp.GetLine().c_str());
}

TEST(TText, can_go_down_link)
{
    TTextLink::InitMemSystem(2);
    PTTextLink pDown = new TTextLink((char *)"str2", NULL, NULL);
    PTTextLink pLink = new TTextLink((char *)"str", NULL, pDown);
    TText tmp(pLink);
    tmp.GoDownLink();
    EXPECT_STREQ("str2", tmp.GetLine().c_str());
}

TEST(TText, can_go_next_link)
{
    TTextLink::InitMemSystem(2);
    PTTextLink pNext = new TTextLink((char *)"strNext", NULL, NULL);
    PTTextLink pLink = new TTextLink((char *)"str", pNext, NULL);
    TText tmp(pLink);
    tmp.GoNextLink();
    EXPECT_STREQ("strNext", tmp.GetLine().c_str());
}

TEST(TText, can_go_prev_link)
{
    TTextLink::InitMemSystem(3);
    PTTextLink pNext2 = new TTextLink((char *)"strNext2", NULL, NULL);
    PTTextLink pNext = new TTextLink((char *)"strNext", pNext2, NULL);
    PTTextLink pLink = new TTextLink((char *)"str", pNext, NULL);
    TText tmp(pLink);
    tmp.GoNextLink();
    tmp.GoNextLink();
    tmp.GoPrevLink();
    EXPECT_STREQ("strNext", tmp.GetLine().c_str());
}

/* Deleting */
TEST(TText, can_delete_down_line)
{
    TTextLink::InitMemSystem(2);
    PTTextLink pDown = new TTextLink((char *)"strDown", NULL, NULL);
    PTTextLink pLink = new TTextLink((char *)"str", NULL, pDown);
    TText tmp(pLink);
    tmp.DelDownLine();
    tmp.GoDownLink();
    EXPECT_EQ(TextError, tmp.GetRetCode());
}

TEST(TText, can_delete_down_section)
{
    TTextLink::InitMemSystem(2);
    PTTextLink pDown = new TTextLink((char *)"strDown", NULL, NULL);
    PTTextLink pLink = new TTextLink((char *)"str", NULL, pDown);
    TText tmp(pLink);
    tmp.DelDownSection();
    tmp.GoDownLink();
    EXPECT_EQ(TextError, tmp.GetRetCode());
}

TEST(TText, can_delete_next_line)
{
    TTextLink::InitMemSystem(2);
    PTTextLink pNext = new TTextLink((char *)"strDown", NULL, NULL);
    PTTextLink pLink = new TTextLink((char *)"str", pNext, NULL);
    TText tmp(pLink);
    tmp.DelNextLine();
    tmp.GoNextLink();
    EXPECT_EQ(TextError, tmp.GetRetCode());
}

TEST(TText, can_delete_next_section)
{
    TTextLink::InitMemSystem(2);
    PTTextLink pNext = new TTextLink((char *)"strDown", NULL, NULL);
    PTTextLink pLink = new TTextLink((char *)"str", pNext, NULL);
    TText tmp(pLink);
    tmp.DelNextSection();
    tmp.GoNextLink();
    EXPECT_EQ(TextError, tmp.GetRetCode());
}

/* Iterator */
TEST(TText, can_detect_text_ended)
{
    TTextLink::InitMemSystem(1);
    PTTextLink pLink = new TTextLink((char *)"str", NULL, NULL);
    TText tmp(pLink);
    EXPECT_TRUE(tmp.IsTextEnded());
}
TEST(TText, can_reset)
{
    TTextLink::InitMemSystem(2);
    PTTextLink pNext = new TTextLink((char *)"strDown", NULL, NULL);
    PTTextLink pLink = new TTextLink((char *)"str", pNext, NULL);
    TText tmp(pLink);
    tmp.Reset();
    EXPECT_STREQ("str", tmp.GetLine().c_str());
}

TEST(TText, can_go_next)
{
    TTextLink::InitMemSystem(3);
    PTTextLink pNext2 = new TTextLink((char *)"strNext2", NULL, NULL);
    PTTextLink pNext = new TTextLink((char *)"strNext1", pNext2, NULL);
    PTTextLink pLink = new TTextLink((char *)"str", pNext, NULL);
    TText tmp(pLink);
    tmp.Reset();
    tmp.GoNext();
    EXPECT_STREQ("strNext1", tmp.GetLine().c_str());
}

/* Work with files */

TEST(TText, can_read_from_file)
{
    TTextLink::InitMemSystem(10);
    PTTextLink pNext = new TTextLink((char *)"strDown", NULL, NULL);
    PTTextLink pLink = new TTextLink((char *)"str", pNext, NULL);
    TText tmp(pLink);
    ASSERT_NO_THROW(tmp.Read((char *)"file.txt"));
}

TEST(TText, can_write_to_file)
{
    TTextLink::InitMemSystem(10);
    PTTextLink pNext = new TTextLink((char *)"strDown", NULL, NULL);
    PTTextLink pLink = new TTextLink((char *)"str", pNext, NULL);
    TText tmp(pLink);
    ASSERT_NO_THROW(tmp.Write((char *)"file.txt"));
}
TEST(TText, can_print_text)
{
    TTextLink::InitMemSystem(10);
    PTTextLink pNext = new TTextLink((char *)"strDown", NULL, NULL);
    PTTextLink pLink = new TTextLink((char *)"str", pNext, NULL);
    TText tmp(pLink);
    ASSERT_NO_THROW(tmp.Print());
}
