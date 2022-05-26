#include "TScanTable.h"
#include "TBookValue.h"
#include "TSortTable.h"
#include "SVParser.h"
#include "TListHashTable.h"

//������� "����������". ���� - �������� �����, ������ - �����, ����
int main() {
	setlocale(LC_ALL, "Russian");
	TListHashTable table(25);
	CSVParser parser("Books.csv");

	PTBookValue book = new TBookValue("����� �����", "��������");
	table.InsRecord("������ �����", book);

	parser.ParseAndInsert(&table);


	std::cout << table << std::endl;
}