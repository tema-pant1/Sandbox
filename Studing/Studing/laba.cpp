#include <iostream>
#include "DLList.h"
#include <windows.h>

using namespace std;

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	DLList<int> list;
	for (int i = 0; i < 5; i++) list.push_back(i * i);
	list.status();
	list.insert(52, 52);
	list.status();
	return 0;
}