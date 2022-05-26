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
		CurList = HashFunc(key) % TabSize;
		std::list<PTTabRecord>* lst = pList + CurList;
		lst->push_back(new TTabRecord(key, pValue));

	}
	virtual void DelRecord(TKey key) override {
		SetRetCode(TabOK);
		CurList = HashFunc(key) % TabSize;
		PTDataValue tmp=nullptr; 
		for (auto rec : pList[CurList]) {
			Efficiency++;
			if (rec->Key == key) {
				tmp = rec;
				break;
			}
		}
		if (tmp == nullptr) {
			SetRetCode(TabNoRecord);
			return;
		}
		pList[CurList].remove((PTTabRecord)tmp);
	}
	virtual TKey GetKey() const override {
		return (*startChain)->Key;
	}
	virtual PTDataValue GetValue() const override {
		return (*startChain)->pValue;
	}
	virtual bool Reset() override {
		CurList = 0;
		while (pList[CurList].size() == 0) {
			CurList++;
			if (IsTabEnded()) {
				return false;
			}
		}
		startChain = pList[CurList].begin();
		return !IsTabEnded();
	}
	virtual bool GoNext() override {
		if (++startChain != pList[CurList].end()){
			return !IsTabEnded();
		}
		while (pList[++CurList].size() == 0) {

			CurList++;
			if (IsTabEnded()) {
				return false;
			}
		}
		startChain = pList[CurList].begin();
		return !IsTabEnded();
	}
	virtual bool IsTabEnded() const override {
		return CurList >= TabSize;
	}
};