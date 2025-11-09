#pragma once
#include <iostream>
#include <windows.h>
#include "features.h"

template <typename data_t> class Node
{
public:
	data_t data;
	Node* next;
	Node* previous;
	Node(data_t data, Node* next, Node* previous) : data(data), next(next), previous(previous) {};
	Node(data_t data) : data(data), next(nullptr), previous(nullptr) {};
};


template <typename data_t> class DLList
{
	Node<data_t>* head;
	Node<data_t>* tail;
	int size;
public:
	DLList() : head(nullptr), tail(nullptr), size(0) {};

	int GetSize() { return size; }

	Node<data_t>* GetHead() { return head; }

	Node<data_t>* GetTail() { return tail; }

	Node<data_t>* find(int index)
	{
		SetRus();
		if (size == 0)
		{
			std::cout << "\nОшибка функции find - Списко пуст.\n\n";
			UnsetRus();
			return nullptr;
		}
		if (index < 0 || index > size)
		{
			std::cout << "\nОшибка функции find - Неправильный индекс.\n\n";
			UnsetRus();
			return nullptr;
		}
		Node<data_t>* cur_node = head;
		for (int cur_indx = 1; cur_indx <= index; cur_indx++) cur_node = cur_node->next;
		UnsetRus();
		return cur_node;
	}

	void show()
	{
		Node<data_t>* cur_node = head;
		if (GetSize() == 0)
		{
			std::cout << "[]";
			return;
		}
		while (cur_node != nullptr)
		{
			std::cout << "[" << cur_node->data << "]";
			if (cur_node->next != nullptr) std::cout << "<->";
			cur_node = cur_node->next;
		}

	}

	void status()
	{
		SetRus();
		show();
		std::cout << "\nРазмер списка - " << GetSize();
		if (size == 0)
		{
			std::cout << "\nСписок пустой\n";
			UnsetRus();
			return;
		}
		else
		{
			std::cout << "\nГолова - [" << head->data << "]";
			std::cout << "\nХвост - [" << tail->data << "]" << "\n\n";
		}
		UnsetRus();
	}

	void push_back(data_t data)
	{
		Node<data_t>* new_node = new Node<data_t>(data);
		if (head == nullptr)
		{
			head = new_node;
			tail = head;
		}
		else
		{
			tail->next = new_node;
			new_node->previous = tail;
			tail = new_node;
		}
		size++;
	}

	void insert(data_t data, int index)
	{
		Node<data_t>* new_node = new Node<data_t>(data);

		if (index < 0 || index > size)
		{
			SetRus();
			std::cout << "Ошибка: Некорректный индекс\n\n";
			UnsetRus();
			return;
		}
		if (index == 0)
		{
			new_node->next = head;
			head->previous = new_node;
			head = new_node;
			return;
			size++;
		}
		else if (index == size)
		{
			push_back(data);
			return;
		}
		else
		{
			Node<data_t>* prev_node = find(index - 1);
			new_node->next = prev_node->next;
			new_node->previous = prev_node;
			prev_node->next = new_node;
			(new_node->next)->previous = new_node;
			size++;
		}
	}

	void earase(int index)
	{
		if (size == 0)
		{
			SetRus();
			std::cout << "\nОшибка функции pop - Список пустой\n\n";
			UnsetRus();
			return;
		}
		if (index < 0 || index > size)
		{
			SetRus();
			std::cout << "\nОшибка функции pop - Неправильный индекс\n\n";
			UnsetRus();
			return;
		}
		if (index == 0)
		{
			Node<data_t>* new_head = head->next;
			new_head->previous = nullptr;
			delete head;
			head = new_head;
			size--;
			return;
		}
		if (index == size - 1)
		{
			Node<data_t>* new_tail = tail->previous;
			new_tail->next = nullptr;
			delete tail;
			tail = new_tail;
			size--;
			return;
		}
		else
		{
			Node<data_t>* deleted_node = find(index);
			Node<data_t>* prev_node = deleted_node->previous;
			Node<data_t>* next_node = deleted_node->next;
			prev_node->next = next_node;
			next_node->previous = prev_node;
			delete deleted_node;
			size--;
			return;
		}
	}
};

