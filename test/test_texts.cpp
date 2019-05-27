#include <gtest.h>
#include "TText.h"

TEST(TTextLink, can_init_mem_default)
{
	ASSERT_NO_THROW(TTextLink::InitMemSystem());
}

TEST(TTextLink, can_create_link_default)
{
	TTextLink::InitMemSystem();
	PTTextLink pLink;

	ASSERT_NO_THROW(pLink = new TTextLink);
}

TEST(TTextLink, can_create_link_with_text)
{
	TTextLink::InitMemSystem();
	PTTextLink pLink;

	ASSERT_NO_THROW(pLink = new TTextLink("Text"));
}

TEST(TTextLink, can_create_link)
{
	TTextLink::InitMemSystem();
	PTTextLink pLink;
	PTTextLink pLink2 = new TTextLink;
	PTTextLink pLink3 = new TTextLink;

	ASSERT_NO_THROW(pLink = new TTextLink("Text", pLink2, pLink3));
}

TEST(TTextLink, can_get_next_link)
{
	TTextLink::InitMemSystem();
	PTTextLink pLinkN = new TTextLink;
	PTTextLink pLinkD = new TTextLink;
	PTTextLink pLink = new TTextLink("Text", pLinkN, pLinkD);

	EXPECT_EQ(pLink->GetNext(), pLinkN);
}

TEST(TTextLink, can_get_down_link)
{
	TTextLink::InitMemSystem();
	PTTextLink pLinkN = new TTextLink;
	PTTextLink pLinkD = new TTextLink;
	PTTextLink pLink = new TTextLink("Text", pLinkN, pLinkD);

	EXPECT_EQ(pLink->GetDown(), pLinkD);
}

TEST(TTextLink, can_get_copy_link)
{
	TTextLink::InitMemSystem();
	PTTextLink pLinkN = new TTextLink;
	PTTextLink pLinkD = new TTextLink;
	PTTextLink pLink = new TTextLink("Text", pLinkN, pLinkD);
	PTTextLink pLinkCopy = (PTTextLink)pLink->GetCopy();
	bool flag = true;

	if (pLink->GetDown() != pLinkCopy->GetDown() || pLink->GetNext() != pLinkCopy->GetNext())
		flag = false;


	EXPECT_EQ(true, flag);
}

TEST(TTextLink, can_delete_link)
{
	TTextLink::InitMemSystem();
	PTTextLink pLink = new TTextLink;

	ASSERT_NO_THROW(delete pLink);
}

TEST(TText, can_create_link_with_text)
{
	ASSERT_NO_THROW(TTextLink("111"));
}

TEST(TText, can_create_null_link)
{
	ASSERT_NO_THROW(TTextLink());
}

TEST(TText, can_create_link)
{
	PTTextLink pNext = new TTextLink();
	PTTextLink pDown = new TTextLink();

	ASSERT_NO_THROW(TTextLink("111", pNext, pDown));
}

TEST(TText, can_create)
{
	PTTextLink plink;

	ASSERT_NO_THROW(TText(plink));
}

TEST(TText, can_get_copy)
{
	TText txt(new TTextLink("text"));
	TText* txt2;

	txt2 = txt.GetCopy();
	txt.Reset();
	txt2->Reset();

	EXPECT_EQ(txt.GetLine(), txt2->GetLine());
}

TEST(TText, can_ins_down_line_if_current_null)
{
	TText txt(new TTextLink());

	txt.InsDownLine("text");

	EXPECT_EQ(TextError, txt.GetRetCode());
}

TEST(TText, can_ins_down_section_if_current_null)
{
	TText txt(new TTextLink());

	txt.InsDownSection("text");

	EXPECT_EQ(TextError, txt.GetRetCode());
}

TEST(TText, can_ins_next_line_if_current_null)
{
	TText txt(new TTextLink());

	txt.InsNextLine("text");

	EXPECT_EQ(TextError, txt.GetRetCode());
}

TEST(TText, can_ins_next_section_if_current_null)
{
	TText txt(new TTextLink());

	txt.InsNextSection("text");

	EXPECT_EQ(TextError, txt.GetRetCode());
}

TEST(TText, can_ins_down_line)
{
	TTextLink::InitMemSystem(2);
	TText txt(new TTextLink("text"));

	txt.GoFirstLink();
	txt.InsDownLine("text2");
	txt.GoDownLink();

	EXPECT_EQ(txt.GetLine(), "text2");
}

TEST(TText, can_ins_down_long_line)
{
	TTextLink::InitMemSystem(2);
	TText txt(new TTextLink("text"));

	txt.GoFirstLink();
	txt.InsDownLine("ttttttttttttttttttttttttttttt");

	EXPECT_EQ(txt.GetRetCode(), TooLongString);

}

TEST(TText, can_ins_down_section)
{
	TTextLink::InitMemSystem(2);
	TText txt(new TTextLink("text"));

	txt.GoFirstLink();
	txt.InsDownSection("text2");
	txt.GoDownLink();

	EXPECT_EQ(txt.GetLine(), "text2");
}

TEST(TText, can_ins_down_long_section)
{
	TTextLink::InitMemSystem(2);
	TText txt(new TTextLink("text"));

	txt.GoFirstLink();
	txt.InsDownSection("ttttttttttttttttttttttttttttt");

	EXPECT_EQ(txt.GetRetCode(), TooLongString);
}

TEST(TText, can_ins_next_line)
{
	TTextLink::InitMemSystem(2);
	TText txt(new TTextLink("text"));

	txt.GoFirstLink();
	txt.InsNextLine("text2");
	txt.GoNextLink();

	EXPECT_EQ(txt.GetLine(), "text2");
}

TEST(TText, can_ins_next_long_line)
{
	TTextLink::InitMemSystem(2);
	TText txt(new TTextLink("text"));

	txt.GoFirstLink();
	txt.InsNextLine("ttttttttttttttttttttttttttttt");

	EXPECT_EQ(txt.GetRetCode(), TooLongString);
}

TEST(TText, can_ins_next_section)
{
	TTextLink::InitMemSystem(2);
	TText txt(new TTextLink("text"));

	txt.GoFirstLink();
	txt.InsNextSection("text2");
	txt.GoNextLink();

	EXPECT_EQ(txt.GetLine(), "text2");
}

TEST(TText, can_ins_next_long_section)
{
	TTextLink::InitMemSystem(2);
	TText txt(new TTextLink("text"));

	txt.GoFirstLink();
	txt.InsNextSection("ttttttttttttttttttttttttttttt");

	EXPECT_EQ(txt.GetRetCode(), TooLongString);
}

TEST(TText, no_del_down_line_which_have_down_line)
{
	TTextLink::InitMemSystem(3);
	TText txt(new TTextLink("text"));

	txt.GoFirstLink();
	txt.InsDownLine("text2");
	txt.GoDownLink();
	txt.InsDownLine("text3");
	txt.GoFirstLink();
	txt.DelDownLine();
	txt.GoDownLink();

	EXPECT_EQ(txt.GetLine(), "text2");
}

TEST(TText, can_del_down_line)
{
	TTextLink::InitMemSystem(2);
	TText txt(new TTextLink("text"));

	txt.GoFirstLink();
	txt.InsDownLine("text2");
	txt.DelDownLine();
	txt.GoDownLink();

	EXPECT_EQ(TextError, txt.GetRetCode());
}

TEST(TText, no_del_next_line_which_have_down_line)
{
	TTextLink::InitMemSystem(3);
	TText txt(new TTextLink("text"));

	txt.GoFirstLink();
	txt.InsNextLine("text2");
	txt.GoNextLink();
	txt.InsDownLine("text3");
	txt.GoFirstLink();
	txt.DelNextLine();
	txt.GoNextLink();

	EXPECT_EQ(txt.GetLine(), "text2");
}

TEST(TText, can_del_next_line)
{
	TTextLink::InitMemSystem(2);
	TText txt(new TTextLink("text"));

	txt.GoFirstLink();
	txt.InsNextLine("text2");
	txt.DelNextLine();
	txt.GoNextLink();

	EXPECT_EQ(TextError, txt.GetRetCode());
}

TEST(TText, can_del_down_section)
{
	TTextLink::InitMemSystem(3);
	TText txt(new TTextLink("text"));

	txt.GoFirstLink();
	txt.InsDownSection("text2");
	txt.GoDownLink();
	txt.InsNextLine("text3");

	txt.GoFirstLink();
	txt.DelDownSection();
	txt.GoDownLink();

	EXPECT_EQ(txt.GetLine(), "text3");
}

TEST(TText, can_del_next_section)
{
	TTextLink::InitMemSystem(3);
	TText txt(new TTextLink("text"));

	txt.GoFirstLink();
	txt.InsNextSection("text2");
	txt.GoNextLink();
	txt.InsNextLine("text3");

	txt.GoFirstLink();
	txt.DelNextSection();
	txt.GoNextLink();

	EXPECT_EQ(txt.GetLine(), "text3");
}

TEST(TText, can_reset)
{
	TTextLink::InitMemSystem(3);
	TText txt(new TTextLink("text"));

	txt.GoFirstLink();
	txt.InsNextLine("text2");
	txt.GoNextLink();
	txt.InsNextLine("text3");
	txt.GoNextLink();

	txt.Reset();

	EXPECT_EQ(txt.GetLine(), "text");
}

TEST(TText, can_go_next)
{
	TTextLink::InitMemSystem(3);
	TText txt(new TTextLink("text"));

	txt.GoFirstLink();
	txt.InsNextLine("text2");
	txt.GoNextLink();
	txt.InsNextLine("text3");
	txt.GoNextLink();

	txt.Reset();
	txt.GoNext();

	EXPECT_EQ(txt.GetLine(), "text2");
}

TEST(TText, can_go_next_if_end)
{
	TTextLink::InitMemSystem(3);
	TText txt(new TTextLink("text"));

	txt.GoFirstLink();
	txt.InsNextLine("text2");
	txt.GoNextLink();
	txt.InsNextLine("text3");
	txt.GoNextLink();

	txt.GoNext();
	txt.GoNext();

	EXPECT_EQ(txt.GetLine(), "text3");
}

TEST(TText, can_chek_end_text_return_false)
{
	TTextLink::InitMemSystem(3);
	TText txt(new TTextLink("text"));

	txt.GoFirstLink();
	txt.InsNextLine("text2");
	txt.GoNextLink();
	txt.InsNextLine("text3");
	txt.GoNextLink();

	txt.Reset();
	txt.GoNext();

	EXPECT_EQ(txt.IsTextEnded(), 0);
}

TEST(TText, can_chek_end_text_return_true)
{
	TTextLink::InitMemSystem(3);
	TText txt(new TTextLink("text"));

	txt.GoFirstLink();
	txt.InsNextLine("text2");
	txt.GoNextLink();
	txt.InsNextLine("text3");
	txt.GoNextLink();

	txt.Reset();
	txt.GoNext();
	txt.GoNext();
	txt.GoNext();

	EXPECT_EQ(txt.IsTextEnded(), 1);
}

TEST(TText, can_go_first_link)
{
	TTextLink::InitMemSystem(3);
	TText txt(new TTextLink("text"));

	txt.GoFirstLink();

	EXPECT_EQ(txt.GetLine(), "text");
}

TEST(TText, can_go_down_link_if_down_null)
{
	TTextLink::InitMemSystem(3);
	TText txt(new TTextLink("text"));

	txt.GoDownLink();

	EXPECT_EQ(TextError, txt.GetRetCode());
}

TEST(TText, can_go_down_link)
{
	TTextLink::InitMemSystem(3);
	TText txt(new TTextLink("text"));

	txt.GoFirstLink();
	txt.InsDownSection("text2");
	txt.GoDownLink();

	EXPECT_EQ(txt.GetLine(), "text2");
}

TEST(TText, can_go_next_link_if_next_null)
{
	TTextLink::InitMemSystem(3);
	TText txt(new TTextLink("text"));

	txt.GoNextLink();

	EXPECT_EQ(TextError, txt.GetRetCode());
}

TEST(TText, can_go_next_link)
{
	TTextLink::InitMemSystem(3);
	TText txt(new TTextLink("text"));

	txt.GoFirstLink();
	txt.InsNextSection("text2");
	txt.GoNextLink();

	EXPECT_EQ(txt.GetLine(), "text2");
}

TEST(TText, can_go_prev_link_if_not_prev)
{
	TTextLink::InitMemSystem(3);
	TText txt(new TTextLink("text"));

	txt.GoFirstLink();
	txt.GoPrevLink();

	EXPECT_EQ(TextNoPrev, txt.GetRetCode());
}

TEST(TText, can_go_prev_link)
{
	TTextLink::InitMemSystem(3);
	TText txt(new TTextLink("text"));

	txt.GoFirstLink();
	txt.InsDownSection("text2");
	txt.GoDownLink();
	txt.GoPrevLink();

	EXPECT_EQ(txt.GetLine(), "text");
}

TEST(TText, can_get_line)
{
	TTextLink::InitMemSystem(3);
	TText txt(new TTextLink("text"));

	txt.GoFirstLink();

	EXPECT_EQ(txt.GetLine(), "text");
}

TEST(TText, can_get_line_if_current_null)
{
	TTextLink::InitMemSystem(3);
	TText txt(new TTextLink());

	txt.GoFirstLink();

	EXPECT_EQ(txt.GetLine(), "");
}

TEST(TText, can_set_line)
{
	TTextLink::InitMemSystem(3);
	TText txt(new TTextLink("text"));

	txt.GoFirstLink();
	txt.SetLine("text2");

	EXPECT_EQ(txt.GetLine(), "text2");
}

TEST(TText, can_set_long_line)
{
	TTextLink::InitMemSystem(3);
	TText txt(new TTextLink("text"));

	txt.GoFirstLink();

	txt.SetLine("ttttttttttttttttttttttttt");

	EXPECT_EQ(txt.GetRetCode(), TooLongString);
}

TEST(TText, can_get_copy_text)
{
	TTextLink::InitMemSystem(10);
	TText txt(new TTextLink("text"));
	PTText txtCopy;
	bool flag = true;

	txt.GoFirstLink();
	txt.InsNextLine("text2");
	txt.GoNextLink();
	txt.InsNextLine("text3");
	txt.GoNextLink();
	txt.InsNextLine("text4");
	txt.GoNextLink();
	txt.InsNextLine("text5");
	txt.GoNextLink();

	txtCopy = txt.GetCopy();

	for (txt.Reset(), txtCopy->Reset(); txt.IsTextEnded() ||
		txtCopy->IsTextEnded(); txt.GoNext(), txtCopy->GoNext())
	{
		if (txt.GetLine() != txtCopy->GetLine())
			flag = false;
	}

	EXPECT_TRUE(flag);
}

TEST(TText, if_change_copy_don_not_change_original)
{
	TTextLink::InitMemSystem(10);
	TText txt(new TTextLink("text"));
	PTText txtCopy;
	bool flag = true;

	txt.GoFirstLink();
	txt.InsNextLine("text2");
	txt.GoNextLink();
	txt.InsNextLine("text3");
	txt.GoNextLink();
	txt.InsNextLine("text4");
	txt.GoNextLink();
	txt.InsNextLine("text5");
	txt.GoNextLink();

	txtCopy = txt.GetCopy();

	txt.GoFirstLink();
	txt.SetLine("CHANGE");

	txtCopy->GoFirstLink();
	EXPECT_NE(txtCopy->GetLine(), "CHANGE");
}