#pragma once
#include "DLList.h"
#include "features.h"

template <typename data_t> class stack {
	Node<data_t>* current;
	int size;
public:
	stack() : current(nullptr), size(0) {};

	int GetSize() { return size; }

	data_t& operator[](int index)
	{
		if (index < 0 || index >= size)
		{
			SetRus();
			std::cout << "Ошибка оператора стека [] - неправильный индекс";
			std::exit(2);
		}
		Node<data_t>* data = current;
		for (int i = 1; i < index + 1; i++)
		{
			data = data->next;
		}
		return data->data;
	}

	const data_t& operator[](int index) const
	{
		if (index < 0 || index >= size)
		{
			SetRus();
			std::cout << "Ошибка оператора стека [] - неправильный индекс";
			std::exit(2);
		}
		Node<data_t>* data = current;
		for (int i = 1; i < index + 1; i++)
		{
			data = data->next;
		}
		return data->data;
	}

	bool is_empty()
	{
		if (size == 0) return true;
		return false;
	}

	data_t top() { return current->data; }

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

	void remove(int index)
	{
		if (size == 0)
		{
			SetRus();
			std::cout << "Ошибка удаления элементов стека - стек пуст\n";
			std::exit(3);
		}
		if (index < 0 || index >= size)
		{
			SetRus();
			std::cout << "Ошибка удаления элементов стека - неправильный индекс\n";
			std::exit(4);
		}
		if (index == 0) pop();
		Node<data_t>* cur = current;
		Node <data_t>* deleted;
		for (int i = 0; i < index - 1; i++) cur = cur->next;
		deleted = cur->next;
		cur->next = deleted->next;
		delete deleted;
	}

	void status()
	{
		SetRus();
		show();
		if (size == 0) 
		{
			std::cout << "\nСтек пуст\n";
			UnsetRus();
			return;
		}
		else
		{
			std::cout << "\nСледующий в очереди - [" << current->data << "]\n";
			UnsetRus();
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
			UnsetRus();
			return;
		}
		else
		{
			Node<data_t>* del_node = current;
			current = current->next;
			delete del_node;
			size--;
			return;
		}
	}
};