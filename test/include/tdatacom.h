#pragma once

// ��������� ����� ����������
enum class Data { TextOk, TextError, TextNoMem, TextNoDown, TextNoNext, TextNoPrev };

// TDataCom �������� ����� ������� �������
class TDataCom
{
protected:
	Data RetCode; // ��� ����������
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
