#include "TText.h"
#include "TLink.h"
#include<Windows.h>
#include <iostream>
using namespace std;
TMem TLink::mem;
bool KEY[256];
int GetKEY()
{
	int i = 0;
	while (i < 256)
	{
		if (GetAsyncKeyState(i))
			return i;
		i++;
	}
}
void clrscr(void)
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!Console) return;

	CONSOLE_SCREEN_BUFFER_INFO buf;
	GetConsoleScreenBufferInfo(Console, &buf);

	DWORD Count;

	COORD zpos;
	zpos.X = 0;
	zpos.Y = 0;

	FillConsoleOutputCharacter(Console, ' ', buf.dwSize.X * buf.dwSize.Y, zpos, &Count);
	SetConsoleCursorPosition(Console, zpos);
}

void clreol(void)
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!Console)return;

	CONSOLE_SCREEN_BUFFER_INFO buf;
	GetConsoleScreenBufferInfo(Console, &buf);

	WORD Attr;
	DWORD Count;

	COORD zpos = buf.dwCursorPosition;

	zpos.X = buf.dwCursorPosition.X + 1;
	zpos.Y = buf.dwCursorPosition.Y;

	FillConsoleOutputCharacter(Console, ' ', buf.dwSize.X - buf.dwCursorPosition.X - 1, zpos, &Count);
	SetConsoleCursorPosition(Console, buf.dwCursorPosition);
}

void gotoxy(int x, int y)
{
	HANDLE Console = GetStdHandle(STD_OUTPUT_HANDLE);
	if (!Console)return;

	COORD pos;
	pos.X = x;
	pos.Y = y;

	SetConsoleCursorPosition(Console, pos);
}
int main()
{
	TLink::InitMem(100);
	setlocale(LC_CTYPE, "Russian");
	bool flag = false;
	TText txt;
	FILE *f;
	int p;
	int down = 0;
	int level = 0;
	TStack<int> ShortDown(100);
	TStack<int> ShortRight(100);
	TStack<TLink*> prev;
	f = fopen("text.txt", "r");
	txt.Read("text.txt");
	txt.print();
	txt.Reset();
	gotoxy(0, 0);
	ShortDown.clear();
	while (1)
	{
		
		switch(GetKEY()) {
		case 37:
			if (!ShortRight.isEmpty()) {
				level--;
				down = ShortRight.pop();
				gotoxy(level, down);
				txt.setpCurr(prev.pop());
				txt.goPrevLink();
			}
			break;
		case 38:
			if (!ShortDown.isEmpty() && !txt.isDownLevel()) {
				down = down -ShortDown.pop();
				gotoxy(level, down);
				txt.goPrevLink();
			}
			break;
		case 39:
			if (txt.HavePDown()) {
				ShortRight.push(down);
				prev.push(txt.getCurr());
				txt.goDownLink();
				level++;
				down++;
				gotoxy(level, down);
			}
			break;
		case 40:
			if (txt.HaveNext()) {
				down += txt.DownCount();
				ShortDown.push(txt.DownCount());
				txt.goNextLink();
				gotoxy(level, down);
			}
			break;
		case 27: flag = true; break;
		case 13:
			txt.addNextSection("aaaaa");
			clrscr();
			txt.print();
			gotoxy(0, 0);
			txt.Reset();
			ShortDown.clear();
			ShortRight.clear();
			down = 0;
			level=0;
			break;

		case 32:
			txt.addNextLine("AAAAA");
			clrscr();
			txt.print();
			gotoxy(0, 0);
			txt.Reset();
			ShortDown.clear();
			ShortRight.clear();
			down = 0;
			level = 0;
			break;
		case 46:
			txt.delNextLink();
			clrscr();
			txt.print();
			gotoxy(0, 0);
			txt.Reset();
			ShortDown.clear();
			ShortRight.clear();
			down = 0;
			level = 0;
			break;
		case 8:
			txt.delDownLink();
			clrscr();
			txt.print();
			gotoxy(0, 0);
			txt.Reset();
			ShortDown.clear();
			ShortRight.clear();
			down = 0;
			level = 0;
			break;
		}
		Sleep(300);
		if (flag) break;
	}

	//txt.save("text.txt");
	fclose(f);
	clrscr();
	TLink::printFree();
	TLink::MemClean(txt);
	cout << endl;
	TLink::printFree();
	return 0;
}