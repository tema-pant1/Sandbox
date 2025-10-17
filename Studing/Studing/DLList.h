#pragma once
#include <iostream>
#include <windows.h>

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
	void SetRus()
	{
		SetConsoleOutputCP(1251);
		SetConsoleCP(1251);
	}
public:
	DLList() : head(nullptr), tail(nullptr), size(0) {};

	int GetSize() { return size; }

	Node<data_t>* find(int index)
	{
		SetRus();
		if (size == 0)
		{
			std::cout << "\nОшибка функции find - Списко пуст.\n\n";
			return nullptr;
		}
		if (index < 0 || index > size)
		{
			std::cout << "\nОшибка функции find - Неправильный индекс.\n\n";
			return nullptr;
		}
		Node<data_t>* cur_node = head;
		for (int cur_indx = 1; cur_indx <= index; cur_indx++) cur_node = cur_node->next;
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
			if (cur_node->next != nullptr) std::cout << "->";
			cur_node = cur_node->next;
		}

	}

	void status()
	{
		SetConsoleOutputCP(1251);
		SetConsoleCP(1251);
		show();
		std::cout << "\nРазмер списка - " << GetSize();
		if (GetSize() == 0)
		{
			std::cout << "\nСписок пустой\n";
			return;
		}
		else
		{
			std::cout << "\nГолова - [" << head->data << "]";
			std::cout << "\nХвост - [" << tail->data << "]" << "\n\n";
		}
		/*	SetConsoleOutputCP(866);
			SetConsoleCP(866);*/
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
			SetConsoleOutputCP(1251);
			SetConsoleCP(1251);
			std::cout << "Ошибка: Некорректный индекс\n\n";
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
};