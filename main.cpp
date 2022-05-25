#include "TScanTable.h"
#include "TBookValue.h"
#include "TSortTable.h"
#include "SVParser.h"
//������� "����������". ���� - �������� �����, ������ - �����, ����
int main() {
	setlocale(LC_ALL, "Russian");
	TScanTable table(25);
	CSVParser parser("Books.csv");

	PTBookValue book = new TBookValue("����� �����", "��������");
	table.InsRecord("������ �����", book);

	parser.ParseAndInsert(&table);

	//std::cout << *table << std::endl;

	//table->DelRecord("������� �����");
	TSortTable table2(table);

	std::cout << table2 << std::endl<<table2.GetEfficiency();
}