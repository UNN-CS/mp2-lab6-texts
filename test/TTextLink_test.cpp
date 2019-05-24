#include <gtest.h>
#include "TTextLink.h"
TEST(TTextLink, can_create_empty_Link)
{
    TTextLink::InitMemSystem(1);
    ASSERT_NO_THROW(new TTextLink());
}
TEST(TTextLink, can_create_link)
{
    TTextLink::InitMemSystem(1);
    ASSERT_NO_THROW(new TTextLink((char *)"test"));
}
TEST(TTextLink, can_printFreeLink)
{
    TTextLink::InitMemSystem(1);
    TTextLink tmp((char *)"hello");
    ASSERT_NO_THROW(tmp.PrintFreeLink());
}
TEST(TTextLink, can_detect_atom)
{
    TTextLink::InitMemSystem(2);
    PTTextLink tmp = new TTextLink;
    TTextLink notAtom((char*)"sometext", NULL, tmp);
    EXPECT_EQ(0, notAtom.IsAtom());
}
TEST(TTextLink, can_get_next)
{
    TTextLink::InitMemSystem(2);
    PTTextLink tmp = new TTextLink;
    TTextLink testLink((char*)"sometext", tmp, NULL);
    EXPECT_EQ(tmp, testLink.GetNext());
}

TEST(TTextLink, can_get_down)
{
    TTextLink::InitMemSystem(2);
    PTTextLink tmp = new TTextLink;
    TTextLink testLink((char*)"sometext", NULL, tmp);
    EXPECT_EQ(tmp, testLink.GetDown());
}
TEST(TTextLink, get_copy_has_its_own_mem)
{
    TTextLink::InitMemSystem(2);
    PTTextLink testLink = new TTextLink((char*)"sometext", NULL, NULL);
    PTTextLink tmp = (PTTextLink)testLink->GetCopy();
    EXPECT_NE(tmp, testLink);
}
