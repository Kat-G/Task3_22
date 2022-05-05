#pragma once
#include "TDataCom.h"
#include "TDataValue.h"
#include <iostream>
#define TabOK 0
#define TabEmpty -101
#define TabFull -102
#define TabNoRecord -103
#define TabRecDbl -104
#define TabNoMem -105
typedef std::string TKey;

class TTable : public TDataCom
{
protected:
	int DataCount; // количество записей в таблице
	int Efficiency;  // показатель эффективности выполнения операции
public:
	TTable() {
		DataCount = 0;
		Efficiency = 0;
		
	}
	virtual ~TTable() {}
	int GetDataCount() {
		return DataCount;
	}
	int GetEfficiency() {
		return Efficiency;
	}
	bool IsEmpty() const {
		return DataCount == 0;
	}
	virtual bool IsFull() const = 0;
	virtual PTDataValue FindRecord(TKey key) = 0;
	virtual void InsRecord(TKey k, PTDataValue pVal) = 0;
	virtual int DelRecord(TKey k) = 0;
	virtual bool Reset() = 0;
	virtual bool GoNext() = 0;
	virtual bool IsTabEnded() const = 0;
	virtual TKey GetKey() const = 0;
	virtual PTDataValue GetValue() const = 0;
	friend std::ostream &operator<<(std::ostream& os, TTable& tab) {
		for (tab.Reset(); !tab.IsTabEnded(); tab.GoNext())
		{
			os << "Key: " << tab.GetKey() << " Val: " << tab.GetValue()->ToString() << std::endl;
		}
		return os;
	}
};