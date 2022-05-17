#include "TScanTable.h"
#include "TBookValue.h"

//������� "����������". ���� - �������� �����, ������ - �����, ����
int main() {
	setlocale(LC_ALL, "Russian");
	TScanTable* table = new TScanTable();

	PTBookValue book = new TBookValue("����� �����", "��������");
	table->InsRecord("������ �����", book);
	
	table->Parse();

	std::cout << *table << std::endl;

	table->DelRecord("������� �����");

	std::cout << *table << std::endl;
}