#pragma once
#include "List.cpp"
#include "RedBlackTree.cpp"

// Edge of graph
struct Edge
{
	int flow;
	int capacity;

	int u; // start vertex
	int v;  //final vertex

	Edge(int flow, int capacity, int u, int v)
	{
		this->flow = flow;
		this->capacity = capacity;
		this->u = u;
		this->v = v;
	}
	~Edge() = default;
};

// Vertex of graph
struct Vertex
{

	int h, e_flow;  //height and tank On vertex

	Vertex(int h, int e_flow)
	{
		this->h = h;
		this->e_flow = e_flow;
	}
	~Vertex() = default;
};

class Graph
{
	int VertexN; // number of vertex
	int EdgesN; // number of edges
	Map<char, int> Map_of_vertex; //map for vertex
	List<Vertex*> ver;
	List<Edge*> edge;

	bool push(int u); // push function

	void relabel(int u); //lift function

	void preflow(int s); //initialization function

	void updateReverseEdgeFlow(Edge*& cur_edge, int flow); // Flow reversal function

	int ifAnyOverFlowVertex(); //overflow check function
public:
	~Graph()
	{
		Map_of_vertex.clear();
		ver.clear();
		edge.clear();
	}
	Graph() {};
	void read(std::string path);
	void add_edge(char u, char v, size_t capacity);
	int getMaxFlow(char s);
	void print();
};
