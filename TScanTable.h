#pragma once
#include <fstream>
#include <vector>
#include "TArrayTable.h"
#include "TBookValue.h"

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
		Efficiency = 1;

		pRecs[DataCount++] = new TTabRecord(k, pVal);
	}
	//найти элемент, который нужно удалить(findrecord) и переместить последний
	//элемент переместить на место удал€емого, очистить пам€ть от старого элемента
	virtual int DelRecord(TKey k) {
		if (FindRecord(k) != nullptr) {
			int i;
			for (i = 0; i < DataCount; i++) {
				if (pRecs[i]->Key == k)
					break;
			}
			pRecs[i]->Key = pRecs[DataCount-1]->Key;
			pRecs[i]->pValue = pRecs[DataCount-1]->pValue;
			delete pRecs[DataCount-1];
			DataCount--;
			SetRetCode(TabOK);
			return TabOK;
		}
		else
			return TabNoRecord;
	}
	void Parse() {
		setlocale(LC_ALL, "rus");
		std::ifstream fin("Books.csv");
		std::string line, tmp;
		std::vector<std::string> b;
		int count = 0;
		if (fin.is_open())
		{
			while (getline(fin, line))
			{
				for (int i = 0; i < line.length(); i++) {
					if (line[i] != ';') {
						tmp += line[i];
					}
					else {
						b.push_back(tmp);
						tmp = "";
					}
				}
				b.push_back(tmp);
				tmp = "";
				PTBookValue book = new TBookValue(b[1], b[2]);
				InsRecord(b[0], book);
				b.clear();
			}
		}
	}
};