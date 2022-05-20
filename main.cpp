#include "TScanTable.h"
#include "TBookValue.h"
#include "TSortTable.h"
#include "SVParser.h"
//������� "����������". ���� - �������� �����, ������ - �����, ����
int main() {
	setlocale(LC_ALL, "Russian");
	TSortTable* table = new TSortTable();
	CSVParser parser("Books.csv");

	PTBookValue book = new TBookValue("����� �����", "��������");
	table->InsRecord("������ �����", book);
	
	parser.ParseAndInsert(table);

	//std::cout << *table << std::endl;

	//table->DelRecord("������� �����");

	std::cout << *table << std::endl;

	delete table;
}