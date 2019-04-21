#include "TText.h"
#include "gtest.h"

TEST(TText, can_create_text_v1)
{
	ASSERT_NO_THROW(TText t);
}

TEST(TText, can_create_text_v2)
{
	TTextLink::InitMemSystem(1);
	TStr s = "test";
	PTTextLink l = new TTextLink(s);
	
	ASSERT_NO_THROW(TText t(l));
}

TEST(TText, go_first_link_v1)
{
	TText t;
	
	EXPECT_EQ(DataErr, t.GoFirstLink());
}

TEST(TText, go_first_link_v2)
{
	TTextLink::InitMemSystem(2);
	PTTextLink tl = new TTextLink();
	TText t(tl);

	EXPECT_EQ(DataOK, t.GoFirstLink());
}

TEST(TText, go_down_link_v1)
{
	TText t;

	EXPECT_EQ(DataErr, t.GoDownLink());
}

TEST(TText, go_down_link_v2)
{
	TTextLink::InitMemSystem(2);
	PTTextLink tl = new TTextLink;
	TText t(tl);

	EXPECT_EQ(DataErr, t.GoDownLink());
}

TEST(TText, go_down_link_v3)
{
	TTextLink::InitMemSystem(2);
	PTTextLink tl1 = new TTextLink;
	PTTextLink tl2 = new TTextLink(NULL,NULL,tl1);
	TText t(tl2);

	EXPECT_EQ(DataOK, t.GoDownLink());
}

TEST(TText, go_next_link_v1)
{
	TText t;

	EXPECT_EQ(DataErr, t.GoNextLink());
}

TEST(TText, go_next_link_v2)
{
	TTextLink::InitMemSystem(2);
	PTTextLink tl = new TTextLink;
	TText t(tl);

	EXPECT_EQ(DataErr, t.GoNextLink());
}

TEST(TText, go_next_link_v3)
{
	TTextLink::InitMemSystem(2);
	PTTextLink tl1 = new TTextLink;
	PTTextLink tl2 = new TTextLink(NULL, tl1);
	TText t(tl2);

	EXPECT_EQ(DataOK, t.GoNextLink());
}

TEST(TText, go_prev_link_v1)
{
	TText t;

	EXPECT_EQ(DataErr, t.GoPrevLink());
}

TEST(TText, go_prev_link_v2)
{
	TTextLink::InitMemSystem(2);
	PTTextLink tl = new TTextLink;
	TText t(tl);

	EXPECT_EQ(DataErr, t.GoPrevLink());
}

TEST(TText, go_prev_link_v3)
{
	TTextLink::InitMemSystem(4);
	PTTextLink tl1 = new TTextLink;
	PTTextLink tl2 = new TTextLink;
	PTTextLink tl3 = new TTextLink(NULL, tl1, tl2);
	TText t(tl3);
	t.GoDownLink();

	EXPECT_EQ(DataOK, t.GoPrevLink());
}

TEST(TText, go_prev_link_v4)
{
	TTextLink::InitMemSystem(3);
	PTTextLink tl1 = new TTextLink;
	PTTextLink tl2 = new TTextLink;
	PTTextLink tl3 = new TTextLink(NULL, tl1, tl2);
	TText t(tl3);
	t.GoNextLink();

	EXPECT_EQ(DataOK, t.GoPrevLink());
}

TEST(TText, get_line_v1_0)
{
	TText t;
	t.GetLine();

	EXPECT_EQ(DataErr, t.GetRetCode());
}

TEST(TText, get_line_v1_1)
{
	TText t;

	EXPECT_EQ("", t.GetLine());
}

TEST(TText, get_line_v2)
{
	TTextLink::InitMemSystem(2);
	TStr s = "test";
	PTTextLink tl = new TTextLink(s);
	TText t(tl);

	EXPECT_EQ(DataOK, t.GetRetCode());
}

TEST(TText, get_line_v3)
{
	TTextLink::InitMemSystem(2);
	TStr s = "test";
	PTTextLink tl = new TTextLink(s);
	TText t(tl);

	EXPECT_EQ(s, t.GetLine());
}

TEST(TText, set_line_v1)
{
	TText t;
	char* s = "test";
	t.SetLine(s);

	EXPECT_EQ(DataErr, t.GetRetCode());
}

TEST(TText, set_line_v2)
{
	TTextLink::InitMemSystem(3);
	char* s = "test";
	PTTextLink ptl = new TTextLink;
	TText t(ptl);
	t.SetLine(s);

	EXPECT_EQ(t.GetLine(), s);
}

TEST(TText, ins_down_line_v1)
{
	TText t;
	t.InsDownLine("test");

	EXPECT_EQ(DataErr, t.GetRetCode());
}

TEST(TText, ins_down_line_v2_1)
{
	TTextLink::InitMemSystem(3);
	PTTextLink tl1 = new TTextLink;
	TText t(tl1);
	t.InsDownLine("test");

	EXPECT_EQ(DataOK, t.GetRetCode());
}

TEST(TText, ins_down_line_v2_2)
{
	char* s = "test";
	TTextLink::InitMemSystem(3);
	PTTextLink tl1 = new TTextLink;
	TText t(tl1);
	t.InsDownLine(s);

	EXPECT_EQ(s, t.GetLine());
}

TEST(TText, ins_down_line_v2_3)
{
	char* s = "test";
	TTextLink::InitMemSystem(3);
	PTTextLink tl1 = new TTextLink;
	TText t(tl1);
	t.InsDownLine(s);

	EXPECT_EQ(DataErr, t.GoDownLink());
}

TEST(TText, ins_down_line_v2_4)
{
	char* s = "test";
	TTextLink::InitMemSystem(3);
	PTTextLink tl1 = new TTextLink;
	TText t(tl1);
	t.InsDownLine(s);

	EXPECT_EQ(DataErr, t.GoNextLink());
}

TEST(TText, ins_down_line_v3_1)
{
	char* s = "test";
	TTextLink::InitMemSystem(3);
	PTTextLink tl1 = new TTextLink(s);
	PTTextLink tl2 = new TTextLink(NULL, NULL, tl1);
	TText t(tl2);
	t.InsDownLine(" ");

	EXPECT_EQ(" ", t.GetLine());
}

TEST(TText, ins_down_line_v3_2)
{
	char* s = "test";
	TTextLink::InitMemSystem(3);
	PTTextLink tl1 = new TTextLink(s);
	PTTextLink tl2 = new TTextLink(NULL, NULL, tl1);
	TText t(tl2);
	t.InsDownLine(" ");
	t.GoNextLink();

	EXPECT_EQ(s, t.GetLine());
}

TEST(TText, ins_down_line_v3_3)
{
	char* s = "test";
	TTextLink::InitMemSystem(3);
	PTTextLink tl1 = new TTextLink(s);
	PTTextLink tl2 = new TTextLink("first", NULL, tl1);
	TText t(tl2);
	t.InsDownLine(" ");
	t.GoPrevLink();

	EXPECT_EQ("first", t.GetLine());
}

TEST(TText, ins_down_line_v4_1)
{
	char* s = "test";
	TTextLink::InitMemSystem(3);
	PTTextLink tl1 = new TTextLink(s);
	PTTextLink tl2 = new TTextLink(NULL,tl1);
	TText t(tl2);
	t.InsDownLine(" ");

	EXPECT_EQ(" ", t.GetLine());
}

TEST(TText, ins_down_line_4_2)
{
	char* s = "test";
	TTextLink::InitMemSystem(3);
	PTTextLink tl1 = new TTextLink(s);
	PTTextLink tl2 = new TTextLink(NULL,tl1);
	TText t(tl2);
	t.InsDownLine(" ");
	
	EXPECT_EQ(DataErr, t.GoNextLink());
}

TEST(TText, ins_down_line_v4_3)
{
	char* s = "test";
	TTextLink::InitMemSystem(3);
	PTTextLink tl1 = new TTextLink(s);
	PTTextLink tl2 = new TTextLink("first", NULL, tl1);
	TText t(tl2);
	t.InsDownLine(" ");
	t.GoPrevLink();

	EXPECT_EQ("first", t.GetLine());
}

TEST(TText, ins_down_section_v1)
{
	TText t;
	t.InsDownSection("test");

	EXPECT_EQ(DataErr, t.GetRetCode());
}

TEST(TText, ins_down_section_v2_1)
{
	TTextLink::InitMemSystem(3);
	PTTextLink tl1 = new TTextLink;
	TText t(tl1);
	t.InsDownSection("test");

	EXPECT_EQ(DataOK, t.GetRetCode());
}

TEST(TText, ins_down_section_v2_2)
{
	char* s = "test";
	TTextLink::InitMemSystem(3);
	PTTextLink tl1 = new TTextLink;
	TText t(tl1);
	t.InsDownSection(s);

	EXPECT_EQ(s, t.GetLine());
}

TEST(TText, ins_down_section_v2_3)
{
	char* s = "test";
	TTextLink::InitMemSystem(3);
	PTTextLink tl1 = new TTextLink;
	TText t(tl1);
	t.InsDownSection(s);

	EXPECT_EQ(DataErr, t.GoDownLink());
}

TEST(TText, ins_down_section_v2_4)
{
	char* s = "test";
	TTextLink::InitMemSystem(3);
	PTTextLink tl1 = new TTextLink;
	TText t(tl1);
	t.InsDownSection(s);

	EXPECT_EQ(DataErr, t.GoNextLink());
}

TEST(TText, ins_down_section_v3_1)
{
	char* s = "test";
	TTextLink::InitMemSystem(3);
	PTTextLink tl1 = new TTextLink(s);
	PTTextLink tl2 = new TTextLink(NULL, NULL, tl1);
	TText t(tl2);
	t.InsDownSection(" ");

	EXPECT_EQ(DataOK, t.GetRetCode());
}

TEST(TText, ins_down_section_v3_2)
{
	char* s = "test";
	TTextLink::InitMemSystem(3);
	PTTextLink tl1 = new TTextLink(s);
	PTTextLink tl2 = new TTextLink(NULL, NULL, tl1);
	TText t(tl2);
	t.InsDownSection(" ");

	EXPECT_EQ(" ", t.GetLine());
}

TEST(TText, ins_down_section_v3_3)
{
	char* s = "test";
	TTextLink::InitMemSystem(3);
	PTTextLink tl1 = new TTextLink(s);
	PTTextLink tl2 = new TTextLink(NULL, NULL, tl1);
	TText t(tl2);
	t.InsDownSection(" ");
	t.GoDownLink();

	EXPECT_EQ(s, t.GetLine());
}

TEST(TText, ins_down_section_v3_4)
{
	char* s = "test";
	TTextLink::InitMemSystem(3);
	PTTextLink tl1 = new TTextLink(s);
	PTTextLink tl2 = new TTextLink("first", NULL, tl1);
	TText t(tl2);
	t.InsDownSection(" ");
	t.GoPrevLink();

	EXPECT_EQ("first", t.GetLine());
}

TEST(TText, ins_down_section_v4_1)
{
	char* s = "test";
	TTextLink::InitMemSystem(3);
	PTTextLink tl1 = new TTextLink(s);
	PTTextLink tl2 = new TTextLink(NULL,tl1);
	TText t(tl2);
	t.InsDownSection(" ");

	EXPECT_EQ(DataOK, t.GetRetCode());
}

TEST(TText, ins_down_section_v4_2)
{
	char* s = "test";
	TTextLink::InitMemSystem(3);
	PTTextLink tl1 = new TTextLink(s);
	PTTextLink tl2 = new TTextLink(NULL,tl1);
	TText t(tl2);
	t.InsDownSection(" ");

	EXPECT_EQ(" ", t.GetLine());
}

TEST(TText, ins_down_section_v4_3)
{
	char* s = "test";
	TTextLink::InitMemSystem(3);
	PTTextLink tl1 = new TTextLink(s);
	PTTextLink tl2 = new TTextLink("first", tl1);
	TText t(tl2);
	t.InsDownSection(" ");
	t.GoPrevLink();

	EXPECT_EQ("first", t.GetLine());
}

TEST(TText, ins_next_line_v1)
{
	TText t;
	t.InsNextLine("");

	EXPECT_EQ(DataErr, t.GetRetCode());
}

TEST(TText, ins_next_line_v2_1)
{
	TTextLink::InitMemSystem(2);
	PTTextLink pl1 = new TTextLink("1");
	TText t(pl1);
	t.InsNextLine("2");

	EXPECT_EQ(DataOK, t.GetRetCode());
}

TEST(TText, ins_next_line_v2_2)
{
	TTextLink::InitMemSystem(2);
	PTTextLink pl1 = new TTextLink("1");
	TText t(pl1);
	t.InsNextLine("2");

	EXPECT_EQ("2", t.GetLine());
}

TEST(TText, ins_next_line_v2_3)
{
	TTextLink::InitMemSystem(2);
	PTTextLink pl1 = new TTextLink("1");
	TText t(pl1);
	t.InsNextLine("2");

	EXPECT_EQ(DataErr, t.GoNextLink());
}

TEST(TText, ins_next_line_v2_4)
{
	TTextLink::InitMemSystem(2);
	PTTextLink pl1 = new TTextLink("1");
	TText t(pl1);
	t.InsNextLine("2");

	EXPECT_EQ(DataErr, t.GoDownLink());
}

TEST(TText, ins_next_line_v3_1)
{
	TTextLink::InitMemSystem(3);
	PTTextLink pl1 = new TTextLink("1");
	PTTextLink pl2 = new TTextLink("2", NULL, pl1);
	TText t(pl2);
	t.InsNextLine("3");

	EXPECT_EQ(DataOK, t.GetRetCode());
}

TEST(TText, ins_next_line_v3_2)
{
	TTextLink::InitMemSystem(3);
	PTTextLink pl1 = new TTextLink("1");
	PTTextLink pl2 = new TTextLink("2", NULL, pl1);
	TText t(pl2);
	t.InsNextLine("3");

	EXPECT_EQ("3", t.GetLine());
}

TEST(TText, ins_next_line_v3_3)
{
	TTextLink::InitMemSystem(3);
	PTTextLink pl1 = new TTextLink("1");
	PTTextLink pl2 = new TTextLink("2", NULL, pl1);
	TText t(pl2);
	t.InsNextLine("3");
	t.GoPrevLink();

	EXPECT_EQ("2", t.GetLine());
}

TEST(TText, ins_next_line_v4_1)
{
	TTextLink::InitMemSystem(3);
	PTTextLink pl1 = new TTextLink("1");
	PTTextLink pl2 = new TTextLink("2",pl1);
	TText t(pl2);
	t.InsNextLine("3");

	EXPECT_EQ(DataOK, t.GetRetCode());
}

TEST(TText, ins_next_line_v4_2)
{
	TTextLink::InitMemSystem(3);
	PTTextLink pl1 = new TTextLink("1");
	PTTextLink pl2 = new TTextLink("2",pl1);
	TText t(pl2);
	t.InsNextLine("3");

	EXPECT_EQ("3", t.GetLine());
}

TEST(TText, ins_next_line_v4_3)
{
	TTextLink::InitMemSystem(3);
	PTTextLink pl1 = new TTextLink("1");
	PTTextLink pl2 = new TTextLink("2",pl1);
	TText t(pl2);
	t.InsNextLine("3");
	t.GoPrevLink();

	EXPECT_EQ("2", t.GetLine());
}

TEST(TText, ins_next_line_v4_4)
{
	TTextLink::InitMemSystem(3);
	PTTextLink pl1 = new TTextLink("1");
	PTTextLink pl2 = new TTextLink("2", pl1);
	TText t(pl2);
	t.InsNextLine("3");
	t.GoNextLink();

	EXPECT_EQ("1", t.GetLine());
}

TEST(TText, ins_next_section_v1)
{
	TText t;
	t.InsNextSection("");

	EXPECT_EQ(DataErr, t.GetRetCode());
}

TEST(TText, ins_next_section_v2_1)
{
	TTextLink::InitMemSystem(3);
	PTTextLink pl1 = new TTextLink("1");
	TText t(pl1);
	t.InsNextSection("2");

	EXPECT_EQ(DataOK, t.GetRetCode());
}

TEST(TText, ins_next_section_v2_2)
{
	TTextLink::InitMemSystem(3);
	PTTextLink pl1 = new TTextLink("1");
	TText t(pl1);
	t.InsNextSection("2");

	EXPECT_EQ("2", t.GetLine());
}

TEST(TText, ins_next_section_v2_3)
{
	TTextLink::InitMemSystem(3);
	PTTextLink pl1 = new TTextLink("1");
	TText t(pl1);
	t.InsNextSection("2");

	EXPECT_EQ(DataErr, t.GoNextLink());
}

TEST(TText, ins_next_section_v2_4)
{
	TTextLink::InitMemSystem(3);
	PTTextLink pl1 = new TTextLink("1");
	TText t(pl1);
	t.InsNextSection("2");

	EXPECT_EQ(DataErr, t.GoDownLink());
}

TEST(TText, ins_next_section_v2_5)
{
	TTextLink::InitMemSystem(3);
	PTTextLink pl1 = new TTextLink("1");
	TText t(pl1);
	t.InsNextSection("2");
	t.GoPrevLink();

	EXPECT_EQ("1", t.GetLine());
}

TEST(TText, ins_next_section_v3_1)
{
	TTextLink::InitMemSystem(3);
	PTTextLink pl1 = new TTextLink("1");
	PTTextLink pl2 = new TTextLink("2",NULL,pl1);
	TText t(pl2);
	t.InsNextSection("3");

	EXPECT_EQ(DataOK, t.GetRetCode());
}

TEST(TText, ins_next_section_v3_2)
{
	TTextLink::InitMemSystem(3);
	PTTextLink pl1 = new TTextLink("1");
	PTTextLink pl2 = new TTextLink("2", NULL, pl1);
	TText t(pl2);
	t.InsNextSection("3");

	EXPECT_EQ("3", t.GetLine());
}

TEST(TText, ins_next_section_v4_1)
{
	TTextLink::InitMemSystem(3);
	PTTextLink pl1 = new TTextLink("1");
	PTTextLink pl2 = new TTextLink("2",pl1);
	TText t(pl2);
	t.InsNextSection("3");

	EXPECT_EQ(DataOK, t.GetRetCode());
}

TEST(TText, ins_next_section_v4_2)
{
	TTextLink::InitMemSystem(3);
	PTTextLink pl1 = new TTextLink("1");
	PTTextLink pl2 = new TTextLink("2",pl1);
	TText t(pl2);
	t.InsNextSection("3");

	EXPECT_EQ("3", t.GetLine());
}

TEST(TText, ins_next_section_v4_3)
{
	TTextLink::InitMemSystem(3);
	PTTextLink pl1 = new TTextLink("1");
	PTTextLink pl2 = new TTextLink("2",pl1);
	TText t(pl2);
	t.InsNextSection("3");
	t.GoDownLink();

	EXPECT_EQ("1", t.GetLine());
}

TEST(TText, del_down_line_v1)
{
	TText t;
	t.DelDownLine();

	EXPECT_EQ(DataErr, t.GetRetCode());
}

TEST(TText, del_down_line_v2_1)
{
	TTextLink::InitMemSystem(2);
	PTTextLink pl1 = new TTextLink("1");
	TText t(pl1);
	t.DelDownLine();

	EXPECT_EQ(DataErr, t.GetRetCode());
}

TEST(TText, del_down_line_v2_2)
{
	TTextLink::InitMemSystem(2);
	PTTextLink pl1 = new TTextLink("1");
	PTTextLink pl2 = new TTextLink("2",NULL,pl1);
	TText t(pl2);
	t.DelDownLine();

	EXPECT_EQ(DataOK, t.GetRetCode());
}

TEST(TText, del_down_line_v2_3)
{
	TTextLink::InitMemSystem(2);
	PTTextLink pl1 = new TTextLink("1");
	PTTextLink pl2 = new TTextLink("2", NULL, pl1);
	TText t(pl2);
	t.DelDownLine();
	t.GoDownLink();

	EXPECT_EQ(DataErr, t.GetRetCode());
}

TEST(TText, del_down_line_v2_4)
{
	TTextLink::InitMemSystem(3);
	PTTextLink pl1 = new TTextLink("1");
	PTTextLink pl2 = new TTextLink("2", pl1);
	PTTextLink pl3 = new TTextLink("3",NULL,pl2);
	TText t(pl3);
	t.DelDownLine();
	t.GoDownLink();

	EXPECT_EQ(DataOK, t.GetRetCode());
}

TEST(TText, del_down_line_v2_5)
{
	TTextLink::InitMemSystem(3);
	PTTextLink pl1 = new TTextLink("1");
	PTTextLink pl2 = new TTextLink("2", pl1);
	PTTextLink pl3 = new TTextLink("3", NULL, pl2);
	TText t(pl3);
	t.DelDownLine();
	t.GoDownLink();

	EXPECT_EQ("1", t.GetLine());
}

TEST(TText, del_down_line_v2_6)
{
	TTextLink::InitMemSystem(3);
	PTTextLink pl1 = new TTextLink("1");
	PTTextLink pl2 = new TTextLink("2",NULL,pl1);
	PTTextLink pl3 = new TTextLink("3", NULL, pl2);
	TText t(pl3);
	t.DelDownLine();

	EXPECT_EQ(DataErr, t.GetRetCode());
}

TEST(TText, del_down_section_v1)
{
	TText t;
	t.DelDownSection();

	EXPECT_EQ(DataErr, t.GetRetCode());
}

TEST(TText, del_down_section_v2_1)
{
	TTextLink::InitMemSystem(2);
	PTTextLink pl1 = new TTextLink("1");
	TText t(pl1);
	t.DelDownSection();

	EXPECT_EQ(DataErr, t.GetRetCode());
}

TEST(TText, del_down_section_v2_2)
{
	TTextLink::InitMemSystem(3);
	PTTextLink pl1 = new TTextLink("1");
	PTTextLink pl2 = new TTextLink("2", NULL, pl1);
	TText t(pl2);
	t.DelDownSection();

	EXPECT_EQ(DataOK, t.GetRetCode());
}

TEST(TText, del_down_section_v2_3)
{
	TTextLink::InitMemSystem(3);
	PTTextLink pl1 = new TTextLink("1");
	PTTextLink pl2 = new TTextLink("2", NULL, pl1);
	TText t(pl2);
	t.DelDownSection();
	t.GoDownLink();

	EXPECT_EQ(DataErr, t.GetRetCode());
}

TEST(TText, del_down_section_v2_4)
{
	TTextLink::InitMemSystem(3);
	PTTextLink pl1 = new TTextLink("1");
	PTTextLink pl2 = new TTextLink("2",pl1);
	PTTextLink pl3 = new TTextLink("3", NULL, pl2);
	TText t(pl3);
	t.DelDownSection();

	EXPECT_EQ(DataOK, t.GetRetCode());
}

TEST(TText, del_down_section_v2_5)
{
	TTextLink::InitMemSystem(3);
	PTTextLink pl1 = new TTextLink("1");
	PTTextLink pl2 = new TTextLink("2", pl1);
	PTTextLink pl3 = new TTextLink("3", NULL, pl2);
	TText t(pl3);
	t.DelDownSection();
	t.GoDownLink();

	EXPECT_EQ(DataOK, t.GetRetCode());
}

TEST(TText, del_down_section_v2_6)
{
	TTextLink::InitMemSystem(3);
	PTTextLink pl1 = new TTextLink("1");
	PTTextLink pl2 = new TTextLink("2", pl1);
	PTTextLink pl3 = new TTextLink("3", NULL, pl2);
	TText t(pl3);
	t.DelDownSection();
	t.GoDownLink();

	EXPECT_EQ("1", t.GetLine());
}

TEST(TText, del_next_line_v1)
{
	TText t;
	t.DelNextLine();

	EXPECT_EQ(DataErr, t.GetRetCode());
}

TEST(TText, del_next_line_v2_1)
{
	TTextLink::InitMemSystem(2);
	PTTextLink pl1 = new TTextLink("1");
	TText t(pl1);
	t.DelNextLine();

	EXPECT_EQ(DataErr, t.GetRetCode());
}

TEST(TText, del_next_line_v2_2)
{
	TTextLink::InitMemSystem(2);
	PTTextLink pl1 = new TTextLink("1");
	PTTextLink pl2 = new TTextLink("2",pl1);
	TText t(pl2);
	t.DelNextLine();

	EXPECT_EQ(DataOK, t.GetRetCode());
}

TEST(TText, del_next_line_v2_3)
{
	TTextLink::InitMemSystem(2);
	PTTextLink pl1 = new TTextLink("1");
	PTTextLink pl2 = new TTextLink("2", pl1);
	TText t(pl2);
	t.DelNextLine();
	t.GoDownLink();

	EXPECT_EQ(DataErr, t.GetRetCode());
}

TEST(TText, del_next_line_v2_4)
{
	TTextLink::InitMemSystem(2);
	PTTextLink pl1 = new TTextLink("1");
	PTTextLink pl2 = new TTextLink("2", pl1);
	TText t(pl2);
	t.DelNextLine();
	t.GoNextLink();

	EXPECT_EQ(DataErr, t.GetRetCode());
}

TEST(TText, del_next_line_v2_5)
{
	TTextLink::InitMemSystem(3);
	PTTextLink pl1 = new TTextLink("1");
	PTTextLink pl2 = new TTextLink("2", pl1);
	PTTextLink pl3 = new TTextLink("3", pl2);
	TText t(pl3);
	t.DelNextLine();

	EXPECT_EQ(DataOK, t.GetRetCode());
}

TEST(TText, del_next_line_v2_6)
{
	TTextLink::InitMemSystem(3);
	PTTextLink pl1 = new TTextLink("1");
	PTTextLink pl2 = new TTextLink("2", pl1);
	PTTextLink pl3 = new TTextLink("3", pl2);
	TText t(pl3);
	t.DelNextLine();
	t.GoNextLink();

	EXPECT_EQ("1", t.GetLine());
}

TEST(TText, del_next_line_v2_7)
{
	TTextLink::InitMemSystem(3);
	PTTextLink pl1 = new TTextLink("1");
	PTTextLink pl2 = new TTextLink("2",NULL,pl1);
	PTTextLink pl3 = new TTextLink("3",pl2);
	TText t(pl3);
	t.DelNextLine();

	EXPECT_EQ(DataErr, t.GetRetCode());
}

TEST(TText, del_next_section_v1)
{
	TText t;
	t.DelNextSection();

	EXPECT_EQ(DataErr, t.GetRetCode());
}

TEST(TText, del_next_section_v2_1)
{
	TTextLink::InitMemSystem(2);
	PTTextLink pl1 = new TTextLink("1");
	TText t(pl1);
	t.DelNextSection();

	EXPECT_EQ(DataErr, t.GetRetCode());
}

TEST(TText, del_next_section_v2_2)
{
	TTextLink::InitMemSystem(2);
	PTTextLink pl1 = new TTextLink("1");
	PTTextLink pl2 = new TTextLink("2",pl1);
	TText t(pl2);
	t.DelNextLine();

	EXPECT_EQ(DataOK, t.GetRetCode());
}

TEST(TText, del_next_section_v2_3)
{
	TTextLink::InitMemSystem(2);
	PTTextLink pl1 = new TTextLink("1");
	PTTextLink pl2 = new TTextLink("2",pl1);
	TText t(pl2);
	t.DelNextLine();
	t.GoNextLink();

	EXPECT_EQ(DataErr, t.GetRetCode());
}

TEST(TText, del_next_section_v2_4)
{
	TTextLink::InitMemSystem(2);
	PTTextLink pl1 = new TTextLink("1");
	PTTextLink pl2 = new TTextLink("2",pl1);
	TText t(pl2);
	t.DelNextLine();
	t.GoDownLink();

	EXPECT_EQ(DataErr, t.GetRetCode());
}

TEST(TText, del_next_section_v2_5)
{
	TTextLink::InitMemSystem(4);
	PTTextLink pl1 = new TTextLink("1");
	PTTextLink pl2 = new TTextLink("2");
	PTTextLink pl3 = new TTextLink("3", pl1,pl2);
	PTTextLink pl4 = new TTextLink("4", pl3);
	TText t(pl4);
	t.DelNextSection();

	EXPECT_EQ(DataOK, t.GetRetCode());
}

TEST(TText, del_next_section_v2_6)
{
	TTextLink::InitMemSystem(4);
	PTTextLink pl1 = new TTextLink("1");
	PTTextLink pl2 = new TTextLink("2");
	PTTextLink pl3 = new TTextLink("3", pl1, pl2);
	PTTextLink pl4 = new TTextLink("4", pl3);
	TText t(pl4);
	t.DelNextSection();
	t.GoNextLink();

	EXPECT_EQ("1", t.GetLine());
}

TEST(TText, del_next_section_v2_7)
{
	TTextLink::InitMemSystem(4);
	PTTextLink pl1 = new TTextLink("1");
	PTTextLink pl2 = new TTextLink("2",pl1);
	PTTextLink pl3 = new TTextLink("3", pl2);
	TText t(pl3);
	t.DelNextSection();

	EXPECT_EQ(DataErr, t.GetRetCode());
}

TEST(TText, reset_v1)
{
	TTextLink::InitMemSystem(3);
	PTTextLink pl1 = new TTextLink("1");
	TText t(pl1);
	t.InsDownSection("2");
	t.InsNextLine("3");
	t.Reset();

	EXPECT_EQ(DataOK, t.GetRetCode());
}

TEST(TText, reset_v2)
{
	TTextLink::InitMemSystem(3);
	PTTextLink pl1 = new TTextLink("1");
	TText t(pl1);
	t.InsDownSection("2");
	t.InsNextLine("3");
	t.Reset();

	EXPECT_EQ("1", t.GetLine());
}

TEST(TText, go_next_v1)
{
	TTextLink::InitMemSystem(3);
	PTTextLink pl1 = new TTextLink("1");
	TText t(pl1);
	t.InsNextLine("2");
	t.GoPrevLink();
	t.InsDownLine("3");
	t.Reset();
	t.GoNext();

	EXPECT_EQ("3", t.GetLine());
}

TEST(TText, go_next_v2)
{
	TTextLink::InitMemSystem(3);
	PTTextLink pl1 = new TTextLink("1");
	TText t(pl1);
	t.InsNextLine("2");
	t.InsDownLine("3");
	t.Reset();
	t.GoNext();

	EXPECT_EQ("2", t.GetLine());
}

TEST(TText, go_next_v3)
{
	TTextLink::InitMemSystem(4);
	PTTextLink pl1 = new TTextLink("1");
	TText t(pl1);
	t.InsNextLine("2");
	t.InsDownLine("3");
	t.GoPrevLink();
	t.InsNextLine("4");
	t.Reset();
	t.GoNext(); t.GoNext(); t.GoNext();

	EXPECT_EQ("4", t.GetLine());
}

TEST(TText, go_next_v4)
{
	TTextLink::InitMemSystem(4);
	PTTextLink pl1 = new TTextLink("1");
	TText t(pl1);
	t.InsNextLine("2");
	t.InsDownLine("3");
	t.GoPrevLink();
	t.InsNextLine("4");
	t.Reset();
	t.GoNext(); t.GoNext(); t.GoNext();
	t.GoNext();

	EXPECT_EQ(DataErr, t.GetRetCode());
}

TEST(TText, is_text_ended_v1)
{
	TTextLink::InitMemSystem(2);
	PTTextLink pl1 = new TTextLink("1");
	TText t(pl1);
	t.InsNextLine("2");
	t.Reset();

	EXPECT_EQ(false, t.IsTextEnded());
}

TEST(TText, is_text_ended_v2)
{
	TTextLink::InitMemSystem(2);
	PTTextLink pl1 = new TTextLink("1");
	TText t(pl1);
	t.InsNextLine("2");
	t.GoNext();

	EXPECT_EQ(true, t.IsTextEnded());
}

TEST(TText, mem_cleaner_v1)
{
	TTextLink::InitMemSystem(7);
	PTTextLink pl1 = new TTextLink("1");
	TText t(pl1);
	t.InsDownLine("\t2");
	t.InsDownLine("\t\t3");
	t.InsNextLine("\t\t4");
	t.InsNextLine("\t\t5");
	t.GoPrevLink(); t.GoPrevLink(); t.GoPrevLink();
	t.InsNextLine("\t6");
	t.Reset();
	t.InsNextLine("7");
	t.Reset();
	t.DelDownSection();
	TTextLink::MemCleaner(t);
	t.Reset();
	
	ASSERT_NO_THROW(t.InsNextLine("8"));
}

TEST(TText, mem_cleaner_v2)
{
	TTextLink::InitMemSystem(7);
	PTTextLink pl1 = new TTextLink("1");
	TText t(pl1);
	t.InsDownLine("\t2");
	t.InsDownLine("\t\t3");
	t.InsNextLine("\t\t4");
	t.InsNextLine("\t\t5");
	t.GoPrevLink(); t.GoPrevLink(); t.GoPrevLink();
	t.InsNextLine("\t6");
	t.Reset();
	t.InsNextLine("7");
	t.Reset();
	t.DelDownSection();
	TTextLink::MemCleaner(t);
	t.Reset();
	t.InsNextLine("8");

	EXPECT_EQ("8", t.GetLine());
}

TEST(TText, can_get_copy_v1)
{
	TTextLink::InitMemSystem();
	PTTextLink pl1 = new TTextLink("1");
	TText t(pl1);
	t.InsDownLine("\t2");
	t.InsDownLine("\t\t3");
	t.InsNextLine("\t\t4");
	t.InsNextLine("\t\t5");
	t.GoPrevLink(); t.GoPrevLink(); t.GoPrevLink();
	t.InsNextLine("\t6");
	t.Reset();
	t.InsNextLine("7");
	
	PTText ct = t.GetCopy();
	EXPECT_EQ(DataOK, ct->GetRetCode());
}

TEST(TText, can_get_copy_v2)
{
	TTextLink::InitMemSystem();
	PTTextLink pl1 = new TTextLink("1");
	TText t(pl1);
	t.InsDownLine("\t2");
	t.InsDownLine("\t\t3");
	t.InsNextLine("\t\t4");
	t.InsNextLine("\t\t5");
	t.GoPrevLink(); t.GoPrevLink(); t.GoPrevLink();
	t.InsNextLine("\t6");
	t.Reset();
	t.InsNextLine("7");

	PTText ct = t.GetCopy();

	for (t.Reset(), ct->Reset();!(t.IsTextEnded());t.GoNext(), ct->GoNext())
		EXPECT_EQ(t.GetLine(), ct->GetLine());
}