#include <gtest/gtest.h>
#include "include/ttext.h"

const char *txt = "../test/text1.txt";

TEST(TText, create)
{
  EXPECT_NO_THROW(TText t);
}

TEST(TText, read_from_file)
{
  TText t;

  EXPECT_NO_THROW(t.Read(txt));
}

TEST(TText, print)
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



