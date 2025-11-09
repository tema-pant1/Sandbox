#pragma once
#include <iostream>
#include "features.h"

template <typename data_t> class DynamicArray
{
	data_t* data;
	int size;
	int capacity;
public:
	DynamicArray() : data(new data_t[2]), size(0), capacity(2) {};

	int GetSize() { return size; }

	void Get(int index, data_t& result)
	{
		SetRus();
		if (index < 0 || index >= size)
		{
			std::cout << "\nОшбика функции Get - неправильный индекс\n\n";
			UnsetRus();
			return;
		}
		result = data[index];
	}

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
			std::cout << data[size - 1] << "]\n";
		}
	}

	void copy(data_t* input, int size, data_t* output)
	{
		for (int i = 0; i < size; i++) output[i] = input[i];
	}

	void shift_elem_r(data_t* array, int index)
	{
		for (int i = size; i != index; i--) array[i] = array[i - 1];
	}

	void status()
	{
		SetRus();
		show();
		std::cout << "Занято " << size << " из " << capacity << "\n\n";
		UnsetRus();
	}

	void resize()
	{
		data_t* new_arr = new data_t[capacity * 2];
		copy(data, size, new_arr);
		delete[] data;
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
			UnsetRus();
			return;
		}
		if (index == size)
		{
			push_back(elem);
			UnsetRus();
			return;
		}
		if (size == capacity) resize();
		shift_elem_r(data, index);
		data[index] = elem;
		size++;
		UnsetRus();
	}

	void shift_elem_l(data_t* array, int index)
	{
		for (int i = index; i < size - 1; i++)
		{
			array[i] = array[i + 1];
		}
	}

	void remove(int index)
	{
		if (size == 0)
		{
			SetRus();
			std::cout << "\nОшибка функции remove - нельзя удалить элемент из пустого списка\n\n";
			UnsetRus();
			return;
		}
		if (index < 0 || index >= size)
		{
			SetRus();
			std::cout << "\nОшибка функции remove - неправильный индекс\n\n";
			UnsetRus();
			return;
		}
		shift_elem_l(data, index);
		size--;
	}
};