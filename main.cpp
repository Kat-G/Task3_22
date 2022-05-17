#include "TScanTable.h"
#include "TBookValue.h"

//таблица "библиотека". Ключ - название книги, данные - автор, жанр
int main() {
	setlocale(LC_ALL, "Russian");
	TScanTable* table = new TScanTable();

	PTBookValue book = new TBookValue("Конан Дойль", "Детектив");
	table->InsRecord("Шерлок Холмс", book);
	
	table->Parse();

	std::cout << *table << std::endl;

	table->DelRecord("Призрак Оперы");

	std::cout << *table << std::endl;
}