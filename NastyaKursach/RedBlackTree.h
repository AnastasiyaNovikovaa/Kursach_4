#pragma once
#include <iostream>
#include "Iterator.h"
#include "List.h"

using namespace std;

template <typename T, typename T2 >
class Map
{
private:

	class node
	{
	public:
		node(T key, T2 data, node* left = nullptr, node* right = nullptr) {
			this->data = data;
			this->left = left;
			this->right = right;
			this->key = key;
			this->parent = nullptr;
			this->color = 'r';
		};
		char color;
		T key; T2 data;
		node* right;
		node* left;
		node* parent;
	};

	node* root;
	size_t size;

public:
	Map();
	~Map();

	class BtfIterator : public Iterator<node*>
	{
	public:
		BtfIterator(node* root)
		{
			current = root;
		};

	private:
		node* next() override;
		bool has_next() override
		{
			return (list.get_size() || current != nullptr);
		};
		List<node*> list;
		node* current;
	};

	Iterator<node*>* create_btf_iterator() const
	{
		if (this == nullptr && this->root == nullptr) throw std::exception("Dictionary does not exist");
		return new BtfIterator(this->root);
	};

private:
	void insertfix(node * t);      //supporting function for insert
	void leftrotate(node*);
	void rightrotate(node*);
	node* get_leaf(node*);       //supporting function for remove
	void add_first(node*);        //adding the first element to the tree
	void delfix(node*);           //supporting function for remove, balance
	node* node_find(node*, T);
public:
	void get_keys();
	void get_value();
	void clear();                 //clearing the tree
	void insert(T, T2);           //insert element in the tree
	void remove(T);               //removing element by key
	int get_size();               //getting size of the tree
	T2 find(T);                 //finding element by key
	bool Find(T key, T2 & value);
};