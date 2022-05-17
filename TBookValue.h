#pragma once
#include"TDataValue.h"
#include <iostream>

class TBookValue;
typedef TBookValue* PTBookValue;

class TBookValue : public TDataValue {
private:
	std::string Author;
	std::string Genre;
public:
	TBookValue(std::string a, std::string g) :Author(a), Genre(g) {}
	virtual TDataValue* GetCopy() {
		return new TBookValue(Author, Genre);
	}
	virtual std::string ToString() {
		std::string s;
		s = "Автор: " + Author + " Жанр: " + Genre;
		return s;
	}
};