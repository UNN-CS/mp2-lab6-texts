#include "gtest.h"
#include "../include/TText.h"
#include <locale>
#include <iostream>


TEST(TText, Can_see_an_error_in_the_absence_of_prev) {
	TTextLink::InitMemSystem(2);
	TText T;

	T.GoFirstLink();
	EXPECT_EQ(T.GoPrevLink(), Data::TextNoPrev);
}

TEST(TText, Can_create_and_add_text_test) {
	const string str = "Hello world!";
	TTextLink Link = TTextLink(str);
	PTTextLink pLink = &Link;
	TTextLink::InitMemSystem(20);
	TText T(pLink);
	T.GoFirstLink();

	EXPECT_EQ(T.GetLine(), str);
}

TEST(TText, Add_and_godown_test) {
	TTextLink::InitMemSystem(20);
	TText T;
	const string str = "Hello world!";
	T.GoFirstLink();
	T.InsDownLine(str);
	T.GoDownLink();

	EXPECT_EQ(T.GetLine(), str);
}

TEST(TText, Can_del_down_line_test) {
	const string str1 = "Hello world!";
	const string str2 = "Hello!";
	const string str3 = "World welcomes you";
	TTextLink::InitMemSystem(20);
	TText T;
	T.GoFirstLink();
	T.InsDownLine(str1);
	T.GoDownLink();
	T.InsDownLine(str2);
	T.InsDownLine(str3);
	T.GoDownLink();
	T.DelDownLine();
	T.GoFirstLink();
	T.GoDownLink();

	EXPECT_EQ(T.GetLine(), str1);
	T.GoDownLink();
	EXPECT_EQ(T.GetLine(), str3);
}

TEST(TText, Read_test) {
	string str1 = "Start File";
	string str2 = "Continuation File 1.1";
	string str3 = "Continuation File 1.1.1";
	PTTextLink TLink = new TTextLink();
	TTextLink::InitMemSystem(20);
	TText File(TLink);
	File.Read("C:\Users\lumpofsugar\Desktop\6\mp2-lab6-texts\files\input.txt");
	File.GoFirstLink();

	EXPECT_EQ(str1, File.GetLine());
	File.GoDownLink();
	EXPECT_EQ(str2, File.GetLine());
	File.GoDownLink();
	EXPECT_EQ(str3, File.GetLine());
}

TEST(TText, Can_Del_Next_Section_test) {
	const string sec1 = "section 1";
	const string sec2 = "section 2";
	const string str1 = "string 1";
	const string str2 = "string 2";
	const string str3 = "string 3";
	TTextLink::InitMemSystem(7);
	TText T;

	T.GoFirstLink();
	T.InsDownLine(sec1);
	T.GoDownLink();
	T.InsNextLine(str2);
	T.InsNextLine(str1);
	T.InsNextSection(sec2);
	T.InsNextLine(str3);

	T.Write("dewv.txt");
	T.GoNextLink();
	T.DelNextSection();

	T.GoFirstLink();
	T.GoDownLink();
	T.GoNextLink();
	EXPECT_EQ(T.GetLine(), str3);
}
TEST(TText, Can_bring_a_positive_error_code) {
	const string str = "Hello world!";
	TTextLink::InitMemSystem(2);
	TText T;
	T.GoFirstLink();
	T.InsDownLine(str);

	T.GoFirstLink();
	EXPECT_EQ(T.GoDownLink(), Data::TextOk);
}

TEST(TText, Can_see_an_error_in_the_absence_of_next) {
	TTextLink::InitMemSystem(2);
	TText T;

	T.GoFirstLink();
	EXPECT_EQ(T.GoNextLink(), Data::TextNoNext);
}
