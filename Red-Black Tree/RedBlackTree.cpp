#include "RedBlackTree.h"
#include <iostream>

RedBlackTree::RedBlackTree()
{
	NIL = new Node;
	NIL->color = BLACK;
	NIL->left = nullptr;
	NIL->right = nullptr;
	NIL->parent = nullptr;
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
	FixInsertViolation(newNode);

	//��� üũ
	if (CheckRB(this)) {
		std::cout << "Insert complete" << std::endl;
	}
	else
	{
		std::cout << "Insert Fail" << std::endl;
	}
}


//�ߺ� ���� ���ٰ� ���� ®���ϴ�.
void RedBlackTree::Delete(int data) {

	Node* nodeToDelete = nullptr;

	if (!(nodeToDelete = _SearchNode(root, data))) {
		std::cout << "no matching data" << std::endl;
		return;
	}
	_Delete(root, data);
	FixDeleteViolation(nodeToDelete);

	//��� üũ
	if (CheckRB(this)) {
		std::cout << "Delete complete" << std::endl;
	}
	else
	{
		std::cout << "Delete Fail fail" << std::endl;
	}
}

Node* RedBlackTree::SearchData(int data)
{
	return _SearchNode(root, data);
}

Node* RedBlackTree::_SearchNode(Node* curNode, int data)
{
	if (!curNode)
		return nullptr;
	
	if (curNode->data == data)
		return curNode;

	else if (curNode->data < data)
	{
		if (curNode->right == NIL)
			return nullptr;
		else
			return _SearchNode(curNode->right, data);
	}
	else
	{
		if (curNode->left == NIL)
			return nullptr;
		else
			return _SearchNode(curNode->left, data);
	}
}

void RedBlackTree::_Delete(Node* curNode, int data)
{
	if (curNode == nullptr)
		return;

	Node * successor;

	if (curNode->left == NIL) // left child�� ���� ���
		Transplant(this, curNode, curNode->right); // node->right�� NULL�� ��� ����
	else if (curNode->right == NIL) // left child�� �ְ� right child�� ���� ���
		Transplant(this, curNode, curNode->left);
	else { // child�� 2���� ���
		successor = TreeMinimum(curNode->right); // right subtree���� �ּҰ� ���
		if (curNode->right != successor) {
			Transplant(this, successor, successor->right);
			successor->right = curNode->right; // successor�� child ����
			successor->right->parent = successor; // right child�� �θ� ����
		}
		Transplant(this, curNode, successor); // ���⿡�� node �ڸ��� successor �̽�
		successor->left = curNode->left; // successor�� left child ����
		successor->left->parent = successor; // successor�� parent ����
	}

}

void RedBlackTree::Transplant(RedBlackTree * tree, Node* delNode, Node* plantNode) // �̽ĵ� ���
{
	if (delNode->parent == NIL) { // parent�� NULL�� ���
		tree->root = plantNode;
		tree->root->parent = NIL;
	}
	else if (delNode->parent->left == delNode)
		delNode->parent->left = plantNode;
	else if (delNode->parent->right == delNode)
		delNode->parent->right = plantNode;
	if (plantNode)
		plantNode->parent = delNode->parent;
}

Node* RedBlackTree::TreeMinimum(Node* node) {
	if (node->left == NIL)
		return node;
	else
		return TreeMinimum(node->left);
}


void RedBlackTree::FixDeleteViolation(Node * node)
{
}

void RedBlackTree::FixInsertViolation(Node* node)
{
	if (node->parent->color == BLACK) //�θ� black�� ��� 
	{
		if (node->parent == NIL) { // �ڽ��� root�϶�.
			node->color = BLACK;
			return;
		}
	}
	else
	{
		Node* grandParent = node->parent->parent;
		if (grandParent->left == node->parent) // �θ� GP�� leftchild�� ���
		{
			
			if (grandParent->right->color == BLACK) // uncle�� black�̸� 
			{
				
				if (node->parent->right == node)// ���� ��尡 rightchild�̸�
				{
					node = node->parent;
					LeftRotate(node);

				}
				grandParent->color = RED;
				node->parent->color = BLACK;
				RightRotate(grandParent);
			}
			else // uncle�� RED�̸�
			{
				grandParent->color = RED;
				grandParent->left->color = BLACK;
				grandParent->right->color = BLACK;
				FixInsertViolation(grandParent);
			}

		}
		else// // �θ� GP�� rightchild�� ���
		{
			if (grandParent->left->color == BLACK)
			{
				if (node->parent->left == node)
				{
					node = node->parent;
					RightRotate(node);
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
				FixInsertViolation(grandParent);
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
	if (y->left != NIL)
		y->left->parent = node;
	y->parent = node->parent;
	if (node->parent == NIL)
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
	if (y->right != NIL)
		y->right->parent = node;
	y->parent = node->parent;
	if (node->parent == NIL)
		root = y;
	else if (node == node->parent->left)
		node->parent->left = y;
	else
		node->parent->right = y;

	y->right = node;
	node->parent = y;
}

bool RedBlackTree::CheckRB(RedBlackTree* rb) {

	int count = _CheckRB(rb->root);
	if (count != -1)
		return true;
	else
		return false;

}

int RedBlackTree::_CheckRB(Node* node) {

	if (!node)
		return 0;

	if (node == NIL) {
		return 1;
	}

	if (node->color == RED)
	{
		if (node->left->color == RED || node->right->color == RED)
			return -1;
	}

	int left = _CheckRB(node->left);
	if (left == -1)
		return -1;

	int right = _CheckRB(node->right);
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
