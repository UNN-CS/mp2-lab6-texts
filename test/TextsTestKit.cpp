#include <gtest/gtest.h>
#include "TText.h"

TEST(TTextLink, Can_not_operator_new_if_memory_has_not_been_initialized)
{
    ASSERT_ANY_THROW(new TTextLink());
}

TEST(TTextLink, Initialize_memory_system_without_parameters)
{
    ASSERT_NO_THROW(TTextLink::InitMemSystem());
}

TEST(TTextLink, Initialize_memory_system_with_positive_parameter)
{
    ASSERT_NO_THROW(TTextLink::InitMemSystem(100));
}

TEST(TTextLink, Can_not_initialize_memory_system_with_parameter_0)
{
    ASSERT_ANY_THROW(TTextLink::InitMemSystem(0));
}

TEST(TTextLink, Can_not_initialize_memory_system_with_negative_size)
{
    ASSERT_ANY_THROW(TTextLink::InitMemSystem(-1));
}

TEST(TTextLink, Create_TextLink_without_parameters)
{
    ASSERT_NO_THROW(PTTextLink link1 = new TTextLink);
    ASSERT_NO_THROW(TTextLink link2);
}

TEST(TTextLink, Create_TextLink_with_first_parameter)
{
    char ch[] = "Metallica";
    
    ASSERT_NO_THROW(PTTextLink link1 = new TTextLink(ch));
    ASSERT_NO_THROW(TTextLink link2(ch));
}

TEST(TTextLink, Create_TextLink_with_text)
{
    ASSERT_NO_THROW(TTextLink link1("Metallica"));
    ASSERT_NO_THROW(PTTextLink link2 = new TTextLink("Ozzy Osbourne"));
}

TEST(TTextLink, Create_TextLink_with_second_parameter)
{
    char ch[] = "Metallica";
    PTTextLink nextLink = new TTextLink(ch);

    ASSERT_NO_THROW(PTTextLink link1 = new TTextLink(ch, nextLink));
    ASSERT_NO_THROW(TTextLink link2(ch, nextLink));
}

TEST(TTextLink, Create_TextLink_with_third_parameter)
{
    char ch[] = "Metallica";
    PTTextLink downLink = new TTextLink(ch);
    PTTextLink nextLink = new TTextLink(ch);

    ASSERT_NO_THROW(PTTextLink link1 = new TTextLink(ch, nullptr, downLink));
    ASSERT_NO_THROW(TTextLink link2(ch, nextLink, downLink));
}

TEST(TTextLink, Can_not_create_TextLink_longer_string)
{
    char ch[TextLineLength + 1];
    for (int i = 0; i < TextLineLength + 1; i++)
        ch[i] = 'a';

    ASSERT_ANY_THROW(TTextLink link(ch));
}

TEST(TTextLink, Operator_delete_increases_free_links)
{
    TTextLink::InitMemSystem();
    PTTextLink link = new TTextLink("Metallica");
    EXPECT_NE(TTextLink::GetFreeCount(), MemSize);
    delete(link);
    EXPECT_EQ(TTextLink::GetFreeCount(), MemSize);
}


TEST(TText, TText_construct_with_text_parameter)
{
    TTextLink::InitMemSystem(1);
    char ch[] = "Metallica";
    TText text(new TTextLink(ch));
    text.GoFirstLink();

    EXPECT_EQ(ch, text.GetLine());
}

TEST(TText, TText_construct_is_correct_with_empty_TTextLink) 
{
    TTextLink::InitMemSystem(1);
    TText text(new TTextLink());
    text.GoFirstLink();

    EXPECT_EQ("", text.GetLine());
}

TEST(TText, GetCopy)
{
    TTextLink::InitMemSystem(2);
    TText text(new TTextLink("Metallica"));
    PTText pText = text.GetCopy();

    text.Reset();
    pText->Reset();

    EXPECT_EQ(text.GetLine(), pText->GetLine());
}

TEST(TText, GetCopy_text)
{
    TTextLink::InitMemSystem(8);
    TText text(new TTextLink("text1"));
    PTText textCopy;
    bool check = true;

    text.GoFirstLink();
    text.InsNextLine("text2");
    text.GoNextLink();
    text.InsNextLine("text3");
    text.GoNextLink();
    text.InsNextLine("text4");
    text.GoNextLink();

    textCopy = text.GetCopy();
    text.Reset();
    textCopy->Reset();
    while (text.IsTextEnded() && textCopy->IsTextEnded())
    {
        if (text.GetLine() != textCopy->GetLine())
            check = false;
        text.GoNext();
        textCopy->GoNext();
    }

    EXPECT_TRUE(check);
}

TEST(TText, can_go_first_link)
{
    TTextLink::InitMemSystem(1);
    TText text(new TTextLink("Metallica"));

    text.GoFirstLink();

    EXPECT_EQ(text.GetLine(), "Metallica");
}

TEST(TText, GoDownLink)
{
    TTextLink::InitMemSystem(2);
    TText text(new TTextLink("text1"));

    text.GoFirstLink();
    text.InsDownSection("text2");
    text.GoDownLink();

    EXPECT_EQ(text.GetLine(), "text2");
}

TEST(TText, Not_GoDownLink_if_down_is_null)
{
    TTextLink::InitMemSystem(1);
    TText text(new TTextLink("text"));

    text.GoDownLink();

    EXPECT_EQ(TextError, text.GetRetCode());
}

TEST(TText, GoNextLink)
{
    TTextLink::InitMemSystem(2);
    TText text(new TTextLink("text1"));

    text.GoFirstLink();
    text.InsNextSection("text2");
    text.GoNextLink();

    EXPECT_EQ(text.GetLine(), "text2");
}

TEST(TText, Not_GoNextLink_if_next_is_null)
{
    TTextLink::InitMemSystem(1);
    TText text(new TTextLink("text"));

    text.GoNextLink();

    EXPECT_EQ(TextError, text.GetRetCode());
}

TEST(TText, GoPrevLink)
{
    TTextLink::InitMemSystem(2);
    TText text(new TTextLink("text1"));

    text.GoFirstLink();
    text.InsDownSection("text2");
    text.GoDownLink();
    text.GoPrevLink();

    EXPECT_EQ(text.GetLine(), "text1");
}

TEST(TText, Not_GoPrevLink_if_not_prev)
{
    TTextLink::InitMemSystem(1);
    TText text(new TTextLink("Metallica"));

    text.GoFirstLink();
    text.GoPrevLink();

    EXPECT_EQ(TextNoPrev, text.GetRetCode());
}

TEST(TText, GetLine)
{
    TTextLink::InitMemSystem(1);
    TText text(new TTextLink("Metallica"));

    text.GoFirstLink();

    EXPECT_EQ(text.GetLine(), "Metallica");
}

TEST(TText, GetLine_if_current_is_null)
{
    TTextLink::InitMemSystem(1);
    TText text(new TTextLink());

    text.GoFirstLink();

    EXPECT_EQ(text.GetLine(), "");
}

TEST(TText, SetLine)
{
    TTextLink::InitMemSystem(1);
    TText text(new TTextLink("text"));

    text.GoFirstLink();
    text.SetLine("Edited text");

    EXPECT_EQ(text.GetLine(), "Edited text");
}

TEST(TText, Not_SetLine_too_long_line)
{
    char ch[TextLineLength + 1];
    for (int i = 0; i < TextLineLength + 1; i++)
        ch[i] = 'a';
    TTextLink::InitMemSystem(1);
    TText text(new TTextLink("Metallica"));

    text.GoFirstLink();
    text.SetLine(ch);

    EXPECT_EQ(text.GetRetCode(), TextTooLongString);
}

TEST(TText, Not__SetLine_if_current_is_null)
{
    TTextLink::InitMemSystem(1);
    TText text;

    text.SetLine("text");

    EXPECT_EQ(text.GetRetCode(), TextError);
}

TEST(TText, InsDownLine)
{
    TTextLink::InitMemSystem(2);
    TText text(new TTextLink("Metallica"));

    text.GoFirstLink();
    text.InsDownLine("Rammstein");
    text.GoDownLink();

    EXPECT_EQ(text.GetLine(), "Rammstein");
}

TEST(TText, Not_InsDownLine_if_current_link_is_null)
{
    TTextLink::InitMemSystem(1);
    TText text(new TTextLink());

    text.InsDownLine("Metallica");

    EXPECT_EQ(TextError, text.GetRetCode());
}

TEST(TText, Not_InsDownLine_too_long_line)
{
    char ch[TextLineLength + 1];
    for (int i = 0; i < TextLineLength + 1; i++)
        ch[i] = 'a';
    TTextLink::InitMemSystem(2);
    TText text(new TTextLink("Metallica"));

    text.GoFirstLink();
    text.InsDownLine(ch);

    EXPECT_EQ(TextTooLongString, text.GetRetCode());
}

TEST(TText, InsDownSection)
{
    TTextLink::InitMemSystem(2);
    TText text(new TTextLink("Metallica"));

    text.GoFirstLink();
    text.InsDownSection("Beatles");
    text.GoDownLink();

    EXPECT_EQ(text.GetLine(), "Beatles");
}

TEST(TText, Not_InsDownSection_if_current_link_is_null)
{
    TTextLink::InitMemSystem(1);
    TText text(new TTextLink());

    text.InsDownSection("Metallica");

    EXPECT_EQ(TextError, text.GetRetCode());
}

TEST(TText, Not_InsDownSection_too_long_section)
{
    char ch[TextLineLength + 1];
    for (int i = 0; i < TextLineLength + 1; i++)
        ch[i] = 'a';
    TTextLink::InitMemSystem(2);
    TText text(new TTextLink("Metallica"));

    text.GoFirstLink();
    text.InsDownSection(ch);

    EXPECT_EQ(TextTooLongString, text.GetRetCode());
}

TEST(TText, InsNextLine)
{
    TTextLink::InitMemSystem(2);
    TText text(new TTextLink("Metallica"));

    text.GoFirstLink();
    text.InsNextLine("Rammstein");
    text.GoNextLink();

    EXPECT_EQ(text.GetLine(), "Rammstein");
}

TEST(TText, Not_InsNextLine_if_current_link_is_null)
{
    TTextLink::InitMemSystem(1);
    TText text(new TTextLink());

    text.InsNextLine("Metallica");

    EXPECT_EQ(TextError, text.GetRetCode());
}

TEST(TText, Not_InsNextLine_too_long_line)
{
    char ch[TextLineLength + 1];
    for (int i = 0; i < TextLineLength + 1; i++)
        ch[i] = 'a';
    TTextLink::InitMemSystem(2);
    TText text(new TTextLink("Metallica"));

    text.GoFirstLink();
    text.InsNextLine(ch);

    EXPECT_EQ(TextTooLongString, text.GetRetCode());
}

TEST(TText, InsNextSection)
{
    TTextLink::InitMemSystem(2);
    TText text(new TTextLink("Metallica"));

    text.GoFirstLink();
    text.InsNextSection("Ozzy Osbourne");
    text.GoNextLink();

    EXPECT_EQ(text.GetLine(), "Ozzy Osbourne");
}

TEST(TText, Not_InsNextSection_if_current_null)
{
    TTextLink::InitMemSystem(1);
    TText text(new TTextLink());

    text.InsNextSection("Metallica");

    EXPECT_EQ(TextError, text.GetRetCode());
}

TEST(TText, Not_InsNextSection_too_long_section)
{
    char ch[TextLineLength + 1];
    for (int i = 0; i < TextLineLength + 1; i++)
        ch[i] = 'a';
    TTextLink::InitMemSystem(2);
    TText text(new TTextLink("Metallica"));

    text.GoFirstLink();
    text.InsNextSection(ch);

    EXPECT_EQ(TextTooLongString, text.GetRetCode());
}

TEST(TText, DelDownLine)
{
    TTextLink::InitMemSystem(2);
    TText text(new TTextLink("Metallica"));

    text.GoFirstLink();
    text.InsDownLine("Ozzy");
    text.DelDownLine();

    EXPECT_EQ(TextNoDown, text.GoDownLink());
}

TEST(TText, Not_DelDownLine_which_have_down_line)
{
    TTextLink::InitMemSystem(3);
    TText text(new TTextLink("text1"));

    text.GoFirstLink();
    text.InsDownLine("text2");
    text.GoDownLink();
    text.InsDownLine("text3");
    text.GoFirstLink();
    text.DelDownLine();
    text.GoDownLink();

    EXPECT_EQ(text.GetLine(), "text2");
}

TEST(TText, DelDownSection)
{
    TTextLink::InitMemSystem(3);
    TText text(new TTextLink("text1"));

    text.GoFirstLink();
    text.InsDownSection("text2");
    text.GoDownLink();
    text.InsNextLine("text3");
    text.GoFirstLink();
    text.DelDownSection();
    text.GoDownLink();

    EXPECT_EQ(text.GetLine(), "text3");
}

TEST(TText, DelNextLine)
{
    TTextLink::InitMemSystem(2);
    TText text(new TTextLink("text1"));

    text.GoFirstLink();
    text.InsNextLine("text2");
    text.DelNextLine();

    EXPECT_EQ(TextNoNext, text.GoNextLink());
}

TEST(TText, Not_DelNextLine_which_have_down_line)
{
    TTextLink::InitMemSystem(3);
    TText text(new TTextLink("text1"));

    text.GoFirstLink();
    text.InsNextLine("text2");
    text.GoNextLink();
    text.InsDownLine("text3");
    text.GoFirstLink();
    text.DelNextLine();
    text.GoNextLink();

    EXPECT_EQ(text.GetLine(), "text2");
}

TEST(TText, DelNextSection)
{
    TTextLink::InitMemSystem(3);
    TText text(new TTextLink("text1"));

    text.GoFirstLink();
    text.InsNextSection("text2");
    text.GoNextLink();
    text.InsNextLine("text3");
    text.GoFirstLink();
    text.DelNextSection();
    text.GoNextLink();

    EXPECT_EQ(text.GetLine(), "text3");
}

TEST(TText, Reset)
{
    TTextLink::InitMemSystem(3);
    TText text(new TTextLink("text1"));

    text.GoFirstLink();
    text.InsNextLine("text2");
    text.GoNextLink();
    text.InsNextLine("text3");
    text.GoNextLink();
    text.Reset();

    EXPECT_EQ(text.GetLine(), "text1");
}

TEST(TText, GoNext)
{
    TTextLink::InitMemSystem(3);
    TText text(new TTextLink("text1"));

    text.GoFirstLink();
    text.InsNextLine("text2");
    text.GoNextLink();
    text.InsNextLine("text3");
    text.GoNextLink();

    text.Reset();
    text.GoNext();

    EXPECT_EQ(text.GetLine(), "text2");
}

TEST(TText, GoNext_if_end)
{
    TTextLink::InitMemSystem(3);
    TText text(new TTextLink("text1", new TTextLink("text2")));

    text.GoFirstLink();
    text.GoNextLink();
    text.InsNextLine("text3");
    text.GoNextLink();
    text.GoNext();
    text.GoNext();

    EXPECT_EQ(text.GetLine(), "text3");
    EXPECT_EQ(TextEnded, text.GoNext());
}


TEST(TText, gonext_is_true_when_textnoended)
{
    TTextLink::InitMemSystem(3);
    TText text(new TTextLink("text1"));
    text.GoFirstLink();
    text.InsNextLine("text2");
    text.GoNextLink();
    text.InsDownLine("text3");
    text.Reset();

    EXPECT_EQ(TextOk, text.GoNext());
    EXPECT_EQ(TextOk, text.GoNext());
    EXPECT_EQ(TextEnded, text.GoNext());
}

TEST(TText, IsTextEnded_check_return_true)
{
    TTextLink::InitMemSystem(3);
    TText text(new TTextLink("text1"));

    text.GoFirstLink();
    text.InsNextLine("text2");
    text.GoNextLink();
    text.InsNextLine("text3");
    text.GoNextLink();
    text.Reset();
    text.GoNext();
    text.GoNext();
    text.GoNext();

    EXPECT_TRUE(text.IsTextEnded());
}

TEST(TText, IsTextEnded_check_return_false)
{
    TTextLink::InitMemSystem(3);
    TText text(new TTextLink("text1"));

    text.GoFirstLink();
    text.InsNextLine("text2");
    text.GoNextLink();
    text.InsNextLine("text3");
    text.GoNextLink();
    text.Reset();
    text.GoNext();

    EXPECT_FALSE(text.IsTextEnded());
}