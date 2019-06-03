#ifndef __DATVALUE_H
#define __DATVALUE_H

#include <iostream>

class TDatValue {
public:
	virtual TDatValue * GetCopy() = 0;
	~TDatValue() {}
};

typedef TDatValue *PTDatValue;

#endif
