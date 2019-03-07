#ifndef __DATVALUE_H__
#define __DATVALUE_H__

class TDatValue;
typedef TDatValue *PTDatValue;

class TDatValue
{
public:
  virtual PTDatValue GetCopy() const = 0;
  virtual ~TDatValue(){}
};

#endif

