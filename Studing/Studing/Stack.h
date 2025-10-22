#pragma once
#include "DLList.h"

template <typename data_t> class stack {
	Node<data_t>* current;
	int size;
public:
	stack() : current(nullptr), size(0) {};

	int GetSize() { return size; }

	void show()
	{
		if (size == 0)
		{
			std::cout << "\n[]\n";
			return;
		}
		std::cout << std::endl;
		Node<data_t>* cur_node = current;
		while (cur_node != nullptr)
		{
			std::cout << "[" << cur_node->data << "]";
			if (cur_node->next != nullptr) std::cout << "->";
			cur_node = cur_node->next;
		}
	}

	void status()
	{
		SetRus()
		show();
		if (size == 0) 
		{
			std::cout << "\nСтек пуст\n";
			UnsetRus()
			return;
		}
		else
		{
			std::cout << "\nСледующий в очереди - [" << current->data << "]\n";
			UnsetRus()
			return;
		}
	}

	void push(data_t data)
	{
		Node<data_t>* new_current = new Node<data_t>(data);
		new_current->next = current;
		current = new_current;
		size++;
	}

	void pop()
	{
		if (size == 0)
		{
			SetRus();
			std::cout << "\nОшибка функции pop - Нельзя удалить элемнет из пустого стека\n\n";
			UnsetRus()
			return;
		}
		else
		{
			Node<data_t>* del_node = current;
			current = current->next;
			delete del_node;
			size--;
		}
	}
};