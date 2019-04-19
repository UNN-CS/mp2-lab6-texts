#include <gtest/gtest.h>
#include "include/ttext.h"

const char *txt = "../test/text1.txt";
const char *txt2 = "../test/text2.txt";

TEST(TText, create_no_throw)
{
  EXPECT_NO_THROW(TText t);
}

TEST(TText, print_no_throw)
{
  TText t;

  t.Read(txt);

  EXPECT_NO_THROW(t.Print());
}

TEST(TText, get_copy_no_throw)
{
  TText t;

  EXPECT_NO_THROW(t.GetCopy());
}

TEST(TText, get_copy)
{
  TText t;
  PTText pt;

  t.Read(txt);
  pt = t.GetCopy();
  t.Reset();
  pt->Reset();

  EXPECT_EQ(t.GetLine(), pt->GetLine());
  while(!t.IsTextEnded() && !pt->IsTextEnded())
  {
    t.GoNext();
    pt->GoNext();
    EXPECT_EQ(t.GetLine(), pt->GetLine());
  }
}

TEST(TText, go_first)
{
  TText t;

  for(int i = 0; i < 5; ++i)
  {
    t.InsDownLine("sample_text");
    t.InsNextLine("sample_text");
    t.GoDownLink();
  }

  EXPECT_TRUE(t.GoFirstLink());
  EXPECT_FALSE(t.GoFirstLink());
}

TEST(TText, go_down)
{
  TText t;

  t.InsDownLine("sample_text");
  t.InsNextLine("sample_text");
  t.GoFirstLink();

  EXPECT_TRUE(t.GoDownLink());
  EXPECT_FALSE(t.GoDownLink());
}

TEST(TText, go_prev)
{
  TText t;

  t.InsNextLine("sample_text");
  t.InsNextLine("sample_text");
  t.GoNextLink();
  t.GoNextLink();

  EXPECT_TRUE(t.GoPrevLink());
  EXPECT_TRUE(t.GoPrevLink());
  EXPECT_FALSE(t.GoPrevLink());
}

TEST(TText, set_line)
{
  TText t;
  const char *str_ = "fgrgji34ij";

  t.SetLine(str_);

  EXPECT_EQ(std::string(str_), t.GetLine());
}

TEST(TText, get_line)
{
  TText t;

  t.Read(txt);
  t.Reset();
  t.GoDownLink();

  EXPECT_EQ(std::string("Header2"), t.GetLine());
}

TEST(TText, del_down_line_throw)
{
  TText t;

  t.Read(txt);
  t.Reset();

  EXPECT_ANY_THROW(t.DelDownLine());
}

TEST(TText, del_next_line_throw)
{
  TText t;

  t.Read(txt2);
  t.Reset();

  EXPECT_ANY_THROW(t.DelNextLine());
}

TEST(TText, del_down_section_no_throw)
{
  TText t;

  t.Read(txt);
  t.Reset();

  EXPECT_NO_THROW(t.DelDownSection());
}

TEST(TText, del_next_section_no_throw)
{
  TText t;

  t.Read(txt2);
  t.Reset();

  EXPECT_NO_THROW(t.DelNextSection());
}

TEST(TText, read_throw)
{
  TText t;

  EXPECT_ANY_THROW(t.Read("2c4242v4/dsadwd"));
}

TEST(TText, ins_down_line_no_throw)
{
  TText t;

  t.Read(txt);
  t.Reset();
  t.GoNext();
  t.GoNext();

  EXPECT_NO_THROW(t.InsDownLine(std::string("sample_text")));
}

TEST(TText, ins_down_line)
{
  TText t;
  const char *str_ = "2d9djnf32r";

  t.Read(txt);
  t.Reset();
  t.GoNext();
  t.GoNext();
  t.InsDownLine(str_);
  t.GoDownLink();

  EXPECT_EQ(std::string(str_), t.GetLine());
}

TEST(TText, ins_next_line_no_throw)
{
  TText t;

  t.Read(txt);
  t.Reset();
  t.GoNext();
  t.GoNext();

  EXPECT_NO_THROW(t.InsNextLine(std::string("sample_text")));
}

TEST(TText, ins_next_line)
{
  TText t;
  const char *str_ = "2d9djnf32r";

  t.Read(txt);
  t.Reset();
  t.GoNext();
  t.GoNext();
  t.InsNextLine(str_);
  t.GoNextLink();

  EXPECT_EQ(std::string(str_), t.GetLine());
}

TEST(TText, ins_down_section_no_throw)
{
  TText t;
  const char *str_ = "34r89fjw94f";

  t.Read(txt);
  t.Reset();

  EXPECT_NO_THROW(t.InsDownSection(std::string(str_)));
}

TEST(TText, ins_down_section)
{
  TText t;
  const char *str_ = "2qe9qe9d";

  t.Read(txt);
  t.Reset();
  t.InsDownSection(str_);
  t.GoDownLink();

  EXPECT_EQ(std::string(str_), t.GetLine());
  t.GoDownLink();
  EXPECT_EQ(std::string("Header2"), t.GetLine());
}

TEST(TText, ins_next_section_no_throw)
{
  TText t;
  const char *str_ = "hg87d87h8";

  t.Read(txt2);
  t.Reset();

  EXPECT_NO_THROW(t.InsNextSection(std::string(str_)));
}

TEST(TText, ins_next_section)
{
  TText t;
  const char *str_ = "83dj93wdf";

  t.Read(txt2);
  t.Reset();
  t.InsNextSection(str_);
  t.GoNextLink();

  EXPECT_EQ(std::string(str_), t.GetLine());
  t.GoDownLink();
  EXPECT_EQ(std::string("Header2"), t.GetLine());
}

