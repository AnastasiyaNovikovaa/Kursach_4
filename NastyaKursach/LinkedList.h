#pragma once
#include <stdexcept>
#include "Iterator.h"

template <typename  T>
class List {
public:
	class node
	{
	public:
		node(T data, node* next = nullptr, node* prev = nullptr) {
			this->data = data;
			this->next = next;
			this->prev = prev;
		};
		~node()
		{
			next = nullptr;
			delete next;
			prev = nullptr;
			delete prev;
			data = {};
		};
		T data;
		node* next;
		node* prev;
	};
	void add_first(T newElem);
	void reset_list();
	node* head{};
	node* tail{};
	size_t size;
	class ListIterator : public Iterator<T>
	{
	public:
		ListIterator(node* head)
		{
			current = head;
		};

	private:
		T next() override;
		bool has_next() override;
		node* current;
	};
public:
	List();
	~List();
	void push_back(T newElem);
	void push_front(T newElem);
	void pop_back(); // удаление последнего элемента
	void pop_front(); // удаление первого элемента
	void insert(size_t index, T newElem); // добавление элемента по индексу
	T at(size_t index) const;
	void remove(size_t index); // удаление элемента по индексу
	size_t get_size() const;
	void print_to_console() const; // вывод элементов списка в консоль через разделитель, не использовать at
	void clear(); // удаление всех элементов списка
	void set(size_t index, T newElem) const; // замена элемента по индексу на передаваемый элемент
	bool isEmpty() const; // проверка на пустоту списка
	bool contains(List* list) const; // проверка на содержание другого списка в списке
	bool contains(T data) const;
	bool equals(List* list) const;

	Iterator<T>* create_list_iterator() const;
};