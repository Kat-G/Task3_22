#include "TScanTable.h"
#include "TBookValue.h"
#include "TSortTable.h"
#include "SVParser.h"
#include "TListHashTable.h"

//таблица "библиотека". Ключ - название книги, данные - автор, жанр
int main() {
	setlocale(LC_ALL, "Russian");
	TListHashTable table(25);
	CSVParser parser("Books.csv");

	PTBookValue book = new TBookValue("Конан Дойль", "Детектив");
	table.InsRecord("Шерлок Холмс", book);

	parser.ParseAndInsert(&table);


	std::cout << table << std::endl;
}