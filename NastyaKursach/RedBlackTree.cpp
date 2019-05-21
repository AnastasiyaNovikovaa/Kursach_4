#pragma once
#include "RedBlackTree.h"
#include <stdexcept>

template <typename T, typename T2 >
Map<T, T2>::Map()
{
	size = 0;
}

template <typename T, typename T2 >
Map<T, T2>::~Map()
{
	clear();
}

template <typename T, typename T2>
typename Map<T, T2>::node* Map<T, T2>::BtfIterator::next()
{
	while (current != nullptr) {
		list.push_front(current);
		current = current->left;
	}
	current = list.at(0);
	list.pop_front();
	auto temp = current;
	current = current->right;
	return temp;
}

template <typename T, typename T2 >
void Map<T, T2> ::add_first(node* current)                    //добавление элемента в пустой список
{
	root = current;
	root->parent = nullptr;
}

template <typename T, typename T2 >
void Map<T, T2>::remove(T key)
{
	if (this->root == nullptr)                                //если список пуст
	{
		throw out_of_range("SOS! Dangerous! Error");
	}

	node* current;
	current = root;
	node* parent_of_leaf = NULL;
	node* leaf = NULL;
	int flag = 0;                                             // переменная-флаг, принимает значение 1, если элемент для удаления найден
	while (current != NULL && flag == 0)                      //цикл для нахождения нужного элемента
	{
		if (current->key == key)
			flag = 1;
		if (flag == 0)
		{
			if (current->key < key)
				current = current->right;
			else
				current = current->left;
		}
	}
	if (flag == 0)                                            //если элемент не найден
	{
		throw out_of_range("Not found");
	}
	else
	{
		if (current->left == nullptr || current->right == nullptr)  //если у элемента нет правого или левого потомка
			parent_of_leaf = current;
		else
			parent_of_leaf = get_leaf(current);
		if (parent_of_leaf->left != nullptr)
			leaf = parent_of_leaf->left;
		else
		{
			if (parent_of_leaf->right != nullptr)
				leaf = parent_of_leaf->right;
			else
				leaf = nullptr;
		}
		if (leaf != nullptr)
			leaf->parent = parent_of_leaf->parent;
		if (parent_of_leaf->parent == nullptr)
			root = leaf;
		else
		{
			if (parent_of_leaf == parent_of_leaf->parent->left)
				parent_of_leaf->parent->left = leaf;                     //зануляем указатели посленего элемента
			else
				parent_of_leaf->parent->right = leaf;
		}
		if (parent_of_leaf != current)                                  //переносим значения последнего элемента
		{
			current->color = parent_of_leaf->color;
			current->key = parent_of_leaf->key;
		}
		if (parent_of_leaf->color == 'b')                              //перебалансировка цветов
			delfix(leaf);
	}
	size--;
}

template <typename T, typename T2 >
void Map<T, T2>::delfix(node * current)
{
	node* temp_elem;
	while (current != nullptr && current != root && current->color == 'b')
	{
		if (current->parent->left == current)
		{
			temp_elem = current->parent->right;
			if (temp_elem->color == 'r')
			{
				temp_elem->color = 'b';
				current->parent->color = 'r';
				leftrotate(current->parent);
				temp_elem = current->parent->right;
			}
			if (temp_elem->right->color == 'b' && temp_elem->left->color == 'b')
			{
				temp_elem->color = 'r';
				current = current->parent;
			}
			else
			{
				if (temp_elem->right->color == 'b')
				{
					temp_elem->left->color = 'b';
					temp_elem->color = 'r';
					rightrotate(temp_elem);
					temp_elem = current->parent->right;
				}
				temp_elem->color = current->parent->color;
				current->parent->color = 'b';
				temp_elem->right->color = 'b';
				leftrotate(current->parent);
				current = root;
			}
		}
		else
		{
			temp_elem = current->parent->left;
			if (temp_elem->color == 'r')
			{
				temp_elem->color = 'b';
				current->parent->color = 'r';
				rightrotate(current->parent);
				temp_elem = current->parent->left;
			}
			if (temp_elem->left->color == 'b' && temp_elem->right->color == 'b')
			{
				temp_elem->color = 'r';
				current = current->parent;
			}
			else
			{
				if (temp_elem->left->color == 'b')
				{
					temp_elem->right->color = 'b';
					temp_elem->color = 'r';
					leftrotate(temp_elem);
					temp_elem = current->parent->left;
				}
				temp_elem->color = current->parent->color;
				current->parent->color = 'b';
				temp_elem->left->color = 'b';
				rightrotate(current->parent);
				current = root;
			}
		}
		current->color = 'b';
		root->color = 'b';
	}
}

template <typename T, typename T2>
typename Map<T, T2>::node* Map<T, T2>::node_find(node * node, T key)
{
	if (node == nullptr)
		return nullptr;
	if (key < node->key)
		return node_find(node->left, key);
	if (key > node->key)
		return node_find(node->right, key);
	if (node->key == key)
		return node;
	return nullptr;
}

template <typename T, typename T2 >
T2 Map<T, T2>::find(T key)
{
	if (this->root == nullptr)
	{
		throw out_of_range("Tree is empty");
	}
	node* temp = node_find(root, key);
	if (temp == nullptr)
		return {};
	return temp->data;
}

template <typename T, typename T2>
bool Map<T, T2>::Find(T key, T2 & value)
{
	if (this->root == nullptr)
	{
		throw out_of_range("Tree is empty");
	}
	node* temp = node_find(root, key);
	if (temp == nullptr)
		return false;
	value = (*temp).data;
	return true;
}

template <typename T, typename T2 >
void Map<T, T2>::get_keys()
{
	if (this->root == nullptr)
	{
		throw out_of_range("SOS! ATTENTION! ERROR!");
	}

	auto it = create_btf_iterator();
	while (it->has_next())
	{
		cout << it->next()->key << ' ';
	}
	cout << '\n';
	auto it1 = create_btf_iterator();
	while (it1->has_next())
	{
		cout << it1->next()->color << ' ';
	}

	cout << '\n';
}

template <typename T, typename T2 >
void Map<T, T2>::get_value()
{
	if (this->root == nullptr)
	{
		throw out_of_range("SOS! ATTENTION! ERROR!");
	}
	auto it1 = create_btf_iterator();
	while (it1->has_next())
		cout << it1->next()->data << ' ';
	cout << '\n';
}

template <typename T, typename T2 >
int Map<T, T2>::get_size() {
	return size;
}

template <typename T, typename T2 >
void Map<T, T2>::clear()                   //clear of RED-BLACK-TREE
{
	/*while (size > 0)
		remove(root->key);*/

	if (size == 0) cout << "\n";
}

template <typename T, typename T2 >
typename Map<T, T2>::node* Map<T, T2>::get_leaf(node * current)      //получение крайнего листового элемента
{
	node* leaf = NULL;
	if (current->left != NULL)
	{
		leaf = current->left;
		while (leaf->right != NULL)
			leaf = leaf->right;
	}
	else
	{
		leaf = current->right;
		while (leaf->left != NULL)
			leaf = leaf->left;
	}
	return leaf;
}

template <typename T, typename T2 >
void Map<T, T2>::insert(T key, T2 value) {
	node* help_elem, * prev;
	node* current = new node(key, value);
	help_elem = root;
	prev = nullptr;
	if (root == nullptr)                         //если список пустой
	{
		add_first(current);
	}
	else
	{
		while (help_elem != nullptr)               //цикл для нахождения места для вставки нового элемента
		{
			prev = help_elem;
			if (help_elem->key < current->key)
				help_elem = help_elem->right;
			else
				if (help_elem->key > current->key)
					help_elem = help_elem->left;
				else
					if (help_elem->key == current->key)
						return;
		}
		current->parent = prev;
		if (prev->key < current->key)
			prev->right = current;
		else
			prev->left = current;
	}

	insertfix(current);
	size++;
}

template <typename T, typename T2 >
void Map<T, T2>::insertfix(node * current) {  // расстановка цветов по правилам
	node* uncle;
	if (root == current)
	{
		current->color = 'b';
		return;
	}

	while (current->parent != nullptr && current->parent->color == 'r')
	{
		node* grandparents = current->parent->parent;
		if (grandparents->left == current->parent)
		{
			if (grandparents->right != nullptr)
			{
				uncle = grandparents->right;
				if (uncle->color == 'r')
				{
					current->parent->color = 'b';
					uncle->color = 'b';
					grandparents->color = 'r';
					current = grandparents;
				}
			}
			else
			{
				if (current->parent->right == current)
				{
					current = current->parent;
					leftrotate(current);
				}
				current->parent->color = 'b';
				grandparents->color = 'r';
				rightrotate(grandparents);
			}
		}
		else
		{
			if (grandparents->left != nullptr)
			{
				uncle = grandparents->left;
				if (uncle->color == 'r')
				{
					current->parent->color = 'b';
					uncle->color = 'b';
					grandparents->color = 'r';
					current = grandparents;
				}
			}
			else
			{
				if (current->parent->left == current)
				{
					current = current->parent;
					rightrotate(current);
				}
				current->parent->color = 'b';
				grandparents->color = 'r';
				leftrotate(grandparents);
			}
		}
		root->color = 'b';
	}
}

template <typename T, typename T2 >
void Map<T, T2>::leftrotate(node * current)
{
	if (current->right == nullptr)
		return;
	else
	{
		node* y = current->right;
		if (y->left != nullptr)
		{
			current->right = y->left;
			y->left->parent = current;
		}
		else
			current->right = nullptr;
		if (current->parent != nullptr)
			y->parent = current->parent;
		if (current->parent == nullptr)
			root = y;
		else
		{
			if (current == current->parent->left)
				current->parent->left = y;
			else
				current->parent->right = y;
		}
		y->left = current;
		current->parent = y;
	}
}

template <typename T, typename T2 >
void Map<T, T2>::rightrotate(node * current)
{
	if (current->left == nullptr)
		return;
	else
	{
		node* child = current->left;
		if (child->right != nullptr)
		{
			current->left = child->right;
			child->right->parent = current;
		}
		else
			current->left = nullptr;
		if (current->parent != nullptr)
			child->parent = current->parent;
		if (current->parent == nullptr)
			root = child;
		else
		{
			if (current == current->parent->left)
				current->parent->left = child;
			else
				current->parent->right = child;
		}
		child->right = current;
		current->parent = child;
	}
}