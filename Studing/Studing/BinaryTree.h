#pragma once

#include "features.h"

#include <iostream>

template <typename T>
struct binary_tree_node
{
	T value;
	binary_tree_node* left, * right;

//public:

	binary_tree_node(T value) :
		value(value), left(nullptr), right(nullptr) {};

	~binary_tree_node()
	{
		delete left;
		delete right;
	}

};

const bool RIGHT = true;
const bool LEFT = false;
const char T_BRANCH = (char)-61; //символ ├
const char L_BRANCH = (char)-64;  //символ └
const char BRANCH = (char)-60; //символ ─
const char VERT_BRANCH = (char)-77; //символ │

template <typename T>
class BinaryTree 
{
	binary_tree_node<T>* root;

	void overwritig_error()
	{
		SetRus();
		std::cout << "Ошибка добавления узла - нельзя перезаписать сущетсвующий элемент";
		std::exit(-1);
	}

	void nonexist_parent_error()
	{
		SetRus();
		std::cout << "Ошибка добавления узла - нулевой родитель\n";
		std::exit(-1);
	}

	void print_node(binary_tree_node<T>* node, int depth, bool is_right_parent)
	{
		/*
		1) разбиаремся с отступами
		2) выводим значение
		3) вызываем рекурсивно для правой ветки
		4) вызываем рекурсивно для левой
		*/

	}

public: 
	
	BinaryTree() : root(nullptr) {};

	BinaryTree(binary_tree_node<T> root) : root(&root) {};

	BinaryTree(T value) {root = new binary_tree_node<T>(value);}

	~BinaryTree() { delete root; }

	void add(binary_tree_node<T>* parent, T value, bool is_right = 0) 
	{
		if (!parent) nonexist_parent_error();
		binary_tree_node<T>* child = new binary_tree_node<T>(value);
		if (is_right)
		{
			if (parent->right) overwritig_error();
			parent->right = child;
		}
		else
		{
			if (parent->left) overwritig_error();
			parent->left = child;
		}
	}

	void fill(int depth, binary_tree_node<T>* node = nullptr)
	{
		if (depth == 0) return;
		if (node == nullptr)
		{
			root = new binary_tree_node<T>(random());
			node = root;
		}
		add(node, random(), LEFT);
		add(node, random(), RIGHT);
		fill(--depth, node->left);
		fill(depth, node->right);
	}

	void show()
	{
		print_node(root, 0, 0);
	}

};
