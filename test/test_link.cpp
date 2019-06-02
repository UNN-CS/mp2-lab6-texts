#include "TText.h"

#include <gtest/gtest.h>

TEST(TLink, can_create_link)
{
  ASSERT_NO_THROW(TLink);

}
TEST(TLink, can_create_link_with_str)
{
	ASSERT_NO_THROW(TLink("qweq"));

}
TEST(TLink, can_get_pNext)
{
	TLink *tmp = new TLink();
	ASSERT_NO_THROW(tmp->getPNext());

}
TEST(TLink, can_get_pDown)
{
	TLink *tmp = new TLink();
	ASSERT_NO_THROW(tmp->getPDown());

}
TEST(TLink, can_set_pNext)
{
	TLink *tmp1 = new TLink();
	TLink *tmp2 = new TLink();
	ASSERT_NO_THROW(tmp1->setPNext(tmp2));

}
TEST(TLink, can_set_pDown)
{
	TLink *tmp1 = new TLink();
	TLink *tmp2 = new TLink();
	ASSERT_NO_THROW(tmp1->setPDown(tmp2));

}
