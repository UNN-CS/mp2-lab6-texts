#pragma once
#include"TTextLink.h"
struct Position
{
	short pos_in_text,
		pos_in_page,
		pos_in_string;
};
class TEXT
{
public:
	short max_page=4,
		max_string=5,
		max_sign=80;
	Text * text;
	char*name = "NO NAME";
	Position cursor = {0,0,0};
	Link* Buffer;
	Link* currentp;
	Link* currents;
//public:
	TEXT();
	TEXT(short mpage, short mstr, short msign);

	~TEXT();


	void setCurrent();
	bool GoNextString();
	bool GoNextPage();
	bool GoBackString();
	bool GoBackPage();
	bool GoToPos(Position pos);
	bool DeleteString();
	bool DeletePage();
	bool CutString();
	bool CutPage();
	bool ChangeString();
	bool ChangePage();
	bool CopyString();
	bool CopyPage();
	bool insert();
	bool insertStr(char * str);
	void CorrectCursor();


};
