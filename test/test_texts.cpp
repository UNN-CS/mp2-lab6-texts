#include <gtest.h>
#include <iostream>
#include "ttext.h"
#include "ttextlink.h"

using namespace std;

TEST(TText, Can_Create_TText_Without_Args) {
	ASSERT_NO_THROW(TText text);
}

TEST(TText, Can_Create_TText) {
	TTextLink::InitMemSystem();
	TTextLink t("Test");
	ASSERT_NO_THROW(TText text(&t));
}

TEST(TText, Correct_Get_Line) {
	TTextLink::InitMemSystem();
	TTextLink l("Test");
	TText t(&l);
	EXPECT_EQ("Test", t.GetLine());
}

TEST(TText, Correct_Set_Line) {
	TTextLink::InitMemSystem();
	TTextLink l("Test 1");
	TText text(&l);
	text.SetLine("Test 2");
	EXPECT_EQ("Test 2", text.GetLine());
}

TEST(TText, Correct_Ins_Down_Line) {
	TTextLink::InitMemSystem();
	TText text;
	text.InsDownLine("Test");
	text.GoDownLink();
	EXPECT_EQ("Test", text.GetLine());
}

TEST(TText, Correct_Ins_Next_Line) {
	TTextLink::InitMemSystem();
	TText text;
	text.SetLine("Test 1");
	text.InsNextLine("Test 2");
	text.GoNextLink();
	EXPECT_EQ("Test 2", text.GetLine());
}

TEST(TText, Correct_Ins_Next_Section) {
	TTextLink::InitMemSystem();
	TText text;
	text.SetLine("Test 1");
	text.InsNextSection("Test 2");
	text.GoNextLink();
	EXPECT_EQ("Test 2", text.GetLine());
}

TEST(TText, Can_Del_Down_Line) {
	TTextLink::InitMemSystem();
	TText text;
	text.InsDownLine("Test");
	ASSERT_NO_THROW(text.DelDownLine());
}

TEST(TText, Can_Del_Next_Line) {
	TTextLink::InitMemSystem();
	TText text;
	text.InsNextLine("Test");
	ASSERT_NO_THROW(text.DelNextLine());
}

TEST(TText, Can_Del_Next_Section) {
	TTextLink::InitMemSystem();
	TText text;
	text.InsNextSection("Test");
	ASSERT_NO_THROW(text.DelNextSection());
}

TEST(TText, Correct_Go_Prev_Link) {
	TTextLink::InitMemSystem();
	TText text;
	text.SetLine("Test 1");
	text.InsDownLine("Test 2");
	text.GoDownLink();
	text.GoPrevLink();
	EXPECT_EQ("Test 1", text.GetLine());
}