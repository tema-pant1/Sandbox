#pragma once
#include <iostream>
#include "features.h"

template <typename data_t> class DynamicArray
{
	data_t* data;
	int size;
	int capacity;
	
	bool correct_index(int index)
	{
		if (index < 0 || index >= capacity) return false;
		return true;
	}

public:
	DynamicArray(int razmer = 2) : data(new data_t[razmer]), size(0), capacity(razmer) {};

	//DynamicArray(DynamicArray<data_t> source, int begin = 0; int end = source.GetSize())
	//{
	//	size = source.GetSize();
	//	capasity = source.GetCapasity();
	//	for (int i = 0; i < size; i++) data[i] = source[i];
	//}

	int GetSize() { return size; }

	int GetCapasity() { return capacity; }
	
	data_t& operator[](int index)
	{
		if (!correct_index(index))
		{
			SetRus();
			std::cout << "\nОшибка оператора [] - неправильный индекс: " << index << "\n\n";
			std::exit(1);
		}
		return data[index];
	}

	const data_t& operator[](int index) const
	{
		if (!correct_index(index))
		{
			SetRus();
			std::cout << "\nОшибка оператора [] - неправильный индекс: " << index << "\n\n";
			std::exit(1);
		}
		return data[index];
	}

	void show(int begin = 0, int end = -1)
	{
		if (size == 0)
		{
			std::cout << "[]\n";
			return;
		}
		else
		{
			if (end == -1) end = size;
			std::cout << "[";
			for (int i = begin; i < end - 1; i++) std::cout << data[i] << ", ";
			std::cout << data[end - 1] << "]\n";
		}
	}

	void copy(data_t* input, int size, data_t* output)
	{
		for (int i = 0; i < size; i++) output[i] = input[i];
	}

	void copy(DynamicArray<data_t> from, int begin_to = 0, int begin_from = 0, int tsize = -1)
	{
		if (tsize == -1) tsize = from.GetSize();
		if (!correct_index(begin_from) || !correct_index(begin_to))
		{
			SetRus();
			std::cout << "\nОшибка функции копирования массива - неправильный индекс начала\n\n";
			std::exit(5);
		}
		if (tsize > capacity - begin_to)
		{
			SetRus();
			std::cout << "\nОшибка функции копирования массива - слишком большой массиив:\n\n";
			std::exit(6);
		}
		for (int i(0); i < tsize; i++)
		{
			if (i >= size) size++;
			data[begin_to++] = from[begin_from++];
		}
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
		if (!correct_index(index))
		{
			SetRus();
			std::cout << "\nОшибка функции remove - неправильный индекс\n\n";
			UnsetRus();
			return;
		}
		shift_elem_l(data, index);
		size--;
	}

	void swap(int index1, int index2)
	{
		if (correct_index(index1) && correct_index(index2))
		{
			data_t temp = data[index1];
			data[index1] = data[index2];
			data[index2] = temp;
		}
		else
		{
			SetRus();
			std::cout << "\nОшибка функции swap - неправильный индекс\n\n";
			UnsetRus();
			return;
		}
	}

	void reverse(int begin = 0, int end = -1)
	{
		if (end == -1) end = GetSize()-1;
		while (begin < end) swap(begin++, end--);
	}
};