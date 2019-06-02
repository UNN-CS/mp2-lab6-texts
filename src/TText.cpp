#include "TText.h"
void TText::goNextLink() {
	if (!pCurr->getPNext()) return;
	stack.push(pCurr);
	pCurr = pCurr->getPNext();
}
void TText::goPrevLink() {
	if (stack.isEmpty()) return;
	pCurr = stack.pop();
}
void TText::goDownLink() {
	if (!pCurr->getPDown()) return;
	stack.push(pCurr);
	pCurr = pCurr->getPDown();
}
void TText::addNextLine(char *s) {
	TLink *tmp = new TLink(s, pCurr->getPNext(), nullptr);
	pCurr->setPNext(tmp);
	pCurr = pCurr->getPNext();
}
void TText::addNextSection(char *s) {
	TLink *tmp= new TLink(s, nullptr,nullptr);
	if (pCurr->getPDown()!=NULL) {
		TLink *tmp1 = pCurr->getPDown();
		pCurr->setPDown(tmp);
		pCurr = pCurr->getPDown();
		pCurr->setPNext(tmp1);
		return;
	}
	pCurr->setPDown(tmp);
	//pCurr->setPNext()
	pCurr = pCurr->getPDown();
}
void TText::delNextLink() { 
	delete pCurr->getPNext();
	pCurr->setPNext(NULL);
   // goPrevLink();
	/*
	if (pCurr) 
		if (pCurr->getPNext()) {
			if (pCurr->getPNext()->getPDown()) {
				delstack.push(pCurr);
				goNextLink();
				delDownLink();
				pCurr = delstack.pop();
			}
			if (pCurr->getPNext()->getPNext()) {
				TLink *tmp = pCurr->getPNext()->getPNext();
				delstack.push(pCurr);
				goNextLink();
				delete pCurr;
				pCurr = delstack.pop();
				pCurr->setPNext(tmp);
			}
			else { delstack.push(pCurr); goNextLink();  delete pCurr; pCurr = delstack.pop(); pCurr->setPNext(nullptr); }
		}
		//else { delete pCurr; goPrevLink(); pCurr->setPNext(nullptr); } */
}
void TText::delDownLink() {
	delete pCurr->getPDown();
	pCurr->setPDown(NULL);
	/*
	if (pCurr)
		if (pCurr->getPDown()) {
			delstack.push(pCurr);
			goDownLink();
			for (; pCurr->getPNext(); ) {
				delNextLink();
			}
			//goPrevLink();
			pCurr = delstack.pop();
			delete pCurr->getPDown();
			
		}
			*/
}
char* TText::getLine() {
	return pCurr->getStr();
}

void TText::setLine(char* tmp) {
	strcpy(pCurr->getStr(), tmp);
}

TLink* TText::recursionRead(ifstream& file) {
	char buf[80];
	TLink *tmp, *firstTmp = NULL;
	while (!file.eof()) {
		file.getline(buf, 80, '\n');
		if (buf[0] == '}')
			break;
		else {
			if (buf[0] == '{')
				tmp->setPDown(recursionRead(file));
			else {
				if (!firstTmp) {
					firstTmp = new TLink(buf);
					tmp = firstTmp;
				}
				else {
					tmp->setPNext( new TLink(buf));
					tmp = tmp->getPNext();
				}
			}
		}
	}
	return firstTmp;
}

void TText::Read(char *fn) {
	ifstream ifs(fn);
	pFirst = recursionRead(ifs);
}


void TText::printText(TLink* tmp) {
	if (tmp) {
		for (int i = 0; i < level; i++)
			cout << " ";
		cout << tmp->getStr() << endl;
		level++;
		printText(tmp->getPDown());
		level--;
		printText(tmp->getPNext());
	}
}


void TText::print() {
	level = 0;
	printText(pFirst);
}


void TText::saveText(TLink* tmp, ofstream& f) {
	f << tmp->getStr() << endl;
	if (tmp->getPDown()) {
		f << "{\n";
		saveText(tmp->getPDown(), f);
		f << "}\n";
	}
	if (tmp->getPNext())
		saveText(tmp->getPNext(), f);
}


void TText::save(char* fn) {
	ofstream ofs(fn);
	saveText(pFirst, ofs);
}



TLink* TText::CopyRecursion(TLink *tmp) {
	TLink *pN = NULL, *pD = NULL;
	if (tmp->getPDown())
		pD = CopyRecursion(tmp->getPDown());
	if (tmp->getPNext())
		pN = CopyRecursion(tmp->getPNext());
	TLink *unit = new TLink(tmp->getStr(), pN, pD);
	return unit;
}

TLink* TText::Copy() {
	return CopyRecursion(pFirst);
}


void TText::Reset() {
	pCurr = pFirst;
	stack.clear();
	stack.push(pCurr);
	if (pFirst->getPDown())
		stack.push(pFirst->getPDown());
	if (pFirst->getPNext())
		stack.push(pFirst->getPNext());
}


bool TText::IsEnd() {
	return stack.isEmpty();
}

void TText::GoNext() {
	pCurr = stack.pop();
	if (pCurr != pFirst) {
		if (pCurr->getPDown())
			stack.push(pCurr->getPDown());
		if (pCurr->getPNext())
			stack.push(pCurr->getPNext());
	}
}
int TText::DownCount() {
	if (!pCurr->getPDown()) return 1;
	TLink *tmp = pCurr;
	int k=0;
	stack.clear();
	stack.push(pCurr = pCurr->getPDown());
	for (; !IsEnd(); GoNext())
		k++;
	pCurr = tmp;
	return k+1;
}