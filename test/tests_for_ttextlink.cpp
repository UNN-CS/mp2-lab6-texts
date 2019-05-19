#include <gtest.h>

#include "TTextLink.h"

TEST(TTextLink, Can_Init_Mem_System) {
    ASSERT_NO_THROW(TTextLink::InitMemSystem(5));
}

TEST(TTextLink, Can_Init_Mem_System_Without_Parametres) {
    ASSERT_NO_THROW(TTextLink::InitMemSystem());
}

TEST(TTextLink, Can_Create_Link) {
	 ASSERT_NO_THROW(TTextLink t);
}

TEST(TTextLink, Can_Create_Link_With_Line) {
	 ASSERT_NO_THROW(TTextLink t("qwerty"));
}

TEST(TTextLink, Create_Link_Without_Parameters_Is_Correct) {
	 TTextLink::InitMemSystem();
	 TTextLink t;

	 EXPECT_EQ(NULL, t.GetNext());
	 EXPECT_EQ(NULL, t.GetDown());
}

TEST(TTextLink, Operator_New_Is_Correct) {
	TTextLink::InitMemSystem(1);
	PTTextLink t1 = new TTextLink;

 	ASSERT_ANY_THROW(PTTextLink t2 = new TTextLink);
}

 TEST(TTextLink, Can_Get_Copy)
{
	TTextLink::InitMemSystem();
    TTextLink t("qwerty");

    ASSERT_NO_THROW(PTTextLink t2 = (PTTextLink)t.GetCopy());
}