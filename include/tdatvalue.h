#ifndef __TDATVALUE_H__
#define __TDATVALUE_H__

#define MemSize 20
#define TextLineLength 20

class TDatValue;
typedef TDatValue *PTDatValue;

class TDatValue {
  public:
    virtual PTDatValue GetCopy() = 0; // создание копии
	~TDatValue() {}
}; 

class TTextLink;
typedef TTextLink *PTTextLink;
typedef char TStr[TextLineLength];
class TText;
typedef TText *PTText;

#endif //__TDATVALUE_H__
