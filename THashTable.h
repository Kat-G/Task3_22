#pragma once
#include "TTable.h"
class THashTable :public TTable {
public:
	THashTable():TTable(){ }
protected:
	virtual uint32_t HashFunc(const TKey key) {
		uint64_t hashValue = 0;
		int len = key.length();
		for (int i = 0; i < len; i++) {
			hashValue = (hashValue << 3) + key[i];
		}
		return hashValue;
	}
};