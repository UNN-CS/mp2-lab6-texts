#include <gtest/gtest.h>
#include "TTextViewer.h"

TEST(text, can_create_textEditor) {
	 //Arrange & Act & Assert
	EXPECT_NO_THROW(TextEditor test());
}

TEST(text, can_create_textEditor_whis_path) {
	// Arrange & Act & Assert
	EXPECT_NO_THROW(TextEditor test("text.den"));
}
TEST(text, can_create_matrix_with_positive_length)
{
	ASSERT_NO_THROW(list<int>* m = new list<int>());
}
TEST(text, can_add_elem_in_stack)
{
	list<int>* m = new list<int>();
	ASSERT_NO_THROW(m->push_back(5));
}
TEST(text, can_create_copy)
{
	list<int>* m = new list<int>();
	ASSERT_NO_THROW(list<int>* m1 = new list<int>(*m));
}
TEST(text, copy_is_equal_to_origin)
{
	list<int>* m = new list<int>();
	m->push_back(3);
	list<int>* m1 = new list<int>(*m);
	EXPECT_EQ(m->getElem(0).Val, m1->getElem(0).Val);
}
TEST(text, can_delete_last)
{
	list<int>* m = new list<int>();
	m->push_back(3);
	m->push_back(4);
	m->push_back(5);
	m->push_back(6);
	m->pop_back();
	EXPECT_NE(m->getElem(2).Val, 6);
}
TEST(text, correctness_of_the_extracted_element)
{
	list<int>* m = new list<int>();
	m->push_back(3);
	m->push_back(4);
	m->push_back(5);
	m->push_back(6);
	int m1 = m->getElem(3).Val;
	EXPECT_EQ(m1, 6);
}


TEST(text, attempt_to_retrieve_an_element_from_an_empt_list)
{
	list<int>* m = new list<int>();
	ASSERT_ANY_THROW(m->pop_back());
}
TEST(text, correctness_of_the_insert_element)
{
	list<int>* m = new list<int>();
	m->push_back(3);
	m->push_back(4);
	m->push_back(5);
	m->push_back(6);
	m->insert(10, 2);
	EXPECT_EQ(m->getElem(2).Val, 10);
}