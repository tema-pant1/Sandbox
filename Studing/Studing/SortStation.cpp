#include <iostream>
#include <map>
#include <string>
#include <stdio.h>

#include "features.h"
#include "Stack.h"
#include "SortStation.h"
#include "DynArray.h"


std::map<std::string, int> operators_priority = { {"sin", 5}, {"cos", 5}, {"^", 4}, { "*", 2 } , {"/", 2}, {"+", 1}, {"-", 1} }; //Указывается оператор и его приоритет

bool is_operator(std::string input)
{
	return (input == "^" || input == "/" || input == "*" || input == "+" || input == "-" || input == "sin" || input == "cos");
}

void from_stck_to_out(stack<std::string>& stack, DynamicArray<std::string>& result)
{
	result.push_back(stack.top());
	stack.pop();
}

int arity(std::string oprtr)
{
	if (oprtr == "sin" || oprtr == "cos") return 1;
	if (oprtr == "+" || oprtr == "-" || oprtr == "*" || oprtr == "/" || oprtr == "^") return 2;
	else return -1;
}

void process_token(std::string& token, stack<std::string>& operators, DynamicArray<std::string>& result)
{
	if (token.empty()) return;

	if (is_num(token)) result.push_back(token);
	else if (token == "(") operators.push(token);
	else if (token == ")")
	{
		while (!operators.is_empty() && operators.top() != "(")
			from_stck_to_out(operators, result);
		if (operators.is_empty()) {
			std::cout << "Ошибка: непарная закрывающая скобка\n";
			return;
		}
		operators.pop();
	}
	else if (is_operator(token))
	{
		while (!operators.is_empty() &&
			operators.top() != "(" &&
			operators_priority[operators.top()] >= operators_priority[token] && token != "^")
		{
			from_stck_to_out(operators, result);
		}
		operators.push(token);
	}

	token = "";
}

void sort_to_RPN(DynamicArray<std::string> &result, std::string input)
{
	std::string token;
	stack<std::string> operators;
	for (int i = 0; i < input.size(); i++)
	{
		if (input[i] == ' ')
		{
			process_token(token, operators, result);
			token = "";
		}
		else token += input[i];
	}
	process_token(token, operators, result);
	while (!operators.is_empty())
	{
		result.push_back(operators.top());
		operators.pop();
	}
	return;
}

double calculate_RPN(DynamicArray<std::string> expression)
{
	double result(0);
	stack<double> numbers;
	for (int i = 0; i < expression.GetSize(); i++)
	{
		std::string token;
		expression.Get(i, token);
		double a, b, oprtr_rslt(0);
		if (is_num(token))
		{
			int num;
			str_to_int(token, num);
			numbers.push(num);
		}
		else if (arity(token) == 1 && numbers.GetSize() >= 1)
		{
			a = numbers.top();
			numbers.pop();
			if (token == "sin") oprtr_rslt = sin(a);
			else if (token == "cos") oprtr_rslt = cos(a);
			numbers.push(oprtr_rslt);
		}
		else if (arity(token) == 2 && numbers.GetSize() >= 2)
		{
			a = numbers.top();
			numbers.pop();
			b = numbers.top();
			numbers.pop();
			if (token == "+") oprtr_rslt = a+b;
			else if (token == "-") oprtr_rslt = b - a;
			else if (token == "*") oprtr_rslt = a * b;
			else if (token == "/") oprtr_rslt = b / a;
			else if (token == "^") oprtr_rslt = pow(b, a);
			numbers.push(oprtr_rslt);
		}
	}
	return numbers.top();
}


void calculator()
{
	SetRus();
	std::string input;
	DynamicArray<std::string> output;
	double result(0);
	std::cout << ">> ";
	std::getline(std::cin, input);
	sort_to_RPN(output, input);
	result = calculate_RPN(output);
	/*std::cout << "Выражение в RPN - ";
	output.show();*/
	printf("%.2f\n", result);

}