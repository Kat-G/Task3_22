#pragma once
#include <iostream>
#include "TDataValue.h"
typedef std::string TKey;
class TTabRecord;
typedef TTabRecord* PTTabRecord;

class TTabRecord :public TDataValue
{
protected:
	TKey Key;
	PTDataValue pValue;
	virtual void Print()
	{
		std::cout << Key << " " << pValue->ToString() << std::endl;
	}
public:
	TTabRecord(TKey key, PTDataValue val) {
		Key = key;
		pValue = val;
	}
	void SetKey(TKey key) {
		Key = key;
	}
	TKey GetKey() {
		return Key;
	}
	void SetValue(PTDataValue p) {
		pValue = p;
	}
	PTDataValue GetValue() {
		return pValue;
	}
	virtual TDataValue* GetCopy() {
		return new TTabRecord(Key, pValue);
	}
	TTabRecord& operator=(const TTabRecord& tr) {
		if (this == &tr)
			return *this;
		Key = tr.Key;
		pValue = tr.pValue->GetCopy();
	}
	virtual bool operator==(const TTabRecord& tr) const {
		return Key == tr.Key;
	}
	virtual bool operator>(const TTabRecord& tr) const {
		return Key > tr.Key;
	}
	virtual bool operator<(const TTabRecord& tr) const {
		return Key < tr.Key;
	}

	std::string ToString() override {

	}
	friend class TArrayTable;
	friend class TSortTable;
	friend class TTreeNote;
	friend class TTreeTable;
	friend class TScanTable;
	friend class TArrayHashTable;
	friend class TListHashTable;

};