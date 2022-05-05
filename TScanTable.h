#pragma once
#include "TArrayTable.h"

class TScanTable :public TArrayTable {
public:
	TScanTable(int size = 25):TArrayTable(size) { }
	virtual PTDataValue FindRecord(TKey k) {
		SetRetCode(TabOK);
		int i;
		for (i = 0; i < DataCount; i++) {
			if (pRecs[i]->Key == k)
				break;
		}
		Efficiency = i + 1;
		if (i < DataCount)
		{
			CurPos = i;
			return pRecs[i]->pValue;
		}
		SetRetCode(TabNoRecord);
		return nullptr;
	}
	virtual void InsRecord(TKey k, PTDataValue pVal)
	{
		if (IsFull())
		{
			SetRetCode(TabFull);
			return;
		}
		else
		{
			SetRetCode(TabOK);
		}
		CurPos++;
		pRecs[CurPos] = new TTabRecord(k, pVal);
		DataCount++;
	}
	//найти элемент, который нужно удалить(findrecord) и переместить последний
	//элемент переместить на место удал€емого, очистить пам€ть от старого элемента
	virtual void DelRecord(TKey k) {
		if (FindRecord(k) != nullptr) {
			int i;
			for (i = 0; i < DataCount; i++) {
				if (pRecs[i]->Key == k)
					break;
			}
			pRecs[i]->Key = pRecs[DataCount]->Key;
			pRecs[i]->pValue = pRecs[DataCount]->pValue;
			delete pRecs[DataCount];
			DataCount--;
			SetRetCode(TabOK);
		}
	}
};