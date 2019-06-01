#include <gtest.h>
#include "ttext.h"
#include "textlink.h"

TEST(TTextLink, Can_Create_Link)
{
    TTextLink::InitMemSystem(120);
    ASSERT_NO_THROW(TTextLink tl("Hello, it's me"));
}

TEST(TTextLink, Can_Init_Memory)
{
    ASSERT_NO_THROW(TTextLink::InitMemSystem());
}

TEST(TTextLink, Can_Get_Copy)
{
    TTextLink::InitMemSystem();
    TTextLink tl1("Hello, it's me");
    ASSERT_NO_THROW(PTTextLink tl2 = (PTTextLink)tl1.GetCopy());
}

TEST(TText, Can_Create_TText)
{
    TTextLink::InitMemSystem();
    TTextLink tl("Hello, it's me");
    ASSERT_NO_THROW(TText tt(&tl));
}

TEST(TText, Can_Insert_Down_Line)
{
    TTextLink::InitMemSystem(120);
    TText tt;
    ASSERT_NO_THROW(tt.InsDownLine("Hello, it's me"));
}

TEST(TText, Can_Insert_Down_Section)
{
    TTextLink::InitMemSystem(120);
    TText tt;
    ASSERT_NO_THROW(tt.InsDownSection("Hello"));
}

TEST(TText, Can_Insert_Next_Line)
{
    TTextLink::InitMemSystem(120);
    TText tt;
    ASSERT_NO_THROW(tt.InsNextLine("darkness"));
}

TEST(TText, Can_Insert_Next_Section)
{
    TTextLink::InitMemSystem(120);
    TText tt;
    ASSERT_NO_THROW(tt.InsNextSection("my old friend"));
}

TEST(TText, Can_Delete_Down_Line)
{
    TTextLink::InitMemSystem(120);
    TText tt;
    tt.InsDownLine("Pretty woman");
    ASSERT_NO_THROW(tt.DelDownLine());
}

TEST(TText, Can_Delete_Down_Section)
{
    TTextLink::InitMemSystem(120);
    TText tt;
    tt.InsDownSection("walking down the street");
    ASSERT_NO_THROW(tt.DelDownSection());
}

TEST(TText, Can_Delete_Next_Line)
{
    TTextLink::InitMemSystem(120);
    TText tt;
    tt.InsNextLine("Pretty woman");
    ASSERT_NO_THROW(tt.DelNextLine());
}

TEST(TText, Can_Delete_Next_Section)
{
    TTextLink::InitMemSystem(120);
    TText tt;
    tt.InsDownLine("the kind I like to meet");
    ASSERT_NO_THROW(tt.DelNextSection());
}