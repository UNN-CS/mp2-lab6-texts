#include "ttextviewer.hpp"

void TTextViewer::Insertion(PTText pText)
{
    char input;
    do
    {
        cout << "1.SetLine\n2.InsDownLine\n3.InsDownSection\n";
        cout << "4.InsNextLine\n5.InsNextSection\nESC.Exit\n";
        cin >> input;
        system("clear");
    } while (input != ESC && input > 5 && input <= 0);
    string str;
    switch (input)
    {
    case '1':
        cout << "input line:" << endl;
        cin >> str;
        pText->SetLine(str.c_str());
        break;
    case '2':
        cout << "input line:" << endl;
        cin >> str;
        pText->InsDownLine(str);
        break;
    case '3':
        cout << "input line:" << endl;
        cin >> str;
        pText->InsDownSection(str);
        break;
    case '4':
        cout << "input line:" << endl;
        cin >> str;
        pText->InsNextLine(str);
        break;
    case '5':
        cout << "input line:" << endl;
        cin >> str;
        pText->InsNextSection(str);
        break;
    }
}
void TTextViewer::Navigation(PTText pText)
{
    char input;
    do
    {
        cout << "1.GoFirstLink\n2.GoDownLink\n3.GoNextLink\n";
        cout << "4.GoPrevLink\nESC.Exit\n";
        cin >> input;
        system("clear");
    } while (input != ESC && input > 5 && input <= 0);
    string str;
    switch (input)
    {
    case '1':
        pText->GoFirstLink();
        break;
    case '2':
        pText->GoDownLink();
        break;
    case '3':
        pText->GoNextLink();
        break;
    case '4':
        pText->GoPrevLink();
        break;
    }
}
void TTextViewer::Deleting(PTText pText)
{
    char input;
    do
    {
        cout << "1.DelDownLine\n2.DelDownSection\n3.DelNextLine\n";
        cout << "4.DelNextSection\nESC.Exit\n";
        cin >> input;
        system("clear");
    } while (input != ESC && input > 5 && input <= 0);
    string str;
    switch (input)
    {
    case '1':
        pText->DelDownLine();
        break;
    case '2':
        pText->DelDownSection();
        break;
    case '3':
        pText->DelNextLine();
        break;
    case '4':
        pText->DelNextSection();
        break;
    }
}

void TTextViewer::StartInterface(PTText pText)
{
    char input;
    while (input != ESC)
    {
        cout << "hello it's interface manager" << endl;
        cout << "0.Print" << endl;
        cout << "1.Insertion" << endl;
        cout << "2.Navigation" << endl;
        cout << "3.Deleting" << endl;
        cout << "4.WriteToFile" << endl;
        cout << "5.ReadFromFile" << endl;
        cout << "ESC.Exit" << endl;
        cin >> input;
        system("clear");
        if ((input - '0') == 0)
            pText->Print();
        else if ((input - '0') == 1)
            Insertion(pText);

        else if ((input - '0') == 2)
            Navigation(pText);

        else if ((input - '0') == 3)
        {
            Deleting(pText);
        }
        else if ((input - '0') == 4)
        {
            pText->Write((char *)"output.txt");
        }
        else if ((input - '0') == 5)
        {
            pText->Read((char *)"file.txt");
        }
    }
}
