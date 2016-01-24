#pragma once

typedef enum color {
	BLACK = 0,
	RED = 1
}COLOR;
typedef struct _Node
{
	struct _Node* left;
	struct _Node* right;
	struct _Node* parent;
	COLOR color;
	int data;
}Node;

class RedBlackTree
{
public:
	RedBlackTree();
	~RedBlackTree();

	void Insert(int data);
	void Delete(int data);
	Node* SearchData(int data);
	bool CheckRB(RedBlackTree* rb);
private:

	void RightRotate(Node* node);
	void LeftRotate(Node* node);

	void _Insert(Node* curNode, Node* newNode);
	void FixInsertViolation(Node* node);

	void _Delete(Node* delNode, Node** nodeToFix, COLOR* erasedColor);
	void FixDeleteViolation(Node* nodeToFix);

	void Transplant(RedBlackTree * tree, Node* delNode, Node* plantNode);
	Node* TreeMinimum(Node* node);

	Node* _SearchNode(Node* curNode, int data);

	int _CheckRB(Node* node);
	Node* root;
	Node* NIL;
};

