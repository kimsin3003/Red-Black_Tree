#include "RedBlackTree.h"
#include <random>
#include <time.h>
#include <iostream>
int main()
{
	RedBlackTree rb;
	srand(time(NULL));


	/*
	insert delete�� �Ź� ȣ�� �Ŀ� redblack tree�� �����ǰ� �ִ��� �˻��մϴ�.
	*/

	//insert ������ ���ڸ� insert.

	std::cout << "insert start\n" << std::endl;
	for (int i = 0; i < 20; i++)
	{
		rb.Insert(rand() %20);
	}

	//search. delete�ȿ��� �Ź� ȣ���ϱ� ������ 10�� search�غý��ϴ�. 
	std::cout << "\n\n\nsearch start\n" << std::endl;
	Node* result = rb.SearchData(10);
	if(result)
		std::cout << "search 10: " << (result->data) << std::endl;
	else
		std::cout << "No Such Data" << std::endl;


	//delete ������ ���ڸ� delete. ���� ��� no matching data�� ��ϴ�.
	std::cout << "\n\n\ndelete start" << std::endl;
	for (int i = 0; i < 20; i++)
	{
		rb.Delete(rand()%20);
	}

	getchar();
}