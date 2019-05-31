#ifndef _TTEXT_H
#define _TTEXT_H

#include <stack>
#include <fstream>
#include <string>
#include "tdatacom.h"
#include"TTextLink.h"

#define TextOk 0           
#define TextNoDown 101     
#define TextNoNext 102      
#define TextNoPrev 103     
#define TextError -102      
#define TextNoMem -101      
#define TooLongString -103  
#define BufLength  80

class TText;

typedef TText* PTText;

class TText : public TDataCom
{
	
	protected:
		PTTextLink pFirst;       
		PTTextLink pCurrent;      
		stack< PTTextLink > Path; 
		stack< PTTextLink > St;  
		PTTextLink GetFirstAtom(PTTextLink pl); 
		void PrintText(PTTextLink ptl);         
		PTTextLink ReadText(ifstream &TxtFile);
		
	public:
		TText(PTTextLink pl = nullptr);
		~TText()
		{
			pFirst = nullptr;
		}
		PTText GetCopy();

		int GoFirstLink(void);
		int GoDownLink(void);  
		int GoNextLink(void); 
		int GoPrevLink(void); 

		string GetLine(void);   
		void SetLine(string s); 

		void InsDownLine(string s);  
		void InsDownSection(string s);
		void InsNextLine(string s);    
		void InsNextSection(string s); 
		void DelDownLine(void);        
		void DelDownSection(void);     
		void DelNextLine(void);        
		void DelNextSection(void);     


		int Reset(void);             
		int IsTextEnded() const { return !St.size(); }; 
		int GoNext(void);              

		
		void Read(char * pFileName);   
		void Write(char * pFileName);  

		void Print(void);              
};

#endif