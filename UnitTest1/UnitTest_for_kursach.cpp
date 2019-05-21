#include "pch.h"
#include "CppUnitTest.h"
#include "../NastyaKursach/Graph.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(Overall_test_insert_literal)
		{
			Graph g;

			g.add_edge('0', '1', 16);
			g.add_edge('0', '2', 13);
			g.add_edge('1', '2', 10);
			g.add_edge('2', '1', 4);
			g.add_edge('1', '3', 12);
			g.add_edge('2', '4', 14);
			g.add_edge('3', '2', 9);
			g.add_edge('3', '5', 20);
			g.add_edge('4', '3', 7);
			g.add_edge('4', '5', 4);

			Assert::IsTrue(g.getMaxFlow('0') == 23);
		}

		TEST_METHOD(Overall_test_insert_num)
		{
			Graph g;

			g.add_edge('1', '2', 20);
			g.add_edge('1', '3', 10);
			g.add_edge('2', '3', 30);
			g.add_edge('2', '4', 10);
			g.add_edge('3', '4', 20);

			Assert::IsTrue(g.getMaxFlow('1') == 30);
		}

		TEST_METHOD(Overall_test_insert_no_path)
		{
			try {
				Graph g;

				g.add_edge('0', '1', 16);
				g.add_edge('0', '2', 13);
				g.add_edge('3', '2', 9);
				g.add_edge('3', '5', 20);
				g.add_edge('4', '3', 7);
				g.add_edge('4', '5', 4);
			}
			catch (std::exception e)
			{
				Assert::AreEqual(e.what(), "Пути из истока в сток нет\n");
			}
		}

		TEST_METHOD(Overall_test_insert_wrong_stock)
		{
			try
			{
				Graph g;

				g.add_edge('1', '2', 20);

				Assert::IsTrue(g.getMaxFlow('5') == 30);
			}
			catch (std::exception e)
			{
				Assert::AreEqual(e.what(), "No vertex with this letter.");
			}
		}

		TEST_METHOD(Overall_test_read_all_ok)
		{
			Graph g;
			g.read("C:\\Users\\Анастасия\\source\\repos\\NastyaKursach\\NastyaKursach\\Read.txt");

			Assert::IsTrue(g.getMaxFlow('S') == 23);
		}

		TEST_METHOD(Overall_test_read_empty)
		{
			try
			{
				Graph g;
				g.read("C:\\Users\\Анастасия\\source\\repos\\NastyaKursach\\NastyaKursach\\ReadEmpty.txt");
			}
			catch (std::exception e)
			{
				Assert::AreEqual(e.what(), "File is empty.");
			}
		}

		TEST_METHOD(Overall_test_read_wrong_data1)
		{
			try
			{
				Graph g;
				g.read("C:\\Users\\Анастасия\\source\\repos\\NastyaKursach\\NastyaKursach\\ReadWrongData1.txt");
			}
			catch (std::exception e)
			{
				Assert::AreEqual(e.what(), "Wrong input data in file.");
			}
		}

		TEST_METHOD(Overall_test_read_wrong_data2)
		{
			try
			{
				Graph g;
				g.read("C:\\Users\\Анастасия\\source\\repos\\NastyaKursach\\NastyaKursach\\ReadWrongData2.txt");
			}
			catch (std::exception e)
			{
				Assert::AreEqual(e.what(), "Wrong input data in file.");
			}
		}

		TEST_METHOD(Overall_test_read_wrong_data3)
		{
			try
			{
				Graph g;
				g.read("C:\\Users\\Анастасия\\source\\repos\\NastyaKursach\\NastyaKursach\\ReadWrongData3.txt");
			}
			catch (std::exception e)
			{
				Assert::AreEqual(e.what(), "Wrong input data in file.");
			}
		}

		TEST_METHOD(Overall_test_not_exist)
		{
			try
			{
				Graph g;
				g.read("NonExist.txt");
			}
			catch (std::exception e)
			{
				Assert::AreEqual(e.what(), "No file found.");
			}
		}
	};
}