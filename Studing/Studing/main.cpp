#include <iostream>
#include "Timsort.h"
#include <ctime>

using namespace std;

int main()
{
	DynamicArray<int> a = random_array<int>(20000);
	DynamicArray<int> b(20000);
	b.copy(a);
	//b.status();
	clock_t start = clock();
	insertion_sort(b, 0, 0, b.GetSize());
	double insertion_sort_time = (double)(clock() - start) / CLOCKS_PER_SEC;
	start = clock();
	timsort(a);
	double timsort_time = (double)(clock() - start) / CLOCKS_PER_SEC;
	SetRus();
	cout << "Время работы сортировки вставками - " << insertion_sort_time << endl;
	cout << "Время работы сортировки timsort - " << timsort_time << endl;
	return 0;
}

