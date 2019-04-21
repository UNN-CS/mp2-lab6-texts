#include "TTextLink.h"
#include "gtest.h"


TEST(TTextLink, can_create_link_v1)
{
	ASSERT_NO_THROW(TTextLink l);
}

TEST(TTextLink, can_create_link_v2)
{
	TStr s = "test";

	ASSERT_NO_THROW(TTextLink l(s));
}

TEST(TTextLink, init_system_v1)
{
	TTextLink::InitMemSystem();
	PTTextLink tl = new TTextLink;

	EXPECT_NE(nullptr, tl);
}

TEST(TTextLink, init_system_v2)
{
	TTextLink::InitMemSystem(1);
	PTTextLink tl = new TTextLink;

	ASSERT_ANY_THROW(PTTextLink tl2 = new TTextLink);
}

TEST(TTextLink, default_constructor_v1)
{
	TTextLink l;

	EXPECT_EQ(NULL, l.GetDown());
}

TEST(TTextLink, default_constructor_v2)
{
	TTextLink l;

	EXPECT_EQ(NULL, l.GetNext());
}

TEST(TTextLink, is_atom_v1)
{
	TTextLink l;

	EXPECT_EQ(true, l.IsAtom());
}

TEST(TTextLink, is_atom_v2)
{
	TStr s = "test";
	TTextLink tl;
	PTTextLink p = &tl;
	TTextLink l(s,NULL,p);
	
	EXPECT_EQ(false, l.IsAtom());
}

TEST(TTextLink, _operator_new_v1)
{
	EXPECT_ANY_THROW(PTTextLink pl = new TTextLink);
}

TEST(TTextLink, _operator_new_v2)
{
	TTextLink::InitMemSystem(2);
	PTTextLink pl1 = new TTextLink;
	PTTextLink pl2 = new TTextLink;

	ASSERT_ANY_THROW(PTTextLink pl3 = new TTextLink);
}