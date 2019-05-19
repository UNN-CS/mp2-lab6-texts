#include <gtest.h>
#include <string>
#include <iostream>

#include "TText.h"

 using namespace std;


TEST(TText, Can_Create_Text_Without_Parameters) {
    TTextLink::InitMemSystem();

    ASSERT_NO_THROW(TText t);
}

TEST(TText, Can_Create_Text) {
    TTextLink::InitMemSystem(1);
	PTTextLink pt = new TTextLink;

    ASSERT_NO_THROW(TText t(pt));
}

TEST(TText, Can_Get_Copy) {
	TTextLink::InitMemSystem();
	TText t1;
	t1.InsNextLine("qwerty");

	ASSERT_NO_THROW(PTText t2 = t1.getCopy());
}

TEST(TText, Get_Copy_Is_Correct) {
	TTextLink::InitMemSystem();
	TText t1;
	t1.InsNextLine("qwerty");
	PTText t2 = t1.getCopy();

	EXPECT_EQ((*t2).GetLine(), t1.GetLine());
}

TEST(TText, Can_Set_Line) {
    TTextLink::InitMemSystem();
    TText t;

    ASSERT_NO_THROW(t.SetLine("qwerty"));
}

TEST(TText, Can_Get_Line) {
    TTextLink::InitMemSystem();
    TText t;
    t.SetLine("qwerty");

    ASSERT_NO_THROW(t.GetLine());
}

TEST(TText, GetLine_Is_Correct_When_Text_Empty) {
    TTextLink::InitMemSystem();
    TText t;

    EXPECT_EQ("", t.GetLine());
}

TEST(TText, GetLine_Is_Correct) {
    TTextLink::InitMemSystem();
    TText t;
    t.SetLine("qwerty");

    EXPECT_EQ("qwerty", t.GetLine());
}

TEST(TText, Can_Go_First_Link) {
    TTextLink::InitMemSystem();
    TText t;

	EXPECT_EQ(TextOK, t.GoFirstLink());
}

TEST(TText, Go_First_Link_And_Ins_Next_Link_Are_Correct) {
    TTextLink::InitMemSystem();
    TText t;
	t.InsNextLine("qwerty");
	t.GoNextLink();
	t.GoFirstLink();

	EXPECT_EQ("", t.GetLine());
}

TEST(TText, Can_Ins_Down_Line)
{
    TTextLink::InitMemSystem();
    TText t;

    EXPECT_EQ(TextOK, t.InsDownLine("qqq"));
}

TEST(TText, Can_Ins_Next_Line)
{
    TTextLink::InitMemSystem();
    TText t;

    EXPECT_EQ(TextOK, t.InsNextLine("qqq"));
}

TEST(TText, Can_Ins_Down_Section)
{
    TTextLink::InitMemSystem();
    TText t;

    EXPECT_EQ(TextOK, t.InsDownSection("qqq"));
}

TEST(TText, Can_Ins_Next_Section)
{
    TTextLink::InitMemSystem();
    TText t;

    EXPECT_EQ(TextOK, t.InsNextSection("qqq"));
}

TEST(TText, Cant_Go_Next_Link_When_Text_Empty) {
    TTextLink::InitMemSystem();
    TText t;

	EXPECT_EQ(TextError, t.GoNextLink());
}

TEST(TText, Can_Go_Next_Link) {
    TTextLink::InitMemSystem();
    TText t;
	t.InsNextLine("qwerty");

	EXPECT_EQ(TextOK, t.GoNextLink());
}

TEST(TText, Go_Next_Link_And_Ins_Next_Link_Are_Correct) {
    TTextLink::InitMemSystem();
    TText t;
	t.InsNextLine("qwerty");
	t.GoNextLink();

	EXPECT_EQ("qwerty", t.GetLine());
}

TEST(TText, Cant_Go_Down_Link_When_Text_Empty)
{
    TTextLink::InitMemSystem();
    TText t;

    EXPECT_EQ(TextError, t.GoDownLink());
}

TEST(TText, Can_Go_Down_Link)
{
    TTextLink::InitMemSystem();
    TText t;
	t.InsDownLine("qqq");

    EXPECT_EQ(TextOK, t.GoDownLink());
}

TEST(TText, Go_Down_Link_And_Ins_Down_Link_Are_Correct)
{
    TTextLink::InitMemSystem();
    TText t;
	t.InsDownLine("qwerty");
	t.GoDownLink();

    EXPECT_EQ("qwerty", t.GetLine());
}

TEST(TText, Cant_Go_Prev_Link_When_Text_Empty)
{
    TTextLink::InitMemSystem();
    TText t;

    EXPECT_EQ(TextNoPrev, t.GoPrevLink());
}

TEST(TText, Can_Go_Prev_Link)
{
    TTextLink::InitMemSystem();
    TText t;
	t.InsNextLine("qqq");
	t.GoNextLink();

    EXPECT_EQ(TextOK, t.GoPrevLink());
}

TEST(TText, Go_Prev_Link_And_Ins_Next_Link_Are_Correct)
{
    TTextLink::InitMemSystem();
    TText t;
	t.InsNextLine("qwerty");
	t.GoNextLink();
	t.InsNextLine("qqq");
	t.GoNextLink();
	t.GoPrevLink();

    EXPECT_EQ("qwerty", t.GetLine());
}

TEST(TText, Ins_Down_Section_Is_Correct)
{
    TTextLink::InitMemSystem();
    TText t;
	t.InsDownSection("qwerty");
	t.GoDownLink();

    EXPECT_EQ("qwerty", t.GetLine());
}

TEST(TText, Ins_Next_Section_Is_Correct)
{
    TTextLink::InitMemSystem();
    TText t;
	t.InsNextSection("qwerty");
	t.GoNextLink();

    EXPECT_EQ("qwerty", t.GetLine());
}

 TEST(TText, Can_Delete_Down_Line)
{
    TTextLink::InitMemSystem();
    TText t;
    t.InsDownLine("qwerty");

    ASSERT_NO_THROW(t.DelDownLine());
}

  TEST(TText, Delete_Down_Line_Is_Correct)
{
    TTextLink::InitMemSystem();
    TText t;
    t.InsDownLine("qwerty");
	t.DelDownLine();

    EXPECT_EQ(TextNoPrev, t.GoPrevLink());
}

 TEST(TText, Can_Delete_Down_Section)
{
    TTextLink::InitMemSystem();
    TText t;
    t.InsDownSection("qwerty");

    ASSERT_NO_THROW(t.DelDownSection());
}

 TEST(TText, Delete_Down_Section_Is_Correct)
{
    TTextLink::InitMemSystem();
    TText t;
    t.InsDownSection("qwerty");
	t.DelDownSection();

    EXPECT_EQ(TextNoPrev, t.GoPrevLink());
}

 TEST(TText, Can_Delete_Next_Line)
{
    TTextLink::InitMemSystem();
    TText t;
    t.InsNextLine("qwerty");

    ASSERT_NO_THROW(t.DelNextLine());
}

 TEST(TText, Delete_Next_Line_Is_Correct)
{
    TTextLink::InitMemSystem();
    TText t;
    t.InsNextLine("qwerty");
	t.DelNextLine();

	EXPECT_EQ(TextError, t.GoNextLink());
}

  TEST(TText, Can_Delete_Next_Section)
{
    TTextLink::InitMemSystem();
    TText t;
    t.InsNextSection("qwerty");

    ASSERT_NO_THROW(t.DelNextSection());
}

 TEST(TText, Delete_Next_Section_Is_Correct)
{
    TTextLink::InitMemSystem();
    TText t;
    t.InsNextSection("qwerty");
	t.DelNextSection();

	EXPECT_EQ(TextError, t.GoNextLink());
}

 TEST(TText, Reset_Is_Correct)
{
    TTextLink::InitMemSystem();
    TText t;
    t.SetLine("qwerty");
	t.InsNextLine("qqq");
    t.GoNextLink();
    t.Reset();

    EXPECT_EQ("qwerty", t.GetLine());
}

 TEST(TText, IsTextEnded_Is_Correct)
{
    TTextLink::InitMemSystem();
    TText t;
    t.SetLine("qwerty");
	t.InsNextLine("qqq");
	t.GoNextLink();
	t.InsNextLine("www");
    t.GoNextLink();

    EXPECT_EQ(1, t.IsTextEnded());
}

 TEST(TText, GoNext_Is_Correct_V1)
{
	TTextLink::InitMemSystem();
	PTTextLink tmp = new TTextLink("qwerty");
	TText t(tmp);
	t.InsNextLine("www");
	t.Reset();
	t.GoNext();

	EXPECT_EQ("www", t.GetLine());
}

 TEST(TText, GoNext_Is_Correct_V2)
{
	TTextLink::InitMemSystem();
	PTTextLink tmp = new TTextLink("qwerty");
	TText t(tmp);
	t.InsNextLine("www");
	t.Reset();
	t.GoNext();

	EXPECT_EQ(1, t.GoNext());
}



