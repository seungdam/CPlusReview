#pragma once

struct TNode
{
	int32* key;
	std::weak_ptr<TNode> parent;
	std::shared_ptr<TNode> left{ nullptr };
	std::shared_ptr<TNode> right{ nullptr };
	TNode(int32* pkey) : key(pkey) {};
	~TNode() { std::cout << "\033[38;5;22mDeleted.. \033[0m" << *key << "\n"; delete key; }

	inline friend std::ostream& operator<<(std::ostream& os, const TNode& rhs)
	{
		std::cout << std::format("[{}]", *(rhs.key));
		return os;
	}
};

using NodePtr = std::shared_ptr<TNode>;
using WNodePtr = std::weak_ptr<TNode>;

class BinarySearchTree
{
	
	NodePtr _root{ nullptr };

public:
	void Insert(int32 key);
	void Insert(int32 key, NodePtr node);
public:
	WNodePtr MinimumNode();
	WNodePtr MaximumNode();
	WNodePtr NextNode(int32 key);
private:
	WNodePtr Min(NodePtr node);
	WNodePtr Max(NodePtr node);
	WNodePtr Next(NodePtr node);
public:
	void Delete(int32 key);
	void Delete(NodePtr node);
	void Replace(NodePtr lhs, NodePtr rhs);
public:
	WNodePtr Search(int32 key);
	WNodePtr Search(int32 key, NodePtr node);
public:
	void print();
	void print_inorder(NodePtr node, int32 x, int32 y);

};

