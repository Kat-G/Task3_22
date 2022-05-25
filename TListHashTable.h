#pragma once
#include "THashTable.h"
#include "TTabRecord.h"
#include <list>
class TListHashTable : public THashTable {
protected:
	int TabSize;
	int CurList; //текущий индекс
	std::list<PTTabRecord>* pList;
	std::list<PTTabRecord>::iterator startChain;
public:
	TListHashTable(int size = 25) :THashTable() {
		pList = new std::list<PTTabRecord>[size];
		TabSize = size;
		CurList = 0;
		for (int i = 0; i < TabSize; i++) { //проверить
			pList[i] = std::list<PTTabRecord>();
		}
	}
	virtual ~TListHashTable() override {
		delete[] pList;
	}
	virtual bool IsFull() const override {
		return false;
	}
	virtual PTDataValue FindRecord(TKey key) override {
		PTDataValue tmp = nullptr;
		CurList = HashFunc(key) % TabSize;
		std::list<PTTabRecord>* lst = pList + CurList;
		for (auto rec : *lst) {
			Efficiency++;
			if (rec->Key == key) {
				tmp = rec->pValue;
				break;
			}
		}
		return tmp;
	}
	virtual void InsRecord(TKey key, PTDataValue pValue) override {

	}
	virtual void DelRecord(TKey key) override {

	}
	virtual TKey GetKey() const override {

	}
	virtual PTDataValue GetValue() const override {

	}
	virtual bool Reset() override {
		CurList = 0;
		startChain = pList->begin();
		return IsTabEnded();
	}
	virtual bool GoNext() override {
		if (startChain++ != pList[CurList].end()){
			return IsTabEnded();
		}
		if (IsTabEnded()) {
			return true;
		}
		CurList++;
		startChain = pList[CurList].begin();
		return IsTabEnded();
	}
	virtual bool IsTabEnded() const override {
		return CurList >= TabSize;
	}
};