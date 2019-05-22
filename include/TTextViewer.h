#pragma once
#include"TText.h"
#include<iostream>
#include<fstream>
class TextEditor
{
	char* PATH;
	TEXT* data;
public:
	TextEditor(char * path);
	bool LoadText();
	//bool Add(char type);
	bool PrintAllText();
	bool PrintCurPage();
	bool PrintCurString();
	bool Copy(char type);
	bool Delete(char type);
	bool Cut(char type);
	bool Insert();
	bool Change(char type);
	bool Goto(short p, short S, short s);
	bool InsertBack();
	bool SaveText();
	bool SaveText(char * path);


private:

};