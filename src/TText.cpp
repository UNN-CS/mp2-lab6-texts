#include "TText.h"

PTTextLink TText::GetFirstAtom(PTTextLink pl)
{
	PTTextLink t = pl;
	while (!t->IsAtom())
		t->GetDown();
	return t;
}

void TText::PrintText(PTTextLink ptl)
{
	if (ptl == NULL)
		SetRetCode(DataErr);
	else
	{
		pCurrent = ptl;
		while (!IsTextEnded())
		{
			std::cout << pCurrent->Str<<std::endl;
			GoNext();
		}
		Reset();
		SetRetCode(DataOK);
	}
}

PTTextLink TText::ReadText(std::ifstream &TxtFile)
{
	char s[TextLineLength] = "";
	PTTextLink t;
	while (TxtFile.eof() == 0)
	{
		TxtFile.getline(s, TextLineLength, '\n');
		if (s[0] == '{')
		{
			InsNextLine("{");
			t = pCurrent;
			TxtFile.getline(s, TextLineLength, '\n');
			InsDownLine(s);
		}
		else if (s[0] == '}')
		{
			InsNextLine("}");
			if (TxtFile.eof() == 0 && s[0] != '}')
			{
				TxtFile.getline(s, TextLineLength, '\n');
				pCurrent = t;
				InsNextLine(s);
			}
		}
		else
			InsNextLine(s);
	}
	return pFirst;
}

TText::TText(PTTextLink pl):pFirst(pl),pCurrent(pFirst) {}

TText::~TText()
{
	pFirst = pCurrent = NULL;
}

PTText TText::GetCopy()
{
	if (pFirst == NULL)
		return NULL;
	else
	{
		Reset();
		PTTextLink pf = new TTextLink(pCurrent->Str);
		PTText ptt = new TText(pf);

		for (;!IsTextEnded();GoNext(),ptt->GoNext())
		{
			if (pCurrent->pDown != NULL)
				ptt->pCurrent->pDown = new TTextLink(pCurrent->pDown->Str);
			if (pCurrent->pNext != NULL)
				ptt->pCurrent->pNext = new TTextLink(pCurrent->pNext->Str);
		}
		SetRetCode(DataOK);
		ptt->SetRetCode(DataOK);
		return ptt;
	}
}

int TText::GoFirstLink()
{
	while (!Path.empty())
		Path.pop();

	pCurrent = pFirst;
	if (pCurrent == NULL)
		SetRetCode(DataErr);
	else
		SetRetCode(DataOK);
	return RetCode;
}

int TText::GoDownLink()
{
	if (!pCurrent)
		SetRetCode(DataErr);
	else if (pCurrent->GetDown() != NULL)
	{
		Path.push(pCurrent);
		pCurrent = pCurrent->GetDown();
		SetRetCode(DataOK);
	}
	else
		SetRetCode(DataErr);
	return RetCode;
}

int TText::GoNextLink()
{
	if (!pCurrent)
		SetRetCode(DataErr);
	else if (pCurrent->GetNext() != NULL)
	{
		Path.push(pCurrent);
		pCurrent = pCurrent->GetNext();
		SetRetCode(DataOK);
	}
	else
		SetRetCode(DataErr);
	return RetCode;
}

int TText::GoPrevLink()
{
	if (pCurrent == NULL)
		SetRetCode(DataErr);
	else if (Path.empty())
		SetRetCode(DataErr);
	else
	{
		pCurrent = Path.top();
		Path.pop();
		SetRetCode(DataOK);
	}
	return RetCode;
}

std::string TText::GetLine()
{
	if (pCurrent == NULL)
	{
		SetRetCode(DataErr);
		return "";
	}
	else
		return std::string(pCurrent->Str);	
}

void TText::SetLine(std::string s)
{
	if (pCurrent == NULL)
		SetRetCode(DataErr);
	else
		strncpy(pCurrent->Str, s.c_str(), TextLineLength);
}

void TText::InsDownLine(std::string s)
{
	if (pCurrent == NULL)
		SetRetCode(DataErr);
	else
	{
		PTTextLink t = new TTextLink;
		strncpy(t->Str, s.c_str(), TextLineLength);
		t->pNext = pCurrent->GetDown();
		pCurrent->pDown = t;
		GoDownLink();
		SetRetCode(DataOK);
	}
}

void TText::InsDownSection(std::string s)
{
	if (pCurrent == NULL)
		SetRetCode(DataErr);
	else
	{
		PTTextLink t = new TTextLink;
		strncpy(t->Str, s.c_str(), TextLineLength);
		t->pDown = pCurrent->GetDown();
		pCurrent->pDown = t;
		GoDownLink();
		SetRetCode(DataOK);
	}
}

void TText::InsNextLine(std::string s)
{
	if (pCurrent == NULL)
		SetRetCode(DataErr);
	else
	{
		PTTextLink t = new TTextLink;
		strncpy(t->Str, s.c_str(), TextLineLength);
		t->pNext = pCurrent->GetNext();
		pCurrent->pNext = t;
		GoNextLink();
		SetRetCode(DataOK);
	}
}

void TText::InsNextSection(std::string s)
{
	if (pCurrent == NULL)
		SetRetCode(DataErr);
	else
	{
		PTTextLink t = new TTextLink;
		strncpy(t->Str,s.c_str(), TextLineLength);
		t->pDown = pCurrent->GetNext();
		pCurrent->pNext = t;
		GoNextLink();
		SetRetCode(DataOK);
	}
}

void TText::DelDownLine()
{
	if (pCurrent == NULL)
		SetRetCode(DataErr);
	else if (pCurrent->pDown != NULL)
	{
		PTTextLink t1 = pCurrent->pDown;
		if (t1->pDown == NULL)
			pCurrent->pDown = t1->pNext;
		else
			SetRetCode(DataErr);
		delete t1;
	}
	else
		SetRetCode(DataErr);
}

void TText::DelDownSection()
{
	if (pCurrent == NULL)
		SetRetCode(DataErr);
	else if (pCurrent->pDown != NULL)
	{
		PTTextLink t = pCurrent->pDown->pNext;
		pCurrent->pDown = t;
	}
	else
		SetRetCode(DataErr);
}

void TText::DelNextLine()
{
	if (pCurrent == NULL)
		SetRetCode(DataErr);
	else if (pCurrent->pNext != NULL)
	{
		if (pCurrent->pNext->pDown == NULL)
		{
			PTTextLink t = pCurrent->pNext;
			pCurrent->pNext = t->pNext;
			SetRetCode(DataOK);
		}
		else
			SetRetCode(DataErr);
	}
	else
		SetRetCode(DataErr);
}

void TText::DelNextSection()
{
	if (pCurrent == NULL)
		SetRetCode(DataErr);
	else if (pCurrent->pNext != NULL)
	{
		if (pCurrent->pNext->pDown != NULL)
		{
			PTTextLink t = pCurrent->pNext;
			pCurrent = t->pNext;
			SetRetCode(DataOK);
		}
		else
			SetRetCode(DataErr);
	}
	else
		SetRetCode(DataErr);
}

int TText::Reset()
{
	while (!St.empty())
		St.pop();
	pCurrent = pFirst;
	return RetCode;
}

bool TText::IsTextEnded() const
{
	return St.empty() && (pCurrent == NULL);
}

int TText::GoNext()
{
	if (pCurrent == NULL)
		SetRetCode(DataErr);
	else
	{
		if (pCurrent->pDown != NULL)
		{
			if (pCurrent->pNext != NULL)
				St.push(pCurrent->pNext);
			pCurrent = pCurrent->pDown;
		}
		else if(pCurrent->pNext != NULL)
			pCurrent = pCurrent->pNext;
		else
		{
			if (IsTextEnded())
			{
				SetRetCode(DataErr);
				return -1;
			}
			else
			{
				if (!St.empty())
				{
					pCurrent = St.top();
					St.pop();
				}
				else
				{
					pCurrent = NULL;
					SetRetCode(DataErr);
				}
			}
		}
	}
	return RetCode;
}

void TText::Print()
{
	PrintText(pFirst);
}

void TText::Read(char *pFileName)
{
	std::ifstream TxtFile;
	TxtFile.open(pFileName);
	if (!TxtFile)
		SetRetCode(DataErr);
	else
	{
		pFirst = ReadText(TxtFile);
		SetRetCode(DataOK);
	}
}

void TText::Write(char *pFileName)
{
	std::ofstream TxtFile;
	TxtFile.open(pFileName);
	if (!TxtFile)
		SetRetCode(DataErr);
	else
	{
		Reset();
		if (pCurrent == NULL)
			SetRetCode(DataErr);
		else
		{
			while (!IsTextEnded())
			{
				TxtFile << pCurrent->Str << std::endl;
				GoNext();
			}
			if (pCurrent != NULL)
				TxtFile << pCurrent->Str << std::endl;
			SetRetCode(DataOK);
		}
		Reset();
	}
}
