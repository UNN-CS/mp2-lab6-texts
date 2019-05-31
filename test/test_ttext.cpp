#include <gtest.h>
#include <iostream>
#include <sstream>

#include "ttext.h"
#include "ttextlink.h"

TEST(TText, Can_Init_Memory)
{	
	// Act & Assert
	ASSERT_NO_THROW(TTextLink::InitMemSystem());
}

TEST(TText, Can_Clean_Memory)
{
	// Arrange
	TTextLink::InitMemSystem();
	TText text;

	// Act & Assert
	ASSERT_NO_THROW(TTextLink::MemCleaner(text));
}

TEST(TText, Can_Insert_To_Next_Line)
{
	// Arrange
	TTextLink::InitMemSystem();
	TText text;

	// Act & Assert
	ASSERT_NO_THROW(text.InsNextLine("Line"));
}

TEST(TText, Can_Insert_To_Down_Line)
{
	// Arrange
	TTextLink::InitMemSystem();
	TText text;

	// Act & Assert
	ASSERT_NO_THROW(text.InsDownLine("Line"));
}

TEST(TText, Can_Go_Next_Line)
{
	// Arrange
	TTextLink::InitMemSystem();
	TText text;

	// Act
	text.InsNextLine("Line");

	// Assert
	ASSERT_NO_THROW(text.GoNextLink());
	ASSERT_EQ(text.GetLine(), "Line");

}

TEST(TText, Can_Go_Down_Line)
{
	// Arrange
	TTextLink::InitMemSystem();
	TText text;

	// Act
	text.InsDownLine("Line");

	// Assert
	ASSERT_NO_THROW(text.GoDownLink());
	ASSERT_EQ(text.GetLine(), "Line");
}

TEST(TText, Can_Delete_Next_Line)
{
	// Arrange
	TTextLink::InitMemSystem();
	TText text;

	// Act
	text.InsNextLine("Line");

	// Assert
	ASSERT_NO_THROW(text.DelNextLine());
	ASSERT_ANY_THROW(text.GoNextLink());
}

TEST(TText, Can_Delete_Down_Line)
{
	// Arrange
	TTextLink::InitMemSystem();
	TText text;

	// Act
	text.InsDownLine("Line");

	// Assert
	ASSERT_NO_THROW(text.DelDownLine());
	ASSERT_ANY_THROW(text.GoDownLink());
}

TEST(TText, Can_Insert_To_Next_Section)
{
	// Arrange
	TTextLink::InitMemSystem();
	TText text;

	// Act & Assert
	ASSERT_NO_THROW(text.InsNextSection("Section"));
}

TEST(TText, Can_Insert_To_Down_Section)
{
	// Arrange
	TTextLink::InitMemSystem();
	TText text;

	// Act & Assert
	ASSERT_NO_THROW(text.InsDownSection("Section"));
}

TEST(TText, Can_Go_Next_Section)
{
	// Arrange
	TTextLink::InitMemSystem();
	TText text;

	// Act
	text.InsNextSection("Section");

	// Assert
	ASSERT_NO_THROW(text.GoNextLink());
	ASSERT_EQ(text.GetLine(), "Section");
}

TEST(TText, Can_Go_Down_Section)
{
	// Arrange
	TTextLink::InitMemSystem();
	TText text;

	// Act
	text.InsDownSection("Section");

	// Assert
	ASSERT_NO_THROW(text.GoDownLink());
	ASSERT_EQ(text.GetLine(), "Section");
}

TEST(TText, Can_Delete_Next_Section)
{
	// Arrange
	TTextLink::InitMemSystem();
	TText text;

	// Act
	text.InsNextSection("Section");

	// Assert
	ASSERT_NO_THROW(text.DelNextSection());
	ASSERT_ANY_THROW(text.GoNextLink());
}

TEST(TText, Can_Delete_Down_Section)
{
	// Arrange
	TTextLink::InitMemSystem();
	TText text;

	// Act
	text.InsDownSection("Section");

	// Assert
	ASSERT_NO_THROW(text.DelDownSection());
	ASSERT_ANY_THROW(text.GoDownLink());
}

TEST(TText, Can_Copy)
{
	// Arrange
	TTextLink::InitMemSystem();
	TText text1;
	PTText text2;

	// Act
	text1.InsNextLine("Line 1");
	text1.InsDownLine("Line 2");
	text1.GoNextLink();
	text1.InsDownSection("Section 1");
	text1.InsNextSection("Section 2");

	// Assert
	ASSERT_NO_THROW(text2 = text1.GetCopy());
	ASSERT_NE(&text1, text2);
}

TEST(TText, Copy_Is_Right)
{
	// Arrange
	TTextLink::InitMemSystem();
	TText text1;
	PTText text2;

	// Act
	text1.InsNextLine("Line 1");
	text1.InsDownLine("Line 2");
	text1.GoNextLink();
	text1.InsDownSection("Section 1");
	text1.InsNextSection("Section 2");

	text2 = text1.GetCopy();

	// Assert
	text2->GoFirstLink();
	text2->GoNextLink();
	ASSERT_EQ(text2->GetLine(), "Line 1");
	text2->GoDownLink();
	ASSERT_EQ(text2->GetLine(), "Section 1");
	text2->GoPrevLink();
	text2->GoNextLink();
	ASSERT_EQ(text2->GetLine(), "Section 2");
	text2->GoFirstLink();
	text2->GoDownLink();
	ASSERT_EQ(text2->GetLine(), "Line 2");
}

TEST(TText, Can_Set_Line)
{
	// Arrange
	TTextLink::InitMemSystem();
	TText text;

	// Act
	text.InsNextLine("Line 1");
	text.GoNextLink();

	// Assert
	ASSERT_NO_THROW(text.SetLine("Line 2"));
	ASSERT_EQ(text.GetLine(), "Line 2");
}
