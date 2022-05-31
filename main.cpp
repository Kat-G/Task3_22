#include "TScanTable.h"
#include "TBookValue.h"
#include "TSortTable.h"
#include "CSVParser.h"
#include "TListHashTable.h"

//таблица "библиотека". Ключ - название книги, данные - автор, жанр
int main() {
	setlocale(LC_ALL, "Russian");
	TListHashTable tab(25);
	CSVParser parser("Books.csv");
	PTBookValue book = new TBookValue("Конан Дойль", "Детектив");
	tab.InsRecord("Шерлок Холмс", book);
	parser.ParseAndInsert(&tab);
	std::cout << tab << std::endl;

	tab.DelRecord("Шерлок Холмс");
	std::cout << "Удаление записи 'Шерлок Холмс':" << std::endl << tab << std::endl;

	std::cout << "Найти харатеристики книги 'Убийство в восточном экспрессе': " << tab.FindRecord("Убийство в восточном экспрессе")->ToString() << std::endl;
}