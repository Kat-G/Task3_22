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
			pR = pMem[i];
			for (j = i - 1; j > -1; j--) {
				if (pMem[j]->Key > pR->Key) {
					pMem[j + 1] = pMem[j];
					Efficiency++;
				}
				else
					break;
			}
			pMem[j + 1] = pR;
		}
	}
	void MergeSort(PTTabRecord* pMem, int DataCount) {
		PTTabRecord* pData = pMem;
		PTTabRecord* pBuf = new PTTabRecord[DataCount];
		PTTabRecord* pTemp = pBuf;
		MergeSorter(pData, pBuf, DataCount);
		delete pTemp;
	}
	void QuickSort(PTTabRecord* pMem, int DataCount) {
		
		int pivot = DataCount / 2;
		QuickSplit(pMem, DataCount, pivot);
		/*if (j > 0) {
			QuickSort(pMem, j + 1);
		}
		if (i < DataCount) {
			QuickSort(&pMem[i], DataCount - i);
		}*/
	}

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
	void MergeData(PTTabRecord*& pData, PTTabRecord*& pBuf, int n1, int n2) {
		int i = 0, i1 = 0, i2 = 0;
		PTTabRecord* pData1 = pData;
		PTTabRecord* pData2 = pData + n1;
		while (i1 < n1 && i2 < n2) {
			if (pData1[i1]->Key < pData2[i2]->Key) {
				pBuf[i++] = pData1[i1++];
			}
			else {
				pBuf[i++] = pData2[i2++];
			}
		}
		while (i1<n1)
		{
			pBuf[i++] = pData1[i1++];
		}
		while (i2 < n2)
		{
			pBuf[i++] = pData2[i2++];
		}
		pData = pBuf;
		pBuf = pData1;
		Efficiency += n1 + n2;
	}
	void QuickSplit(PTTabRecord* pData, int Size, int& pivot) {
		int i = 0, j = DataCount - 1;
		do {
			while (pData[i] < pData[pivot]) {
				i++;
			}
			while (pData[j] > pData[pivot]) {
				j--;
			}

			if (i <= j) {
				PTTabRecord tmp = pData[i];
				pData[i] = pData[j];
				pData[j] = tmp;

				i++;
				j--;
			}
		} while (i <= j);
	}
public:
	TSortTable(int Size = 20) :TScanTable(Size) { };
	TSortTable(const TScanTable& tab) {
		*this = tab;
	}
	TSortTable(const TSortTable& tab) {
		*this = tab;
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
		if (i2 < DataCount && pRecs[i2]->Key == key) {
			SetRetCode(TabOK);
			return pRecs[i2]->pValue;
		}
		SetRetCode(TabNoRecord);
		return nullptr;
	}
	virtual void InsRecord(TKey key,PTDataValue pValue) override {
		if (IsFull())
			SetRetCode(TabFull);
		else {
			PTDataValue temp = FindRecord(key);
			if (temp != nullptr)
				SetRetCode(TabRecDbl);
			else {
				for (int i = DataCount; i > CurPos; i--) {
					pRecs[i] = pRecs[i - 1];
				}
				pRecs[CurPos] = new TTabRecord(key, pValue);
				DataCount++;
				SetRetCode(TabOK);
			}
		}
	}
	virtual int DelRecord(TKey key) override {
		PTDataValue temp = FindRecord(key);
		if (temp == nullptr) {
			SetRetCode(TabNoRecord);
		}
		else {
			for (int i = CurPos; i < DataCount - 1; i++) {
				pRecs[i] = pRecs[i + 1];
			}
			pRecs[--DataCount] = nullptr;
			SetRetCode(TabOK);
		}
		return GetRetCode();
	}
};