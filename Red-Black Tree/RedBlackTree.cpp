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

void RedBlackTree::FixInsertViolation(Node* node)
{
	if (node->parent->color == BLACK) //�θ� black�� ��� 
	{
		if (node->parent == NIL) { // �ڽ��� root�϶�.
			node->color = BLACK;
			root = node;
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


void RedBlackTree::Delete(int data) {

	Node* nodeToDelete = nullptr;
	Node* nodeToFix = nullptr;
	if (!(nodeToDelete = _SearchNode(root, data))) {
		std::cout << "no matching data" << std::endl;
		return;
	}

	COLOR erasedColor;
	_Delete(nodeToDelete, &nodeToFix, &erasedColor);
	if (nodeToFix)
	{
		if (erasedColor == BLACK)
			FixDeleteViolation(nodeToFix);
	}

	//��� üũ
	if (CheckRB(this)) {
		std::cout << "Delete complete" << std::endl;
	}
	else
	{
		std::cout << "Delete Fail" << std::endl;
	}
}

void RedBlackTree::_Delete(Node* delNode, Node** nodeToFix, COLOR* erasedColor)
{
	if (delNode == nullptr)
		return;

	*erasedColor = delNode->color;
	if (delNode->left == NIL) { // left child�� ���� ���
		*nodeToFix = delNode->right;
		Transplant(this, delNode, delNode->right); // node->right�� NULL�� ��� ����
	}
	else if (delNode->right == NIL) { // left child�� �ְ� right child�� ���� ���
		*nodeToFix = delNode->left;
		Transplant(this, delNode, delNode->left);
	}
	else { // child�� 2���� ���
		Node* sucessor = TreeMinimum(delNode->right);	// right subtree���� �ּҰ� ���
		*erasedColor = sucessor->color;
		*nodeToFix = sucessor->right;
		if (sucessor->parent == delNode)
			(*nodeToFix)->parent = sucessor;
		else
		{
			Transplant(this, sucessor, sucessor->right);
			sucessor->right = delNode->right; // successor�� child ����
			sucessor->right->parent = sucessor; // right child�� �θ� ����
		}
		Transplant(this, delNode, sucessor); // ���⿡�� node �ڸ��� successor �̽�
		sucessor->left = delNode->left; // successor�� left child ����
		sucessor->left->parent = sucessor; // successor�� parent ����
		sucessor->color = delNode->color;
	}
}

void RedBlackTree::FixDeleteViolation(Node* nodeToFix)
{
	if (nodeToFix->parent == NIL || nodeToFix->color == RED)
	{
		nodeToFix->color = BLACK;
	}
	else
	{
		Node* sibling;
		if (nodeToFix == nodeToFix->parent->left)
		{
			sibling = nodeToFix->parent->right;
			if (sibling->color == RED)//sibling�� red�̸� black�� ��Ȳ���� �ٲ۴�.
			{
				sibling->color = BLACK;
				nodeToFix->parent->color = RED;
				LeftRotate(nodeToFix->parent);
				sibling = nodeToFix->parent->right;
			}

			//������ʹ� sibling�� ���� ��츸 ����.
			//nodeToFix�� sibling�� bh���� 1�̹Ƿ�, sibling�� NIL�� �� �� ����.
			if(sibling->left->color == BLACK && sibling->right->color == BLACK)
			{
				sibling->color = RED;
				FixDeleteViolation(nodeToFix->parent);
			}
			else
			{
				if (sibling->right->color == BLACK)
				{
					sibling->left->color = BLACK;
					sibling->color = RED;
					RightRotate(sibling);
					sibling = nodeToFix->parent->right;
				}
				sibling->color = nodeToFix->parent->color;
				nodeToFix->parent->color = BLACK;
				sibling->right->color = BLACK;
				LeftRotate(nodeToFix->parent);

			}
		}
		else
		{
			sibling = nodeToFix->parent->left;
			if (sibling->color == RED)//sibling�� red�̸� black�� ��Ȳ���� �ٲ۴�.
			{
				sibling->color = BLACK;
				nodeToFix->parent->color = RED;
				RightRotate(nodeToFix->parent);
				sibling = nodeToFix->parent->left;
			}

			//������ʹ� sibling�� ���� ��츸 ����.
			//nodeToFix�� sibling�� bh���� 1�̹Ƿ�, sibling�� NIL�� �� �� ����.
			if (sibling->left->color == BLACK && sibling->right->color == BLACK)
			{
				sibling->color = RED;
				FixDeleteViolation(nodeToFix->parent);
			}
			else
			{
				if (sibling->left->color == BLACK)
				{
					sibling->right->color = BLACK;
					sibling->color = RED;
					LeftRotate(sibling);
					sibling = nodeToFix->parent->left;
				}
				sibling->color = nodeToFix->parent->color;
				nodeToFix->parent->color = BLACK;
				sibling->left->color = BLACK;
				RightRotate(nodeToFix->parent);

			}
		}
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


void RedBlackTree::Transplant(RedBlackTree * tree, Node* delNode, Node* plantNode) // �̽ĵ� ���
{
	if (delNode->parent == NIL)  // parent�� NULL�� ���
		tree->root = plantNode;
	
	else if (delNode->parent->left == delNode)
		delNode->parent->left = plantNode;

	else if (delNode->parent->right == delNode)
		delNode->parent->right = plantNode;
	
	plantNode->parent = delNode->parent;
}

Node* RedBlackTree::TreeMinimum(Node* node) {
	if (node->left == NIL)
		return node;
	else
		return TreeMinimum(node->left);
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

	if (root->color != BLACK || root->parent != NIL)
		return false;
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
