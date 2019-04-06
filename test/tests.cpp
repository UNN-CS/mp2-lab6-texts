#include <gtest.h>
#include "TText.h"
#include <string>
#include <iostream>
#include "TTextLink.h"

using namespace std;

TEST(TText, can_insert_next_line) {
	TTextLink::InitMemSystem();
	TText txt;
	txt.InsNextLine("alex_di");
	EXPECT_EQ(txt.GoNextLink(),TextOK);
	EXPECT_EQ("alex_di", txt.GetLine());
}

TEST(TText, can_insert_down_line) {
	TTextLink::InitMemSystem();
	TText txt;
	txt.InsDownLine("alex_di");
	EXPECT_EQ(txt.GoDownLink(), TextOK);
	EXPECT_EQ("alex_di", txt.GetLine());
}

TEST(TText, can_insert_next_section) {
	TTextLink::InitMemSystem();
	TText txt;
	txt.InsNextSection("alex_di");
	EXPECT_EQ(txt.GoNextLink(), TextOK);
	EXPECT_EQ("alex_di", txt.GetLine());
}

TEST(TText, can_insert_down_section) {
	TTextLink::InitMemSystem();
	TText txt;
	txt.InsDownSection("alex_di");
	EXPECT_EQ(txt.GoDownLink(), TextOK);
	EXPECT_EQ("alex_di", txt.GetLine());
}

TEST(TTextLink, can_do_memclear)
{
	TTextLink::InitMemSystem(100);
	TText t;
	TTextLink::MemCleaner(t);
}

TEST(TTextLink, can_create_TTextLink)
{
	TTextLink::InitMemSystem(100);
	ASSERT_NO_THROW(TTextLink t("alex"););
}

TEST(TText, can_create_TText)
{
	TTextLink::InitMemSystem(23);
	ASSERT_NO_THROW(TText a);
}

TEST(TText, pfirst_equal_head_of_text)
{
	TTextLink::InitMemSystem(23);
	PTTextLink tmp = new TTextLink("alex");
	TText t(tmp);
	EXPECT_EQ(t.GetLine(), "alex");
}

TEST(TText, SetLine_is_correct)
{
	TTextLink::InitMemSystem();
	TText t;
	t.InsNextLine("alex");
	t.SetLine("_di");
	EXPECT_EQ("_di", t.GetLine());
}

TEST(TText, DelNextLine_is_correct)
{
	TTextLink::InitMemSystem();
	TText t;
	t.InsNextLine("alxe");
	t.InsNextLine("wef");
	EXPECT_EQ(t.DelNextLine(),TextOK);
	EXPECT_EQ(TextOK, t.GoNextLink());
}

TEST(TText, GoNextLink_without_lines)
{
	TTextLink::InitMemSystem();
	TText t;
	EXPECT_EQ(TextError, t.GoNextLink());
}

TEST(TText, DelDownLine_is_correct)
{
	TTextLink::InitMemSystem();
	TText t;
	t.InsDownLine("alex");
	t.InsDownLine("wef");
	EXPECT_EQ(t.DelDownLine(), TextOK);
	t.Print();
	t.GoDownLink();
	EXPECT_EQ("alex", t.GetLine());
}

TEST(TText, DelDownLine_is_correct_2)
{
	TTextLink::InitMemSystem();
	TText t;
	t.InsDownLine("aleddx");
	t.Print();
	EXPECT_EQ(t.DelDownLine(),TextOK);
	t.Print();
	EXPECT_EQ(t.GoDownLink(),TextError);
}

TEST(TText, DelNextSection_is_correct)
{
	TTextLink::InitMemSystem();
	TText t;
	t.InsNextSection("alex");
	ASSERT_EQ(t.DelNextSection(),TextOK);
	EXPECT_EQ(TextError, t.GoNextLink());
}

TEST(TText, DelDownSection_is_correct)
{
	TTextLink::InitMemSystem();
	TText t;
	t.InsDownSection("Math");
	ASSERT_EQ(t.DelDownSection(),TextOK);
	EXPECT_EQ(TextError, t.GoDownLink());
}

TEST(TText, First_Link_is_correct)
{
	TTextLink::InitMemSystem();
	TText t;
	t.InsNextLine("Math");
	t.GoNextLink();
	t.GoFirstLink();
	EXPECT_EQ("", t.GetLine());
}

TEST(TText, First_Link_is_correct_2)
{
	TTextLink::InitMemSystem();
	PTTextLink tmp = new TTextLink("Math");
	TText t(tmp);
	t.GoNextLink();
	t.GoFirstLink();
	EXPECT_EQ("Math", t.GetLine());
}

TEST(TText, GoNext_is_correct)
{
	TTextLink::InitMemSystem();
	PTTextLink tmp = new TTextLink("alex");
	TText t(tmp);
	t.InsNextLine("_di");
	t.Reset();
	t.GoNext();
	EXPECT_EQ("_di", t.GetLine());
	EXPECT_EQ(1, t.GoNext());
}

TEST(TText, can_getCopy)
{
	TTextLink::InitMemSystem();
	TText t1;
	t1.InsNextLine("alex_di1");
	ASSERT_NO_THROW(t1.getCopy());
}

TEST(TText, getCopy_is_correct)
{
	TTextLink::InitMemSystem();
	TText t1;
	TText t2;
	t1.InsNextLine("alex_di1");
	t1.InsNextSection("five");
	t2 = *t1.getCopy();
	t1.Print();
	t2.Print();
	t1.GoNextLink();
	t2.GoNextLink();
	EXPECT_EQ(t1.GetLine(), t2.GetLine());
}
