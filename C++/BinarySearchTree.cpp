#include "pch.h"
#include "BinarySearchTree.h"

using namespace std;


inline void MySetCursorPos(int32 cx, int32 cy)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursorPos = { static_cast<SHORT>(cx), static_cast<SHORT>(cy) };
	::SetConsoleCursorPosition(output, cursorPos);
}

inline COORD MyGetCursorPos()
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	::GetConsoleScreenBufferInfo(output, &csbi);
	return csbi.dwCursorPosition;
}

void BinarySearchTree::Insert(int32 key)
{
	if (!_root)
	{
		_root = make_shared<TNode>(new int{key});
		_root->parent = _root;
		return;
	}

	Insert(key, _root);

}

void BinarySearchTree::Insert(int32 key, NodePtr node)
{
	if (key <= *node->key)
	{
		if(node->left)	Insert(key, node->left);
		else
		{
			node->left = make_shared<TNode>(new int{ key });
			node->left->parent = node;
		}
	}
	else
	{
		if (node->right)	Insert(key, node->right);
		else
		{
			node->right = make_shared<TNode>(new int{ key });
			node->right->parent = node;
		}
	}
}

WNodePtr BinarySearchTree::MinimumNode()
{
	return	Min(_root);
}

WNodePtr BinarySearchTree::Min(NodePtr node)
{
	while (node)
	{
		if (node->left) node = node->left;
		else break;
	}
	return node;
}

WNodePtr BinarySearchTree::MaximumNode()
{
	return Max(_root);
}

WNodePtr BinarySearchTree::NextNode(int32 key)
{
	auto p{ Search(key) };
	if (p.lock()) return Next(p.lock());
	return p;
}

WNodePtr BinarySearchTree::Max(NodePtr node)
{
	while (node)
	{
		if (node->right) node = node->right;
		else break;
	}
	return node;
}

WNodePtr BinarySearchTree::Next(NodePtr node)
{
	if (node->right) return Min(node->right);

	auto parent{ node->parent.lock()};
	while (parent && parent->right == node)
	{
		node = parent;
		parent = node->parent.lock();
	}
	return parent;
}

void BinarySearchTree::Delete(int32 key)
{
	auto p{ Search(key) };
	Delete(p.lock());
}

void BinarySearchTree::Delete(NodePtr node)
{

	if (!node) return;
	
	// 자식 노드가 1개 or 말단 노드
	if (!node->left)
	{
		Replace(node, node->right);
	}
	else if (!node->right) 
	{
		Replace(node, node->left);
	}
	else
	{
		auto next{ Next(node).lock()};
		std::swap(node->key, next->key);
		Delete(next);
	}
	// 노드 자식이 2개
}

// lhs 서브트리를 rhs 서브트리로 교체
void BinarySearchTree::Replace(NodePtr lhs, NodePtr rhs)
{
	auto lparent{ lhs->parent.lock() };
	
	if (!lparent) _root = rhs;
	else if (lhs == lparent->left) // 자신이 왼쪽 자식이였다면
	{
		lparent->left = rhs;
	}
	else
	{
		lparent->right = rhs;
	}
	if (rhs) rhs->parent = lparent;

}

WNodePtr BinarySearchTree::Search(int32 key)
{
	if (*_root->key == key) return _root;

	if (key < *_root->key)
	{
		return Search(key, _root->left);
	}
	else
	{
		return Search(key, _root->right);
	}
}

WNodePtr BinarySearchTree::Search(int32 key, NodePtr node)
{
	if (!node || key == *node->key) return node;

	if (key <= *node->key)
	{
		return Search(key, node->left);
	}
	else
	{
		return Search(key, node->right);
	}
}


void BinarySearchTree::print()
{
	print_inorder(_root, 20, MyGetCursorPos().Y);
}

void BinarySearchTree::print_inorder(NodePtr node, int32 x, int32 y)
{
	MySetCursorPos(x, y);
	cout << *node;

	if (node->left)
	{
		MySetCursorPos(x - 1, y + 1);
		cout << "/";
		print_inorder(node->left, x - 4, y + 2);
	}
	if (node->right)
	{
		MySetCursorPos(x + 4, y + 1);
		cout << R"(\)";
		print_inorder(node->right, x + 3, y + 2);
	}
}
