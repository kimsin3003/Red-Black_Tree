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

	//결과 체크
	if (CheckRB(this)) {
		std::cout << "Insert complete" << std::endl;
	}
	else
	{
		std::cout << "Insert Fail" << std::endl;
	}
}


//중복 값이 없다고 보고 짰습니다.
void RedBlackTree::Delete(int data) {

	Node* nodeToDelete = nullptr;

	if (!(nodeToDelete = _SearchNode(root, data))) {
		std::cout << "no matching data" << std::endl;
		return;
	}
	_Delete(root, data);
	FixDeleteViolation(nodeToDelete);

	//결과 체크
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

	if (curNode->left == NIL) // left child가 없는 경우
		Transplant(this, curNode, curNode->right); // node->right가 NULL인 경우 포함
	else if (curNode->right == NIL) // left child는 있고 right child가 없는 경우
		Transplant(this, curNode, curNode->left);
	else { // child가 2개인 경우
		successor = TreeMinimum(curNode->right); // right subtree에서 최소값 노드
		if (curNode->right != successor) {
			Transplant(this, successor, successor->right);
			successor->right = curNode->right; // successor의 child 지정
			successor->right->parent = successor; // right child의 부모 지정
		}
		Transplant(this, curNode, successor); // 여기에서 node 자리에 successor 이식
		successor->left = curNode->left; // successor의 left child 지정
		successor->left->parent = successor; // successor의 parent 지정
	}

}

void RedBlackTree::Transplant(RedBlackTree * tree, Node* delNode, Node* plantNode) // 이식될 노드
{
	if (delNode->parent == NIL) { // parent가 NULL인 경우
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
	if (node->parent->color == BLACK) //부모가 black인 경우 
	{
		if (node->parent == NIL) { // 자신이 root일때.
			node->color = BLACK;
			return;
		}
	}
	else
	{
		Node* grandParent = node->parent->parent;
		if (grandParent->left == node->parent) // 부모가 GP의 leftchild인 경우
		{
			
			if (grandParent->right->color == BLACK) // uncle이 black이면 
			{
				
				if (node->parent->right == node)// 현재 노드가 rightchild이면
				{
					node = node->parent;
					LeftRotate(node);

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
				FixInsertViolation(grandParent);
			}

		}
		else// // 부모가 GP의 rightchild인 경우
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
