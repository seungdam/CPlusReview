#include "pch.h"
#include "BinarySearchTree.h"


int main()
{
	BinarySearchTree bst;
	bst.Insert(20);
	bst.Insert(10);
	bst.Insert(30);
	bst.Insert(24);
	bst.Insert(25);
	bst.Insert(22);
	bst.Insert(40);
	bst.Insert(50);
	bst.print();
	std::cout << "\n";

	auto retval{ std::weak_ptr<TNode>{bst.Search(40)} };
	std::cout << (retval.lock() ? "True\n" : "False\n");

	std::cout << *(bst.MaximumNode().lock()) << "is Max Node\n";
	std::cout << *(bst.MinimumNode().lock()) << "is Min Node\n";

	auto next{ bst.NextNode(20) };
	if(next.lock()) std::cout << *next.lock() << " is Next Key of 20\n";

	bst.Delete(30);
	bst.print();
	
}