#ifndef __TDATVALUE__
#define __TDATVALUE__

class TDatValue;
typedef TDatValue* PTDatValue;

class TDatValue {
  public:
    virtual TDatValue * GetCopy() =0; // создание копии
   ~TDatValue() {}
};

#endif // __TDATVALUE__
