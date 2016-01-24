#include "RedBlackTree.h"
#include <random>
#include <time.h>
#include <iostream>
int main()
{
	RedBlackTree rb;
	srand(time(NULL));


	/*
	insert delete는 매번 호출 후에 redblack tree가 유지되고 있는지 검사합니다.
	*/

	//insert 임의의 숫자를 insert.

	std::cout << "insert start\n" << std::endl;
	for (int i = 0; i < 20; i++)
	{
		rb.Insert(rand() %20);
	}

	//search. delete안에서 매번 호출하기 때문에 10만 search해봤습니다. 
	std::cout << "\n\n\nsearch start\n" << std::endl;
	Node* result = rb.SearchData(10);
	if(result)
		std::cout << "search 10: " << (result->data) << std::endl;
	else
		std::cout << "No Such Data" << std::endl;


	//delete 임의의 숫자를 delete. 없는 경우 no matching data가 뜹니다.
	std::cout << "\n\n\ndelete start" << std::endl;
	for (int i = 0; i < 20; i++)
	{
		rb.Delete(rand()%20);
	}

	getchar();
}