#include <iostream>
#include "Graph.h"

//S Z 16
//S D 13
//Z D 10
//D Z 4
//Z K 12
//K D 9
//D P 14
//P K 7
//P T 4
//K T 20

int main()
{
	try {
		setlocale(LC_ALL, "rus");
		cout << "Добрый день!\n";
		cout << "Курсовая работа по теме `Проталкивание предпотоков`\n";
		cout << "Работу выполнила Новикова Анастасия, гр.7302\n";
		cout << endl;
		Graph g;

		
		g.read("Read.txt");
		g.print();
		std::cout << "Максимальный поток= " << g.getMaxFlow('S') << std::endl;
		cout << endl;
		cout << "Спасибо за внимание!\n";
	}
	catch (std::exception e)
	{
		cout << e.what();
	}
	return 0;
}