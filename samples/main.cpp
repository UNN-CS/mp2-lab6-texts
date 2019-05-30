#include <iostream>

#include "TText.h"
#include "TTextLink.h"

using namespace std;

int main()
{
	TTextLink::InitMemSystem();
	TText t;
	t.SetLine("1");
	t.InsDownLine("2");
	t.InsNextLine("3");
	t.Print();
	cout << "--------------------"<< endl;
	PTText t2 = t.GetCopy();
	t2->Print();
	return 0;
}