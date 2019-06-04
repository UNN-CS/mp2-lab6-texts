#include "gtest.h"

#include "ttextlink.h"
#include "ttext.h"

TEST(TTextLink, Can_Init_Memory)
{
    ASSERT_NO_THROW(TTextLink::InitMemSystem());
}

TEST(TTextLink, Can_Create_TTextLink)
{
    TTextLink::InitMemSystem();
    ASSERT_NO_THROW(TTextLink tl("TEST TEXT"));
}

TEST(TTextLink, Can_Get_Copy)
{
    TTextLink::InitMemSystem();
    TTextLink tl1("TEST TEXT");
    ASSERT_NO_THROW(PTTextLink tl2 = (PTTextLink)tl1.GetCopy());
}

TEST(TText, Can_Create_TText)
{
    TTextLink::InitMemSystem();
    TTextLink tl("TEST TEXT");
    ASSERT_NO_THROW(TText tt(&tl));
}

TEST(TText, Can_Get_Copy)
{
    TTextLink::InitMemSystem();
    TTextLink tl("TEST TEXT");
    TText tt1(&tl);
    ASSERT_NO_THROW(PTText tt2 = (PTText)tt1.GetCopy());
}

TEST(TText, Can_Set_Line)
{
    TTextLink::InitMemSystem();
    TText tt;
    ASSERT_NO_THROW(tt.SetLine("TEST TEXT"));
}

TEST(TText, Can_Get_Line)
{
    TTextLink::InitMemSystem();
    TTextLink tl("TEST TEXT");
    TText tt(&tl);
    ASSERT_NO_THROW(tt.GetLine());
}

TEST(TText, Gotten_Line_Is_Correct)
{
    TStr s = "TEST TEXT";
    TTextLink::InitMemSystem();
    TTextLink tl(s);
    TText tt(&tl);
    EXPECT_EQ(tt.GetLine(), s);
}

TEST(TText, Copy_Has_Its_Own_Memory)
{
    TTextLink::InitMemSystem();
    TTextLink tl("TEST TEXT");
    TText tt1(&tl);
    PTText tt2 = (PTText)tt1.GetCopy();
    EXPECT_EQ(tt1.GetLine(), tt2->GetLine());
    tt1.SetLine("TEXT TEST");
    EXPECT_NE(tt1.GetLine(), tt2->GetLine());
}

TEST(TText, InsDownLine_Is_Correct)
{
    TStr s = "TEST TEXT";
    TTextLink::InitMemSystem();
    TText tt;
    ASSERT_NO_THROW(tt.InsDownLine(s));
    ASSERT_NO_THROW(tt.GoDownLink());
    ASSERT_EQ(s, tt.GetLine());
}

TEST(TText, GoFirstLink_Is_Correct)
{
    TStr s1 = "TEST TEXT";
    TStr s2 = "TEXT TEST";
    TTextLink::InitMemSystem();
    TText tt;
    tt.SetLine(s1);
    tt.InsDownLine(s2);
    tt.GoDownLink();
    EXPECT_EQ(s2, tt.GetLine());
    tt.GoFirstLink();
    EXPECT_EQ(s1, tt.GetLine());
}

TEST(TText, InsDownSection_Is_Correct)
{
    TStr s = "TEST TEXT";
    TTextLink::InitMemSystem();
    TText tt;
    ASSERT_NO_THROW(tt.InsDownSection(s));
    ASSERT_NO_THROW(tt.GoDownLink());
    ASSERT_EQ(s, tt.GetLine());
}

TEST(TText, InsNextLine_Is_Correct)
{
    TStr s = "TEST TEXT";
    TTextLink::InitMemSystem();
    TText tt;
    ASSERT_NO_THROW(tt.InsNextLine(s));
    ASSERT_NO_THROW(tt.GoNextLink());
    ASSERT_EQ(s, tt.GetLine());
}

TEST(TText, InsNextSection_Is_Correct)
{
    TStr s = "TEST TEXT";
    TTextLink::InitMemSystem();
    TText tt;
    ASSERT_NO_THROW(tt.InsNextSection(s));
    ASSERT_NO_THROW(tt.GoNextLink());
    ASSERT_EQ(s, tt.GetLine());
}

TEST(TText, GoPrevLink_Is_Correct)
{
    TStr s1 = "TEST TEXT";
    TStr s2 = "TEXT TEST";
    TTextLink::InitMemSystem();
    TText tt;
    tt.SetLine(s1);
    tt.InsDownLine(s2);
    tt.GoDownLink();
    EXPECT_EQ(s2, tt.GetLine());
    tt.GoPrevLink();
    EXPECT_EQ(s1, tt.GetLine());
}

TEST(TText, DelDownLine_Is_Correct)
{
    TStr s1 = "TEST TEXT";
    TStr s2 = "TEXT TEST";
    TTextLink::InitMemSystem();
    TText tt;
    tt.SetLine(s1);
    tt.InsDownLine(s2);
    tt.DelDownLine();
    EXPECT_ANY_THROW(tt.GoDownLink());
}

TEST(TText, DelDownSection_Is_Correct)
{
    TStr s1 = "TEST TEXT";
    TStr s2 = "TEXT TEST";
    TTextLink::InitMemSystem();
    TText tt;
    tt.SetLine(s1);
    tt.InsDownLine(s2);
    tt.DelDownSection();
    EXPECT_ANY_THROW(tt.GoDownLink());
}

TEST(TText, DelNextLine_Is_Correct)
{
    TStr s1 = "TEST TEXT";
    TStr s2 = "TEXT TEST";
    TTextLink::InitMemSystem();
    TText tt;
    tt.SetLine(s1);
    tt.InsNextLine(s2);
    tt.DelNextLine();
    EXPECT_ANY_THROW(tt.GoNextLink());
}

TEST(TText, DelNextSection_Is_Correct)
{
    TStr s1 = "TEST TEXT";
    TStr s2 = "TEXT TEST";
    TTextLink::InitMemSystem();
    TText tt;
    tt.SetLine(s1);
    tt.InsNextLine(s2);
    tt.DelNextSection();
    EXPECT_ANY_THROW(tt.GoNextLink());
}

TEST(TText, Reset_And_GoNext_Are_Correct)
{
    TTextLink::InitMemSystem();
    TText tt;
    tt.SetLine("TEST TEXT");
    tt.InsNextLine("TEST");
    tt.InsDownLine("TEXT");
    ASSERT_NO_THROW(tt.Reset());
    ASSERT_NO_THROW(tt.GoNext());
    EXPECT_EQ("TEXT", tt.GetLine());
    ASSERT_NO_THROW(tt.GoNext());
    EXPECT_EQ("TEST", tt.GetLine());
    ASSERT_NO_THROW(tt.GoNext());
    EXPECT_EQ("TEST TEXT", tt.GetLine());
}
