#ifndef __DATVALUE_H
#define __DATVALUE_H

class TDatValue {
public:
	virtual TDatValue * GetCopy() = 0; // создание копии
	~TDatValue() {}
};
typedef TDatValue *PTDatValue;
#endif
