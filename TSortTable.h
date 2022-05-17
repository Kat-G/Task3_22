#pragma once
#include "TScanTable.h"
enum TSortMethod{Insert,Merge,Quick};

class TSortTable:public TScanTable {
protected:
	TSortMethod SortMethod;
	void SortData() {
		Efficiency = 0;
		switch (SortMethod)
		{
		case Insert:
			InsertSort(pRecs, DataCount);
			break;
		case Merge:
			MergeSort(pRecs, DataCount);
			break;
		case Quick:
			QuickSort(pRecs, DataCount);
			break;
		}
	}
	void InsertSort(PTTabRecord* pMem, int DataCount) {
		PTTabRecord pR;
		for (int i = 1, j; i < DataCount; i++) {
			pR = pRecs[i];
			for (j = i - 1; j > -1; j--) {
				if (pRecs[j]->Key > pR->Key) {
					pRecs[j + 1] = pRecs[j];
					Efficiency++;
				}
				else
					break;
			}
			pRecs[j + 1] = pR;
		}
	}
	void MergeSort(PTTabRecord* pMem, int DataCount) {
		PTTabRecord* pData = pMem;
		PTTabRecord* pBuf = new PTTabRecord[DataCount];
		PTTabRecord* pTemp = pBuf;
		MergeSorter(pData, pBuf, DataCount);
		delete pTemp;
	}
	void QuickSort(PTTabRecord* pMem, int DataCount);

	void MergeSorter(PTTabRecord*& pData, PTTabRecord*& pBuf, int Size) { //запуск разделения
		int n1 = (Size + 1) / 2;
		int n2 = Size - n1;
		if (Size > 2) {
			PTTabRecord* pDat2 = pData + n1;
			PTTabRecord* pBuf2 = pBuf + n1;
			MergeSorter(pData, pBuf, n1);
			MergeSorter(pDat2, pBuf2, n2);
		}
		MergeData(pData, pBuf, n1, n2);
	}
	void MergeData(PTTabRecord*& pData, PTTabRecord*& pBuf, int n1,int n2);
	void QuickSplit(PTTabRecord* pData, int Size, int& pivot);
public:
	TSortTable(int Size = 20) :TScanTable(Size) {};
	TSortTable(const TScanTable& tab) {
		*this = tab;
		SortData();
	}
	TSortTable& operator=(const TScanTable& tab) {
		if (this == &tab)
			return *this;
		if (pRecs != nullptr)
		{
			for (int i = 0; i < DataCount; i++) {
				delete pRecs[i];
			}
			delete[] pRecs;
			pRecs = nullptr;
		}
		TabSize = tab.GetTabSize();
		DataCount = tab.DataCount;  //
		pRecs = new PTTabRecord[TabSize];
		for (int i = 0; i < DataCount; i++) {
			pRecs[i] = (PTTabRecord)tab.pRecs[i]->GetCopy();
		}
		SortData();
		CurPos = 0;
		return *this;
	}
	TSortMethod GetSortMethod(){
		return SortMethod;
	}
	void SetSortMethod(TSortMethod sm) {
		SortMethod = sm;
	}
	virtual PTDataValue FindRecord(TKey key) override {
		int i = 0, i1 = 0, i2 = DataCount - 1;
		Efficiency = 0;
		while (i1 <= i2)
		{
			Efficiency++;
			i = (i1 + i2) / 2;
			if (pRecs[i]->Key == key) {
				i1 = i + 1;
				i2 = i;
				break;
			}
			if (pRecs[i]->Key > key) {
				i2 = i - 1;
			}
			else {
				i1 = i + 1;
			}
		}
		if (i2 < 0 || (pRecs[i2]->Key) < key) {
			i2++;
		}
		CurPos = i2;
		if (pRecs[i2]->Key == key && i2 < DataCount) {
			SetRetCode(TabOK);
			return pRecs[i2]->pValue;
		}
		SetRetCode(TabNoRecord);
		return nullptr;
	}
	virtual void InsRecord(TKey key,PTDataValue pValue) override {
		
	}
	virtual int DelRecord(TKey key) override {}
};