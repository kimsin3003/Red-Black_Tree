#include "RedBlackTree.h"
#include <iostream>

RedBlackTree::RedBlackTree()
{
	NIL = new Node;
	NIL->color = BLACK;
	NIL->left = nullptr;
	NIL->right = nullptr;
	NIL->data = -1;
	root = nullptr;
}


RedBlackTree::~RedBlackTree()
{
}

void RedBlackTree::Insert(int data) {
	Node* newNode = new Node;
	newNode->color = RED;
	newNode->data = data;

	if (root == nullptr)//when there's no node in tree.
	{
		root = newNode;
		root->color = BLACK;
		root->data = data;
		root->left = NIL;
		root->right = NIL;
		root->parent = NIL;
		return;
	}


	_Insert(root, newNode);
	FixViolation(newNode);

	//결과 체크
	if (CheckRB(this)) {
		std::cout << "Insert complete" << std::endl;
	}
	else
	{
		std::cout << "Insert Fail fail" << std::endl;
	}
}


void RedBlackTree::FixViolation(Node* node)
{
	if (node->parent->color == BLACK) //부모가 black인 경우 
	{
		if (node->parent == NIL) // 자신이 root일때.
			node->color = BLACK;
	}
	else
	{
		Node* grandParent = node->parent->parent;
		if (grandParent->left == node->parent) // 부모가 GP의 leftchild인 경우
		{
			
			if (grandParent->right->color == BLACK) // uncle이 black이면 
			{
				
				if (node->parent->right == node)
				{
					LeftRotate(node->parent);// 현재 노드가 rightchild이면 leftchild가 되게 함.
				}
				grandParent->color = RED;
				node->parent->color = BLACK;
				RightRotate(grandParent);
			}
			else // uncle이 RED이면
			{
				grandParent->color = RED;
				grandParent->left->color = BLACK;
				grandParent->right->color = BLACK;
				FixViolation(grandParent);
			}

		}
		else// // 부모가 GP의 rightchild인 경우
		{
			if (grandParent->left->color == BLACK)
			{
				if (node->parent->left == node)
				{
					RightRotate(node->parent);
				}
				grandParent->color = RED;
				node->parent->color = BLACK;
				LeftRotate(grandParent);
			}
			else
			{
				grandParent->color = RED;
				grandParent->left->color = BLACK;
				grandParent->right->color = BLACK;
				FixViolation(grandParent);
			}
		}
	}
}

void RedBlackTree::_Insert(Node* curNode, Node* newNode)
{
	if (curNode == nullptr || newNode == nullptr)
		return;

	if (curNode->data > newNode->data) {

		if (curNode->left == NIL)
		{
			curNode->left = newNode;
			newNode->left = NIL;
			newNode->right = NIL;
			newNode->parent = curNode;
			return;
		}
		_Insert(curNode->left, newNode);
	}
	else {

		if (curNode->right == NIL)
		{
			curNode->right = newNode;
			newNode->left = NIL;
			newNode->right = NIL;
			newNode->parent = curNode;
			return;
		}
		_Insert(curNode->right, newNode);
	}
}


void RedBlackTree::LeftRotate(Node* node)
{
	Node* y = node->right;
	node->right = y->left;
	if (y->left != nullptr)
		y->left->parent = node;
	y->parent = node->parent;
	if (node->parent == nullptr)
		root = y;
	else if (node == node->parent->left)
		node->parent->left = y;
	else
		node->parent->right = y;

	y->left = node;
	node->parent = y;
}

void RedBlackTree::RightRotate(Node* node)
{
	Node* y = node->left;
	node->left = y->right;
	if (y->right != nullptr)
		y->right->parent = node;
	y->parent = node->parent;
	if (node->parent == nullptr)
		root = y;
	else if (node == node->parent->left)
		node->parent->left = y;
	else
		node->parent->right = y;

	y->right = node;
	node->parent = y;
}

bool RedBlackTree::CheckRB(RedBlackTree* rb) {

	if (CountBlack(rb->root) != -1)
		return true;
	else
		return false;
}

int RedBlackTree::CountBlack(Node* node) {

	if (node == NIL) {
		return 1;
	}

	int left = CountBlack(node->left);
	if (left == -1)
		return -1;
	int right = CountBlack(node->right);
	if (right == -1)
		return -1;

	if (left != right)
		return -1;
	else {
		if (node->color == BLACK)
			return left + 1;
		else
			return left;
	}
}
