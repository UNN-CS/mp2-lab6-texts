#include <gtest.h>
#include "TText.h"


TEST(TText, can_init_mem)
{
    ASSERT_NO_THROW(TTextLink::InitMemSystem(40));
}

TEST(TText, can_create_TTextLink)
{
    TTextLink::InitMemSystem();
    ASSERT_NO_THROW(PTTextLink p = new TTextLink());
}

TEST(TText, can_create_TText)
{
    TTextLink::InitMemSystem();
    ASSERT_NO_THROW(TText a());
}

TEST(TText, can_read_head_of_text)
{
    TTextLink::InitMemSystem();
    PTTextLink p = new TTextLink("wal");
    TText a(p);
    ASSERT_NO_THROW(a.GetLine());
}

TEST(TText, line_in_text_is_correct)
{
    TTextLink::InitMemSystem();
    string s("wal");
    PTTextLink p = new TTextLink("wal");
    TText a(p);
    EXPECT_TRUE(s == a.GetLine());
}

TEST(TText, can_set_line)
{
    TTextLink::InitMemSystem();
    string s("wal");
    PTTextLink p = new TTextLink("abc");
    TText a(p);
    a.SetLine(s);
    EXPECT_TRUE(s == a.GetLine());
}

TEST(TText, can_InsDownLine)
{
    TTextLink::InitMemSystem();
    string s("wal");
    PTTextLink p = new TTextLink("abc");
    TText a(p);
    ASSERT_NO_THROW(a.InsDownLine(s));
}

TEST(TText, can_InsDownSection)
{
    TTextLink::InitMemSystem();
    string s("wal");
    PTTextLink p = new TTextLink("abc");
    TText a(p);
    ASSERT_NO_THROW(a.InsDownSection(s));
}

TEST(TText, can_InsNextLine)
{
    TTextLink::InitMemSystem();
    string s("wal");
    PTTextLink p = new TTextLink("abc");
    TText a(p);
    ASSERT_NO_THROW(a.InsNextLine(s));
}

TEST(TText, can_InsNextSection)
{
    TTextLink::InitMemSystem();
    string s("wal");
    PTTextLink p = new TTextLink("abc");
    TText a(p);
    ASSERT_NO_THROW(a.InsNextSection(s));
}

TEST(TText, can_DelDownLine)
{
    TTextLink::InitMemSystem();
    string s("wal");
    PTTextLink p = new TTextLink("abc");
    TText a(p);
    a.InsDownLine(s);
    ASSERT_NO_THROW(a.DelDownLine());
    EXPECT_EQ(1, a.GoDownLink());
}

TEST(TText, can_DelDownSection)
{
    TTextLink::InitMemSystem();
    string s("wal");
    PTTextLink p = new TTextLink("abc");
    TText a(p);
    a.InsDownSection(s);
    ASSERT_NO_THROW(a.DelDownSection());
    EXPECT_EQ(1, a.GoDownLink());
}

TEST(TText, can_DelNextLine)
{
    TTextLink::InitMemSystem();
    string s("wal");
    PTTextLink p = new TTextLink("abc");
    TText a(p);
    a.InsNextLine(s);
    ASSERT_NO_THROW(a.DelNextLine());
    EXPECT_EQ(1, a.GoNextLink());
}

TEST(TText, can_DelNextSection)
{
    TTextLink::InitMemSystem();
    string s("wal");
    PTTextLink p = new TTextLink("abc");
    TText a(p);
    a.InsNextSection(s);
    ASSERT_NO_THROW(a.DelNextSection());
    EXPECT_EQ(1, a.GoNextLink());
}

TEST(TText, can_GoFirstLink)
{
    TTextLink::InitMemSystem();
    string s("wal"), c("abc");
    PTTextLink p = new TTextLink("abc");
    TText a(p);
    a.InsNextLine(s);
    a.GoNextLink();
    a.GoFirstLink();
    EXPECT_TRUE(c == a.GetLine());
}

TEST(TText, can_GoDownLink)
{
    TTextLink::InitMemSystem();
    string s("wal");
    PTTextLink p = new TTextLink("abc");
    TText a(p);
    a.InsDownLine(s);
    EXPECT_EQ(0, a.GoDownLink());
    EXPECT_TRUE(s == a.GetLine());
}

TEST(TText, can_GoNextLink)
{
    TTextLink::InitMemSystem();
    string s("wal");
    PTTextLink p = new TTextLink("abc");
    TText a(p);
    a.InsNextLine(s);
    EXPECT_EQ(0, a.GoNextLink());
    EXPECT_TRUE(s == a.GetLine());
}

TEST(TText, can_GoPrevLink)
{
    TTextLink::InitMemSystem();
    string s("wal"), c("abc");
    PTTextLink p = new TTextLink("abc");
    TText a(p);
    a.InsNextLine(s);
    a.GoNextLink();
    EXPECT_EQ(0, a.GoPrevLink());
    EXPECT_TRUE(c == a.GetLine());
}

TEST(TText, can_Reset)
{
    TTextLink::InitMemSystem();
    string s("wal");
    PTTextLink p = new TTextLink("abc");
    TText a(p);
    a.InsNextLine(s);
    a.GoNext();
    EXPECT_EQ(0, a.Reset());
}

TEST(TText, can_GoNext)
{
    TTextLink::InitMemSystem();
    string s("wal");
    PTTextLink p = new TTextLink("abc");
    TText a(p);
    a.InsNextLine(s);
    a.Reset();
    a.GoNext();
    ASSERT_TRUE(s == a.GetLine());
}

TEST(TText, GoNext_is_correct)
{
    TTextLink::InitMemSystem();
    string s("wal");
    PTTextLink p = new TTextLink("abc");
    TText a(p);
    a.InsNextLine(s);
    a.Reset();
    a.GoNext();
    EXPECT_EQ(1, a.GoNext());
}

TEST(TText, can_GetCopy)
{
    TTextLink::InitMemSystem();
    string s("wal"), c("mg");
    PTTextLink p = new TTextLink("abc");
    TText a(p);
    a.InsNextLine(s);
    a.GoNextLink();
    a.InsDownSection(c);
    ASSERT_NO_THROW(a.GetCopy());
}

TEST(TText, copy_of_text_is_correct)
{
    TTextLink::InitMemSystem();
    string s("wal"), c("mg");
    PTTextLink p = new TTextLink("abc");
    TText a(p);
    a.InsNextLine(s);
    a.GoNextLink();
    a.InsDownSection(c);
    a.GoFirstLink();
    TText& q = *a.GetCopy();
    EXPECT_TRUE(a.GetLine() == q.GetLine());
    a.GoNextLink();
    q.GoNextLink();
    EXPECT_TRUE(a.GetLine() == q.GetLine());
    a.GoDownLink();
    q.GoDownLink();
    EXPECT_TRUE(a.GetLine() == q.GetLine());
}

TEST(TText, can_clear_data)
{
    TTextLink::InitMemSystem();
    string s("wal"), c("mg");
    PTTextLink p = new TTextLink("abc");
    TText a(p);
    a.InsNextLine(s);
    a.GoNextLink();
    a.InsDownSection(c);
    ASSERT_NO_THROW(TTextLink::MemCleaner(a));
}

TEST(TText, GoNext_correct_with_next_section)
{
    TTextLink::InitMemSystem();
    string s("wal"), c("mg");
    PTTextLink p = new TTextLink("abc");
    TText a(p);
    a.InsNextLine(s);
    a.InsDownSection(c);
    a.Reset();
    a.GoNext();
    ASSERT_TRUE(c == a.GetLine());
}

TEST(TText, GoNext_correct_with_down_section)
{
    TTextLink::InitMemSystem();
    string s("wal"), c("mg");
    PTTextLink p = new TTextLink("abc");
    TText a(p);
    a.InsDownSection(c);
    a.InsNextSection(s);
    a.Reset();
    a.GoNext();
    ASSERT_TRUE(c == a.GetLine());
}
