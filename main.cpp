#include "TScanTable.h"
#include "TBookValue.h"
#include "TSortTable.h"
#include "CSVParser.h"
#include "TListHashTable.h"

//������� "����������". ���� - �������� �����, ������ - �����, ����
int main() {
	setlocale(LC_ALL, "Russian");
	TListHashTable tab(25);
	CSVParser parser("Books.csv");
	PTBookValue book = new TBookValue("����� �����", "��������");
	tab.InsRecord("������ �����", book);
	parser.ParseAndInsert(&tab);
	std::cout << tab << std::endl;

	tab.DelRecord("������ �����");
	std::cout << "�������� ������ '������ �����':" << std::endl << tab << std::endl;

	std::cout << "����� ������������� ����� '�������� � ��������� ���������': " << tab.FindRecord("�������� � ��������� ���������")->ToString() << std::endl;
}