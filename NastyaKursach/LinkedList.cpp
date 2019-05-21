#pragma once

#include "List.h"
#include <stdexcept>
#include <iostream>

template <typename T>
void List<T>::reset_list()
{
	head = nullptr;
	tail = nullptr;
	size = 0;
}

template <typename T>
List<T>::List()
{
	reset_list();
}

template <typename T>
List<T>::~List()
{
	//clear();
}

template <typename T>
typename T List<T>::ListIterator::next()
{
	if (!current) return T();
	const T data = current->data;
	current = current->next;
	return data;
}

template <typename T>
bool List<T>::ListIterator::has_next()
{
	return (current != nullptr);
}

template <typename T>
void List<T>::add_first(T newElem)
{
	head = new node(newElem);
	tail = head;
	size = 1;
}

template <typename T>
size_t List<T>::get_size() const
{
	return size;
}

template <typename T>
void List<T>::print_to_console() const
{
	if (size == 0)
		return;
	auto * list = create_list_iterator();
	std::cout << "[nullptr] <- ";
	while (list->has_next()) {
		std::cout << "[" << list->next() << "] <- ";
	}
	std::cout << "[nullptr]" << std::endl;
}

template <typename T>
void List<T>::clear()
{
	if (size == 0) return;

	if (size == 1) {
		reset_list();
		delete head;
		delete tail;
	}
	else {
		while (head != nullptr) {
			pop_front();
		}
		reset_list();
		delete head;
		delete tail;
	}
}

template <typename T>
void List<T>::set(size_t index, T newElem) const
{
	if (index >= size) {
		throw std::out_of_range("Index is greater than list size");
	}
	else {
		size_t counter = 0;
		node* current = head;
		while (counter != index) {
			current = current->next;
			counter++;
		}
		current->data = newElem;
	}
}

template <typename T>
bool List<T>::isEmpty() const
{
	return size == 0;
}

template <typename T>
bool List<T>::contains(List * list) const
{
	if (list->size == 0) return true;
	node * current = head;
	node * current_find = list->head;
	bool contains = false;
	do {
		if (current->data == current_find->data)
		{
			current_find = current_find->next;
			if (current_find == nullptr)
			{
				contains = true;
				break;
			}
			current = current->next;
		}
		else
		{
			contains = false;
			current_find = list->head;
			current = current->next;
		}
	} while (current != nullptr);
	return contains;
}

template <typename T>
bool List<T>::contains(T data) const
{
	node* current = head;
	bool contains = false;
	do {
		if (current->data == data)
		{
			return true;
		}
		current = current->next;
	} while (current != nullptr);
	return false;
}

template <typename T>
bool List<T>::equals(List * list) const
{
	if (size != list->size)//if size equals
		return false;
	for (int i = 0; i < size; i++)
	{
		if (at(i) != list->at(i))
			return false;
	}
	return true;
}

template <typename T>
Iterator<T>* List<T>::create_list_iterator() const
{
	if (this == nullptr && this->head == nullptr) throw std::exception("Does not exist");
	return new ListIterator(this->head);
}

template <typename T>
void List<T>::push_back(T newElem)
{
	if (size == 0) {
		add_first(newElem);
	}
	else {
		tail->next = new node(newElem, nullptr, tail);
		tail = tail->next;
		size++;
	}
}

template <typename T>
void List<T>::push_front(T newElem)
{
	if (size == 0) {
		add_first(newElem);
	}
	else {
		head = new node(newElem, head, nullptr);
		size++;
	}
}

template <typename T>
void List<T>::pop_back()
{
	if (size == 0) return;

	if (size == 1) {
		reset_list();
		delete head;
		delete tail;
	}
	else {
		node* current = tail->prev;
		current->next = nullptr;
		delete tail;
		tail = current;
		size--;
	}
}

template <typename T>
void List<T>::pop_front()
{
	if (size == 0) return;

	if (size == 1) {
		reset_list();
		delete head;
		delete tail;
	}
	else {
		node* current = head->next;
		delete head;
		head = current;
		size--;
	}
}

template <typename T>
void List<T>::insert(size_t index, T newElem)
{
	if (index >= size + 1) {
		throw std::out_of_range("Index is greater than list size and more than the index for teoretical last element");
	}
	else {
		if (size == 0 && index == 0)
		{
			add_first(newElem);
			return;
		}
		if (index == 0)
		{
			push_front(newElem);
			return;
		}
		if (index == size)
		{
			push_back(newElem);
			return;
		}
		size_t counter = 0;
		node* current = head;
		node* prev = nullptr;
		while (counter != index) {
			prev = current;
			current = current->next;
			counter++;
		}
		current = new node(newElem, current, prev);
		if (prev != nullptr) {
			prev->next = current;
		}
		else
		{
			head = current;
		}
		size++;
	}
}

template <typename T>
T List<T>::at(size_t index) const
{
	if (index >= size) {
		throw std::out_of_range("Index is greater than list size");
	}
	else {
		size_t counter = 0;
		node* current = head;
		while (counter != index) {
			current = current->next;
			counter++;
		}
		return current->data;
	}
}

template <typename T>
void List<T>::remove(size_t index)
{
	if (index >= size) {
		throw std::out_of_range("Index is greater than list size");
	}
	else {
		if (size == 0)
		{
			return;
		}
		if (index == 0)
		{
			pop_front();
			return;
		}
		if (index == size - 1)
		{
			pop_back();
			return;
		}
		size_t counter = 0;
		node* current = head;
		while (counter != index) {
			current = current->next;
			counter++;
		}
		current->prev->next = current->next;
		current->next->prev = current->prev;
		delete current;
		size--;
	}
}