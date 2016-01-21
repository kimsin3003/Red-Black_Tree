#pragma once
class RedBlackTree
{
public:
	RedBlackTree();
	~RedBlackTree();

	void Insert(int data);
	bool CheckRB(RedBlackTree* rb);
private:
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

	void RightRotate(Node* node);
	void LeftRotate(Node* node);

	void _Insert(Node* curNode, Node* newNode);
	void FixViolation(Node* node);

	int CountBlack(Node* node);
	Node* root;
	Node* NIL;
};

