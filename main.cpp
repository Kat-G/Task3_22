#include "TScanTable.h"
#include "TBookValue.h"
#include "TSortTable.h"
#include "SVParser.h"
//таблица "библиотека". Ключ - название книги, данные - автор, жанр
int main() {
	setlocale(LC_ALL, "Russian");
	TSortTable* table = new TSortTable();
	CSVParser parser("Books.csv");

	PTBookValue book = new TBookValue("Конан Дойль", "Детектив");
	table->InsRecord("Шерлок Холмс", book);
	
	parser.ParseAndInsert(table);

	//std::cout << *table << std::endl;

	//table->DelRecord("Призрак Оперы");

	std::cout << *table << std::endl;

	delete table;
}