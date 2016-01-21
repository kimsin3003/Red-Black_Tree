#include "RedBlackTree.h"
#include <random>
#include <time.h>
int main()
{
	RedBlackTree rb;
	srand(time(NULL));
	for (int i = 0; i < 20; i++)
	{
		rb.Insert(i);
	}

	getchar();
}