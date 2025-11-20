#pragma once
#include <random>
#include "DynArray.h"
#include "Stack.h"

template <typename T>
DynamicArray<T> random_array(int size)
{
	DynamicArray<T> result;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dist(1, 1000);

	for (int i = 0; i < size; i++)
	{
		result.push_back(dist(gen));
	}

	return result;
}

void timsort(DynamicArray<int>& array);

bool balance_stack(stack<std::pair<int, int>>& runs, DynamicArray<int>& array);

void merge(std::pair<int, int> part1, std::pair<int, int> part2, DynamicArray<int>& array);

int GetMinrun(int size);

void insertion_sort(DynamicArray<int>& array, int begin, int begin_sorted, int end);

int GetRun(int begin, int minrun, DynamicArray<int>& array);

//int binary_search_range(DynamicArray<int>& array, int start, int end, int value, bool find_insert_pos);

int gallop_right(DynamicArray<int>& left, int left_start, DynamicArray<int>& right, int right_start, int right_end);

int gallop_left(DynamicArray<int>& right, int right_start, DynamicArray<int>& left, int left_start, int left_end);


