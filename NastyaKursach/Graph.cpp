#pragma once

#include "Graph.h"
#include <algorithm>
#include <string>
#include <fstream>
#include <sstream>

void Graph::preflow(int s) //initialize the graph
{
	ver.at(s)->h = ver.get_size();

	auto iterator = edge.create_list_iterator();
	while (iterator->has_next())
	{
		auto cur_edge = iterator->next();
		if (cur_edge->u == s)
		{
			// Поток приравниваем к ёмкости
			cur_edge->flow = cur_edge->capacity;

			// Инициализируйте избыточный поток для соседнего v
			ver.at(cur_edge->v)->e_flow += cur_edge->flow;

			// Добавить ребро из v в s в остаточном графе с емкостью равной 0
			edge.push_back(new Edge(-cur_edge->flow, 0, cur_edge->v, s));
		}
	}
}

void Graph::updateReverseEdgeFlow(Edge*& cur_edge, int flow) //creating a reverse edge
{
	int u = cur_edge->v;
	int v = cur_edge->u;

	auto iterator = edge.create_list_iterator();
	while (iterator->has_next())
	{
		auto rev_edge = iterator->next();
		if (rev_edge->v == v && rev_edge->u == u)
		{
			rev_edge->flow -= flow;
			return;
		}
	}
	// добавляем обращенное ребро в остаточный граф
	edge.push_back(new Edge(0, flow, u, v));
}

bool is_u_int(const std::string s)//проверка веса на число
{
	return s.find_first_not_of("0123456789") == std::string::npos;
}

void  Graph::read(std::string path) 
{
	std::ifstream file(path.c_str());
	std::string str;
	int flag = 0; string flag1;
	if (file.is_open())
	{
		while (std::getline(file, str))
		{ 
			std::string from, to, weight, trash;
			std::istringstream iss(str);
			iss >> from >> to >> weight >> trash;
			if (from.size() > 1 || from.empty() || to.size() > 1 || to.empty() || !is_u_int(weight) || weight.empty() || !trash.empty()||(from!="S" && flag==0))
				throw std::invalid_argument("Wrong input data in file.");
			this->add_edge(from.at(0), to.at(0), stoi(weight));
			flag++; 
			flag1 = to;
		}
		if (this->edge.get_size() <= 0)
		{
			throw std::invalid_argument("File is empty.");
		}
		if (flag1!="T") throw std::invalid_argument("Wrong input data in file.");

		
	}
	else
	{
		throw std::exception("No file found.");
	}
}

void Graph::add_edge(char u, char v, size_t capacity)
{
	Map_of_vertex.insert(u, Map_of_vertex.get_size());
	Map_of_vertex.insert(v, Map_of_vertex.get_size());
	edge.push_back(new Edge(0, capacity, Map_of_vertex.find(u), Map_of_vertex.find(v)));
}

int Graph::ifAnyOverFlowVertex() //returns the index of the full vertex
{
	auto iterator = ver.create_list_iterator();
	int i = 1;
	iterator->next();
	while (iterator->has_next() && i < ver.get_size() - 1)
	{
		if (iterator->next()->e_flow > 0)
		{
			return i;
		}
		i++;
	}
	return -1;
}

bool Graph::push(int u)// Pushes the flow from the overflowing vertex u
{
	
	auto iterator = edge.create_list_iterator();
	while (iterator->has_next())
	{
		auto cur_edge = iterator->next();
		
		if (cur_edge->u == u)
		{
			// Если поток уже равен проходимости, он нас не интересует
			if (cur_edge->flow == cur_edge->capacity)
				continue;

			// Проталкивание возможено только если высота вершины для проталкивания меньше высоты переполняющейся вершины
			auto cur_vertex = ver.at(u);
			if (cur_vertex->h > ver.at(cur_edge->v)->h)
			{
				// Толкаемый поток равен наименьшему из : оставшийся поток на ребре и избыточный поток
				int flow = min(cur_edge->capacity - cur_edge->flow,
					cur_vertex->e_flow);

				// Уменьшите лишний поток для переполненной вершины (мы его протолкнули)
				cur_vertex->e_flow -= flow;

				// Увеличение потока на соседней вершине (куда протолкнули)
				ver.at(cur_edge->v)->e_flow += flow;

				// Добавить остаточный поток (с мощностью 0 и отрицательным потоком)
				cur_edge->flow += flow;

				updateReverseEdgeFlow(cur_edge, flow);

				return true;
			}
		}
	}
	return false;
}

void Graph::relabel(int u) // lift function
{
	// Инициализировать минимальную высоту соседнего для u
	int max_height = INT_MAX;

	// Поиск соседний с минимальной высотой
	auto iterator = edge.create_list_iterator();
	while (iterator->has_next())
	{
		auto cur_edge = iterator->next();
		if (cur_edge->u == u)
		{
			// если поток равен емкости, то перемаркировывать нечего
			if (cur_edge->flow == cur_edge->capacity)
				continue;

			// Обновить минимальную высоту
			auto cur_vertex = ver.at(cur_edge->v);
			if (cur_vertex->h < max_height)
			{
				max_height = cur_vertex->h;

				// Обновить высоту u
				ver.at(u)->h = max_height + 1;
			}
		}
	}
}

int Graph::getMaxFlow(char s)  //searching max flow
{
	int stock;
	//first letter in file?
	if (!Map_of_vertex.Find(s, stock))
	{
		throw std::invalid_argument("No vertex with this letter.");
	}
	this->EdgesN = edge.get_size(); //added number edges
	this->VertexN = Map_of_vertex.get_size(); //added number vertex
	for (int i = 0; i < this->VertexN; i++)  //create list of vertex
		ver.push_back(new Vertex(0, 0));

	preflow(stock); //initialize the input

	int u;
	while ((u = ifAnyOverFlowVertex()) != -1)
	{
		if (!push(u))
			relabel(u);
	}
	if (ver.get_back()->e_flow == 0)
		throw std::invalid_argument("Пути из истока в сток нет\n");
	else
	 return ver.get_back()->e_flow;
}

void Graph::print()
{
	cout << "Список вершин:";
	auto it = Map_of_vertex.create_btf_iterator();
	while (it->has_next())
	{
		cout << it->next()->key << ' ';
	}
	cout << "\n";
	cout << "   Их индексы:";
	auto it1 = Map_of_vertex.create_btf_iterator();
	while (it1->has_next())
	{
		cout << it1->next()->data << ' ';
	}
	cout << '\n';
	cout << endl;
	cout << "Граф примет вид:" << "\n";
	auto iterator = edge.create_list_iterator();
	while (iterator->has_next())
	{
		auto current = iterator->next();
		cout << "Ребро из " << current->u << " в " << current->v << " потокоемкость " << current->capacity << endl;
	}
}