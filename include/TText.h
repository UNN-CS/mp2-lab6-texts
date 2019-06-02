#pragma once
#define _CRT_SECURE_NO_WARNINGS  
#include <fstream> 
#include "TLink.h"

class TText {
private:
	TLink *pFirst, *pCurr;
	int level;
	TStack<TLink*> stack, delstack;
public:
	TText(TLink *_pFirst=nullptr) {
		if (!_pFirst) _pFirst = new TLink();
		pCurr=pFirst = _pFirst;
	}
	void reset() { pCurr = pFirst; }
	void goNextLink();
	void goPrevLink();
	void goDownLink();
	void addNextLine(char *);
	void addNextSection(char *);
	void delNextLink();
	void delDownLink();
	char* getLine();
	void setLine(char* tmp);
	TLink* recursionRead(ifstream& file);
	void Read(char *fn);
	void printText(TLink* tmp);
	void print();
	void saveText(TLink* tmp, ofstream& f);
	void save(char* fn);
	TLink* CopyRecursion(TLink *tmp);
	TLink* Copy();
	void Reset();
	bool IsEnd();
	void GoNext();
	int DownCount();
	bool HaveNext() { return (pCurr->getPNext() != NULL); }
	bool HavePDown(){ return (pCurr->getPDown() != NULL); }
	TLink* getCurr() { return pCurr; }
	void setpCurr(TLink* _pCurr) { pCurr = _pCurr; }
	bool isDownLevel() { TLink *tmp = stack.pop(); stack.push(tmp); return (tmp->getPDown()==pCurr); }
};