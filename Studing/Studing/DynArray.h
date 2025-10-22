#pragma once
#include <iostream>
#include "DLList.h"

template <typename data_t> class DynamicArray
{
	data_t* data;
	int size;
	int capacity;
public:
	DynamicArray() : data(new data_t[2]), size(0), capacity(2) {};

	void show()
	{
		if (size == 0)
		{
			std::cout << "[]\n";
			return;
		}
		else
		{
			std::cout << "[";
			for (int i = 0; i < size - 1; i++) std::cout << data[i] << ", ";
			std::cout << data[size-1] << "]\n";
		}
	}

	void status()
	{
		SetRus();
		show();
		std::cout << "Занято " << size << " из " << capacity << "\n\n";
		UnsetRus()
	}

	void resize()
	{
		data_t* new_arr = new data_t[capacity * 2];
		std::copy(data, data + capacity, new_arr);
		data = new_arr;
		capacity *= 2;
	}

	void push_back(data_t elem)
	{
		if (size == capacity) resize();
		data[size] = elem;
		size++;
	}

	void insert(data_t elem, int index)
	{
		SetRus();
		if (index < 0 || index > size)
		{
			std::cout << "\nОшибка функции insert - Некорректный индекс\n\n";
			UnsetRus()
			return;
		}
		if (index == size)
		{
			push_back(elem);
			UnsetRus()
			return;
		}
		if (size == capacity) resize();
		data_t* new_arr = new data_t[capacity];
		std::copy(data, data + index, new_arr);
		std::copy(data + index, data + size, new_arr + index + 1);
		new_arr[index] = elem;
		delete[] data;
		data = new_arr;
		size++;
		UnsetRus()
	}

	void remove(int index)
	{
		if (size == 0)
		{
			SetRus()
			std::cout << "\nОшибка функции remove - нельзя удалить элемент из пустого списка\n\n";
			UnsetRus()
			return;
		}
		if (index < 0 || index >= size)
		{
			SetRus()
			std::cout << "\nОшибка функции remove - неправильный индекс\n\n";
			UnsetRus()
			return;
		}
		data_t* new_arr = new data_t[capacity];
		std::copy(data, data + index, new_arr);
		std::copy(data + index + 1, data + size, new_arr + index);
		delete[] data;
		data = new_arr;
		size--;
	}
};