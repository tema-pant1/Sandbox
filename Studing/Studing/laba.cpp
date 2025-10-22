#include <iostream>
#include "DLList.h"
#include <windows.h>
#include "Stack.h"
#include "DynArray.h"

using namespace std;

int main()
{
	SetRus();

	DynamicArray<int> dinara;
	for (int i = 0; i < 8; i++)
	{
		dinara.push_back(i * i);
	}

	dinara.status();

	dinara.remove(8);

	dinara.status();



	return 0;
}