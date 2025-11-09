#include "features.h"
#include <windows.h>
#include <string>
#include <iostream>

void SetRus()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
}

void UnsetRus()
{
	SetConsoleOutputCP(866);
	SetConsoleCP(866);
}

bool is_num(std::string input)
{
	if (input == "-" || input.empty()) return false;
	if ((input[0] < '0' || input[0] > '9') && input[0] != '-') return false;
	for (int i = 1; i < input.size(); i++)	if (input[i] < '0' || input[i] > '9') return false;
	return true;
}

void char_to_int(char digit, int& result)
{
	if (digit < '0' || digit > '9')
	{
		std::cout << "Ошибка функции char_to_void - на выход подано не число";
		return;
	}
	result = (int)digit - 48;
}

void str_to_int(std::string str, int& result)
{
	SetRus();
	if (!is_num(str)) 
	{
		std::cout << "\n\nОшибка функции str_to_int - на входе не число\n\n";
		UnsetRus();
		return;
	}
	result = 0;
	int deg(0), digit;
	int end = (str[0] == '-') ? 0 : -1;
	for (int i = (int)str.size() - 1; i > end; i--) 
	{
		char_to_int(str[i], digit);
		result += digit * (int)pow(10, deg++);
	}
	if (str[0] == '-') result *= -1;
}