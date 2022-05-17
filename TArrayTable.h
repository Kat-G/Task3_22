#pragma once
#include "TTabRecord.h"
#include "TTable.h"
#define TabMaxSize 25;
enum TDataPos{First_pos,Current_pos,Last_pos};
class TArrayTable : public TTable
{
protected:
	PTTabRecord* pRecs;
	int TabSize;// макс. возм.количество записей в таблице
	int CurPos;// номер текущей записи
public:
	TArrayTable(int size = 100) :TabSize(size) {
		pRecs = new PTTabRecord[TabSize];
		for (int i = 0; i < TabSize; i++)
		{
			pRecs[i] = nullptr;
		}
		CurPos = 0;
	}
	virtual ~TArrayTable() {
		for (int i = 0; i < DataCount; i++)
		{
			delete pRecs[i];
		}
		delete[] pRecs;
	}
	virtual bool IsFull() const {
		return DataCount >= TabSize;
	}
	int GetTabSize() const {
		return TabSize;
	}
	virtual TKey GetKey() const {
		return GetKey(Current_pos); 
	}
	virtual PTDataValue GetValue() const {
		return GetValuePtr(Current_pos); 
	}
	virtual TKey GetKey(TDataPos mode)const {
		int pos = -1;
		if (!IsEmpty()) {
			switch (mode)
			{
			case First_pos:
				pos = 0;
				break;
			case Last_pos:
				pos = DataCount - 1;
				break;
			default:
				pos = CurPos;
				break;
			}
		}
		return (pos == -1) ? std::string("") : pRecs[pos]->Key;
	}
	virtual PTDataValue GetValuePtr(TDataPos mode) const {
		int pos = -1;
		if (!IsEmpty()) {
			switch (mode)
			{
			case First_pos:
				pos = 0;
				break;
			case Last_pos:
				pos = DataCount - 1;
				break;
			default:
				pos = CurPos;
				break;
			}
		}
		return (pos == -1) ? nullptr : pRecs[pos]->pValue;
	}
	bool IsTabEnded() const {
		return CurPos >= DataCount;
	}
	bool Reset() {
		CurPos = 0;
		return IsTabEnded();
	}
	bool GoNext() {
		if (!IsTabEnded())
			CurPos++;
		return IsTabEnded();
	}
	int GetCurPos() const {
		return CurPos;
	}
	virtual bool SetCurPos(int pos) {
		CurPos = ((pos > -1) && (pos < DataCount)) ? pos : 0;
		return IsTabEnded();
	}
	friend class TSortTable;
};