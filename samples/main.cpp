#include <iostream>

#include "ttext.h"
#include "ttextlink.h"

using namespace std;

int main()
{
	TTextLink::InitMemSystem();
	TText text;
	text.SetLine("Section 1");
	text.InsDownLine("Line 1.2");
	text.InsDownLine("Line 1.1");
	text.InsNextLine("Section 2");
	text.GoNextLink();
	text.InsDownLine("Line 2.1");
	text.GoDownLink();
	text.InsDownLine("Line 2.1.2");
	text.InsDownLine("Line 2.1.3");
	text.GoPrevLink();
	text.InsNextLine("Section 3");
	text.Print();
	cout << "--------------------"<< endl;
	PTText text2 = text.GetCopy();
	text2->Print();
	return 0;
}