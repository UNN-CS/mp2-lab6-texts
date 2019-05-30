#include "gtest.h"

#include "TTextLink.h"
#include "TText.h"

TEST(TTextLink, can_init_mem)
{
	ASSERT_NO_THROW(TTextLink::InitMemSystem());
}

TEST(TTextLink, can_create_link)
{
	TTextLink::InitMemSystem();
	ASSERT_NO_THROW(TTextLink tl(""));
}

TEST(TTextLink, can_get_copy)
{
	TTextLink::InitMemSystem();
	TTextLink tl1("");
	ASSERT_NO_THROW(PTTextLink tl2 = (PTTextLink)tl1.GetCopy());
}

TEST(TText, can_create_text)
{
	TTextLink::InitMemSystem();
	ASSERT_NO_THROW(TText t);
}

TEST(TText, can_set_line)
{
	TTextLink::InitMemSystem();
	TText t;
	ASSERT_NO_THROW(t.SetLine("8"));
}

TEST(TText, can_insert_down_line)
{
	TTextLink::InitMemSystem();
	TText t;
	ASSERT_NO_THROW(t.InsDownLine("800"));
}

TEST(TText, can_insert_down_section)
{
	TTextLink::InitMemSystem();
	TText t;
	ASSERT_NO_THROW(t.InsDownSection("555"));
}

TEST(TText, can_insert_next_line)
{
	TTextLink::InitMemSystem();
	TText t;
	ASSERT_NO_THROW(t.InsNextLine("3535"));
}

TEST(TText, can_insert_next_section)
{
	TTextLink::InitMemSystem();
	TText t;
	ASSERT_NO_THROW(t.InsNextSection("better"));
}

TEST(TText, can_get_line)
{
	TTextLink::InitMemSystem();
	TText t;
	t.SetLine("call");
	ASSERT_NO_THROW(t.GetLine());
}

TEST(TText, can_delete_down_line)
{
	TTextLink::InitMemSystem();
	TText t;
	t.InsDownLine("than");
	ASSERT_NO_THROW(t.DelDownLine());
}

TEST(TText, can_delete_down_section)
{
	TTextLink::InitMemSystem();
	TText t;
	t.InsDownSection("borrow");
	ASSERT_NO_THROW(t.DelDownSection());
}

TEST(TText, can_delete_next_line)
{
	TTextLink::InitMemSystem();
	TText t;
	t.InsNextLine("money");
	ASSERT_NO_THROW(t.DelNextLine());
}

TEST(TText, can_delete_next_section)
{
	TTextLink::InitMemSystem();
	TText t;
	t.InsDownLine("from someone");
	ASSERT_NO_THROW(t.DelNextSection());
}

TEST(TText, can_go_next)
{
	TTextLink::InitMemSystem();
	TText t;
	t.SetLine("1");
	t.InsDownLine("2");
	t.InsNextLine("3");
	t.Reset();
	EXPECT_EQ("1", t.GetLine());
	t.GoNext();
	EXPECT_EQ("2", t.GetLine());
	t.GoNext();
	EXPECT_EQ("3", t.GetLine());
	t.GoNext();
	EXPECT_EQ("1", t.GetLine());
}
