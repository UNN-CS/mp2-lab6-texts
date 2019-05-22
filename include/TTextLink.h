#pragma once
#include"List.h"
struct Link
{
	list<Link> *data;
	short size;
	char type;
	char * str;
};
struct TString:Link
{
	
	TString() {

	}
	TString(int len)
	{
		str = new char[len];
		size = len;
		type = 's';
	}
};

struct TPage:Link
{
	//list<Link> *strings;
	TPage() {
		data = new list<Link>;
		size = 0;
		type = 'p';
	}
};

struct Text:Link
{
	//list<Link> *pages;
	Text() {
		data = new list<Link>;
		size = 0;
		type = 't';
	}
};
