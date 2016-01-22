#include "RedBlackTree.h"
#include <random>
#include <time.h>
#include <iostream>
int main()
{
	RedBlackTree rb;
	srand(time(NULL));
	for (int i = 0; i < 20; i++)
	{
		rb.Insert(i);
	}

	Node* result = rb.SearchData(10);
	std::cout << (result->data) << std::endl;

	getchar();
}