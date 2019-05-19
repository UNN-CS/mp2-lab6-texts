#define BufLength 80

#include <fstream>
#include "TText.h"

static char StrBuf[BufLength+1]; // ����� ��� ����� �����
static int  TextLevel;           // ����� �������� ������ ������


 PTTextLink TText :: GetFirstAtom (PTTextLink pl) { // ����� ������� �����
	PTTextLink tmp = pl;
	while (!tmp -> IsAtom()) {
		St.push(tmp); 
		tmp = tmp -> GetDown();
	}
	return tmp;
 }

 void TText :: PrintText (PTTextLink ptl){        // ������ ������ �� ����� ptl
	if (ptl != NULL) {
		for ( int i = 0; i < TextLevel; i++ ) 
			std::cout << "  ";
		std::cout << " " << *ptl << std::endl;
		TextLevel++; 
		PrintText(ptl->GetDown());
		TextLevel--; 
		PrintText(ptl->GetNext());
  }
 }

 PTTextLink TText :: ReadText (std::ifstream &TxtFile) { //������ ������ �� �����
	PTTextLink pHead, ptl;
	pHead = ptl = new TTextLink();
	while (TxtFile.eof() == 0) { //���� �� ����� �����
		TxtFile.getline (StrBuf, BufLength, '\n');
		if ( StrBuf[0] == '}' ) { 
			TextLevel--; 
			break; 
		}
		else if ( StrBuf[0] == '{' ) { // ��������, ���� �� �������� �����
			TextLevel++; 
			ptl->pDown = ReadText(TxtFile);
		}
		else {  // ������������� ��������� ������
			ptl -> pNext = new TTextLink(StrBuf, NULL, NULL);
			ptl = ptl -> pNext;
		}
	}
	ptl = pHead;
	if ( pHead -> pDown == NULL ) { // �������� ������ ������, ���� ��� ���������
		pHead = pHead -> pNext; 
		delete ptl;
	}
	return pHead;
 }

 TText :: TText (PTTextLink pl) {
	if ( pl == NULL ) 
		pl = new TTextLink();
	pFirst = pCurrent = pl;
 }

 PTText TText :: getCopy() {
	PTTextLink pl1, pl2, pl = pFirst, cpl = NULL;
	if ( pFirst != NULL ) {
		while ( !St.empty() ) 
			St.pop(); // ������� �����
		while (1) {
		if ( pl != NULL ) {  // ������� � ������� �����
			pl = GetFirstAtom(pl); 
			St.push(pl);
			pl = pl->GetDown();
		}
		else if ( St.empty() ) break;
		else {
			pl1 = St.top(); 
			St.pop();
			if ( strstr(pl1->Str,"Copy") == NULL ) { // ������ ���� �������� �����
			// �������� ����� - pDown �� ��� ������������� ����������
				pl2 = new TTextLink("Copy", pl1, cpl);   // pNext �� ��������
				St.push(pl2);
				pl1 = pl1 -> pNext;
				cpl = nullptr;
			}
        else { // ������ ���� �������� �����
			pl2 = pl1->GetNext();
			strcpy(pl1->Str, pl2->Str);
			pl1->pNext = cpl;
			cpl = pl1;
		}
		}
		}
	}
	return new TText(cpl);
 }


// ���������


 int TText :: GoFirstLink (void) { // ������� � ������ ������
	while ( !Path.empty() ) Path.pop(); // ������� �����
	pCurrent = pFirst;
	if ( pCurrent == NULL ) SetRetCode(TextError); 
	else SetRetCode(TextOK);
	return RetCode;
 }

 int TText :: GoDownLink (void) {  // ������� � ��������� ������ �� Down
	SetRetCode(TextError);
	if ( pCurrent != NULL )
		if ( pCurrent->pDown != NULL ) {
			Path.push(pCurrent);
			pCurrent = pCurrent->pDown;
			SetRetCode(TextOK);
		}
	return RetCode;
 }

 int TText :: GoNextLink (void) {  // ������� � ��������� ������ �� Next
	SetRetCode(TextError);
	if ( pCurrent != NULL )
		if ( pCurrent -> pNext != NULL ) {
			Path.push(pCurrent);
			pCurrent = pCurrent -> pNext;
			SetRetCode(TextOK);
		}
	return RetCode;
 }


 int TText :: GoPrevLink (void) {  // ������� � ���������� ������� � ������
	if ( Path.empty() ) SetRetCode(TextNoPrev);
	else {
		pCurrent = Path.top(); Path.pop();
		SetRetCode(TextOK);
	}
	return RetCode;
 }


// ������


 std::string TText :: GetLine(void) {   // ������ ������� ������
	if ( pCurrent == NULL ) return std::string("");
	else return std::string(pCurrent->Str);
 }

 void TText :: SetLine ( std::string s){ // ������ ������� ������ 
	if ( pCurrent == NULL ) SetRetCode(TextError);
	else strncpy(pCurrent->Str,s.c_str(),TextLineLength);
	pCurrent->Str[TextLineLength-1] = '\0';
 }


// �����������


 int TText :: InsDownLine (std::string s) {    // ������� ������ � ����������
	if ( pCurrent == NULL ) SetRetCode(TextError);
	else {
		PTTextLink pd = pCurrent -> pDown;
		PTTextLink pl = new TTextLink("",pd,NULL);
		strncpy(pl -> Str, s.c_str(), TextLineLength);
		pl -> Str[TextLineLength - 1] = '\0'; // ���������, ���� s ������� Str
		pCurrent -> pDown = pl;             // ��������� ��������� �� ����� ������
		SetRetCode(TextOK);
	}
	return RetCode;
 }

 int TText :: InsDownSection (std::string s) { // ������� ������� � ����������
	if ( pCurrent == NULL ) SetRetCode(TextError);
	else {
		PTTextLink pd = pCurrent -> pDown;
		PTTextLink pl = new TTextLink("", NULL, pd);
		strncpy(pl -> Str, s.c_str(), TextLineLength);
		pl -> Str[TextLineLength - 1] = '\0'; // ���������, ���� s ������� Str
		pCurrent -> pDown = pl;             // ��������� ��������� �� ����� ������
		SetRetCode(TextOK);
	}
	return RetCode;
 }

 int TText :: InsNextLine (std::string s) {    // ������� ������ � ��� �� ������
	if ( pCurrent == NULL ) 
		 SetRetCode(TextError);
	else {
		PTTextLink pn = pCurrent -> pNext;
		PTTextLink pl = new TTextLink("", pn, NULL);
		strncpy(pl -> Str, s.c_str(), TextLineLength);
		pl -> Str[TextLineLength - 1] = '\0'; // ���������, ���� s ������� Str
		pCurrent -> pNext = pl;             // ��������� ��������� �� ����� ������
		SetRetCode(TextOK);
	}
	return RetCode;
 }

 int TText :: InsNextSection (std::string s){  // ������� ������� � ��� �� ������
	if ( pCurrent == NULL ) SetRetCode(TextError);
	else {
		PTTextLink pn = pCurrent -> pNext;
		PTTextLink pl = new TTextLink("", NULL, pn);
		strncpy(pl -> Str, s.c_str(), TextLineLength);
		pl -> Str[TextLineLength - 1] = '\0'; // ���������, ���� s ������� Str
		pCurrent -> pNext = pl;             // ��������� ��������� �� ����� ������
		SetRetCode(TextOK);
	}
	return RetCode;
 }

 int TText :: DelDownLine (void){        // �������� ������ � ���������
	SetRetCode(TextOK);
	if ( pCurrent == NULL ) SetRetCode(TextError);
	else if ( pCurrent->pDown != NULL ) {
		PTTextLink pl1 = pCurrent->pDown;
		PTTextLink pl2 = pl1->pNext;
		if ( pl1->pDown == NULL ) pCurrent->pDown = pl2; // ������ ��� �����
	}
	return RetCode;
 }

 int TText :: DelDownSection (void){     // �������� ������� � ���������
	SetRetCode(TextOK);
	if ( pCurrent == NULL ) SetRetCode(TextError);
	else if ( pCurrent -> pDown != NULL ) {
		PTTextLink pl1  = pCurrent -> pDown;
		PTTextLink pl2  = pl1 -> pNext;
		//delete pl1;
		pCurrent->pDown = pl2;
  }
	return RetCode;
 }

 int TText :: DelNextLine (void) {        // �������� ������ � ��� �� ������
	SetRetCode(TextOK);
	if ( pCurrent == NULL ) SetRetCode(TextError);
	else if ( pCurrent -> pNext != NULL ) {
		PTTextLink pl1  = pCurrent -> pNext;
		PTTextLink pl2  = pl1 -> pNext;
		//delete pl1;
		pCurrent -> pNext = pl2;
  }
	return RetCode;
 }

 int TText :: DelNextSection (void) {     // �������� ������� � ��� �� ������
	SetRetCode(TextOK);
	if ( pCurrent == NULL ) SetRetCode(TextError);
	else if ( pCurrent -> pNext != NULL ) {
		PTTextLink pl1  = pCurrent -> pNext;
		PTTextLink pl2  = pl1 -> pNext;
		//delete pl1;
		pCurrent -> pNext = pl2;
	}
	return RetCode;
 }


// ��������


 int TText :: Reset (void) {              // ���������� �� ������ �������
	while ( !St.empty() ) St.pop(); // ������� �����
  // ������� ������ � ����� �� ��������
  // ���������� - ������ ������ ������, ������� �� ��� �����
	pCurrent = pFirst;
	if ( pCurrent != NULL ) {
		St.push(pCurrent);
		if ( pCurrent->pNext != NULL ) 
			St.push(pCurrent->pNext);
		if ( pCurrent->pDown != NULL ) 
			St.push(pCurrent->pDown);
	}
	return IsTextEnded();
 }

 int TText :: IsTextEnded (void) const {  // ����� ��������?
	 return !St.size();
 }

 int TText :: GoNext (void) {             // ������� � ��������� ������
	if ( !IsTextEnded() ) {
		pCurrent = St.top(); St.pop(); // ���� ����� ������� ���� ����, ������
    if ( pCurrent != pFirst ) {    // ������ ������ ������ ��� ���� ����������
		if ( pCurrent->pNext != NULL ) St.push(pCurrent->pNext);
		if ( pCurrent->pDown != NULL ) St.push(pCurrent->pDown);
		}
	}
	return IsTextEnded();
 }


//������ � �������


 void TText :: Read (char * pFileName) {  // ���� ������ �� �����
	std::ifstream TxtFile(pFileName);
	TextLevel = 0;
	if ( TxtFile != NULL ) pFirst = ReadText(TxtFile);
 }
 void TText :: Write (char * pFileName) { // ����� ������ � ����
	 std::ifstream TxtFile(pFileName);
	 PrintText(pFirst);
 }


//������


 void TText :: Print (void) {             // ������ ������
	TextLevel = 0;
	PrintText(pFirst);
 }


