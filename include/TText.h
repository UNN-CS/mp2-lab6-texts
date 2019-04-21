#include <stack>
#include <fstream>
#include "TDataCom.h"
#include "TTextLink.h"

typedef TText* PTText;

class TText : public TDataCom
{
protected:
	PTTextLink pFirst, pCurrent;
	std::stack < PTTextLink > Path;
	std::stack < PTTextLink > St;
	PTTextLink GetFirstAtom(PTTextLink pl);
	void PrintText(PTTextLink ptl);
	PTTextLink ReadText(std::ifstream &TxtFile);

public:
	TText(PTTextLink pl = NULL);
	~TText();
	PTText GetCopy();

	int GoFirstLink();
	int GoDownLink();
	int GoNextLink();
	int GoPrevLink();
	
	std::string GetLine();
	void SetLine(std::string s);

	void InsDownLine(std::string s);
	void InsDownSection(std::string s);
	void InsNextLine(std::string s);
	void InsNextSection(std::string s);
	void DelDownLine();
	void DelDownSection();
	void DelNextLine();
	void DelNextSection();

	int Reset();
	bool IsTextEnded() const;
	int GoNext();

	void Read(char *pFileName);
	void Write(char *pFileName);

	void Print();
};
