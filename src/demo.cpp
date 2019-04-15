#include "TText.h"

int main()
{
	cout << "Input text: " << endl;
	TTextLink::InitMemSystem(200);
	TText text;
	text.Read("C:\Users\lumpofsugar\Desktop\lab6\mp2-lab6-texts\files\input.txt");
	text.Print();

	PTText copy = text.GetCopy();
	
	text.GoFirstLink();                // Session 1
	text.GoDownLink();                 // Session 1.1
	text.GoDownLink();                 // Session 1.1.1
	text.GoDownLink();                 // Session 1.1.1.1

	text.DelNextLine();                // del Session 1.1.1.2

	text.GoFirstLink();                 // Session 1
	text.GoNextLink();                  // Session 2
	text.DelDownSection();              // del Session 2.1, 2.2, 2.2.1, 2.3

	text.InsNextLine("Session 3.1.1");  // new Session 3.1.1
	text.InsNextSection("Session 3");   // new Session 3

	text.GoFirstLink();                  // Session 1
	text.GoNextLink();                   // Session 2
	text.GoNextLink();                   // Session 3
	text.InsDownSection("Session 3.1");  // new Session 3.1

	cout << endl << endl << "New Text: " << endl;
	text.Print();
	text.Write("output.txt");
	cout << endl << "Copied input text: " << endl;
	copy->Print();
}