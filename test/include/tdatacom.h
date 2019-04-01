#pragma once

// Обработка кодов завершения
enum class Data { TextOk, TextError, TextNoMem, TextNoDown, TextNoNext, TextNoPrev };

// TDataCom является общим базовым классом
class TDataCom
{
protected:
	Data RetCode; // Код завершения
	Data SetRetCode(const Data ret) { return RetCode = ret; }
public:
	TDataCom() : RetCode(Data::TextOk) {}
	Data GetRetCode()
	{
		Data temp = RetCode;
		RetCode = Data::TextOk;
		return temp;
	}
};
