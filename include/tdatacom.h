#pragma once

#define DataOK   0
#define DataErr -1

#define TextOK 0
#define TextNoDown 101
#define TextNoNext 102
#define TextNoPrev 103
#define TextError -102
#define TextNoMem -101


class TDataCom
{
protected:
	int RetCode; 
	int SetRetCode(int ret) { return RetCode = ret; };
public:
	TDataCom() : RetCode(DataOK) {}
	virtual ~TDataCom() {}
	int GetRetCode(){
		int temp = RetCode;
		RetCode = DataOK;
		return temp;
	}
};


