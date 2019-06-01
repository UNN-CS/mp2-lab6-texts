#include <gtest.h>
#include <iostream>
#include "ttext.h"
#include "ttextlink.h"

using namespace std;

TEST(TText, can_set_line)
{
	TTextLink::InitMemSystem();
	TText t;
	ASSERT_NO_THROW(t.SetLine("8"));
}

TEST(TText, can_delete_down_line)
{
	TTextLink::InitMemSystem();
	TText t;
	t.InsDownLine("than");
	ASSERT_NO_THROW(t.DelDownLine());
}

TEST(TText, can_go_next)
{
	TTextLink::InitMemSystem();
	TText t;
	t.SetLine("1");
	t.InsDownLine("2");
	t.InsNextLine("3");
	t.Reset();
    cout<<t.GetLine();
	t.GoNext();
	cout<<t.GetLine();
	t.GoNext();
	cout<<t.GetLine();
	t.GoNext();
	cout<<t.GetLine();
}