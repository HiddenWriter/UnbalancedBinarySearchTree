#pragma once
template <typename T>
class Node
{
public:
	Node()
	{
		left = right = parent = nullptr;
		Data = new T[1];
	}
	~Node()
	{
		delete[] Data;
	}
	Node* left;
	Node* right;
	Node* parent;
	T* Data;
};

#pragma once
template <typename T>
class TreapNode
{
public:
	TreapNode()
	{
		left = right = parent = nullptr;
		Data = new T[1];
		pri = -1;
	}
	~TreapNode()
	{
		delete[] Data;
	}
	TreapNode* left;
	TreapNode* right;
	TreapNode* parent;
	T* Data;
	int pri;
};

#pragma once
template <typename T, template<typename T> class N>
class BaseTree
{
public:
	BaseTree()
		: mLength(0)
	{
		root = nullptr;
	}
	~BaseTree() {}
	virtual bool AddItem(T& _item);
	virtual bool DeleteItem(T& _item);
	
	bool SearchItem(T _item);
	void Print() noexcept;
	void PrintTreeSize1() noexcept;
	int GetTreeSize() noexcept;
	void PrintTreeHeight() noexcept;

protected:
	
	void RemoveNode(N<T>* _u);
	N<T>* GetNode(T& _item);
	void Splice(N<T>* _u);
	N<T>* FindSmallest(T& _item);
	N<T>* FindLastNode(T& _item);
	bool AddItemToChild(N<T>* _p, N<T>* _u);
	bool IsFull() const noexcept;
	bool IsEmpty()const noexcept;
	int PrintSizeOfNodeRecursively(N<T>* _u) noexcept;
	int PrintSizeOfNodeNonRecursively() noexcept;
	int PrintHeightOfNodeRecursively(N<T>* _u) noexcept;
	int GetMax(int _x, int _y) const noexcept;
	int GetDepthOfNode(N<T>* _u) noexcept;
	int GetSizeOfNode(N<T>* _u) noexcept;

protected:

	N<T>* root;
	int mLength;
};

// brief		Add the item to the binary tree
/*
*							< Caution >
	the most time-consuming part of this process is the initial search for _item,
	which takes an amount of time proportional to the height of the newly added node, _u.
	In the worst case, this is equal to the heigth of the UnbalancedBST.
*/
template <typename T, template<typename T> class N>
bool BaseTree<T, N>::AddItem(T& _item)
{
	std::cout << "\n\t\t BaseTree Addition \n\n";
	N<T>* p = FindLastNode(_item);
	N<T>* u = new N<T>[1];
	*u->Data = _item;
	if (AddItemToChild(p, u))
	{
		this->mLength++;
		return true;
	}
	else
	{
		return false;
	}
}
template <typename T, template<typename T> class N>
bool BaseTree<T, N>::DeleteItem(T& _item)
{
	std::cout << "\n\t\t BaseTree Deletion \n";
	N<T>* temp = GetNode(_item);
	if (temp == nullptr) return false;
	RemoveNode(temp);
	return true;
}

// Brief		Search the item.
// Param		_item		Item to search
// return		return true if it is found
template <typename T, template<typename T> class N>
bool BaseTree<T, N>::SearchItem(T _item)
{
	N<T>* u = this->root;
	while (u != nullptr)
	{
		if (*u->Data < _item)
		{
			u = u->left;
		}
		else if (*u->Data > _item)
		{
			u = u->right;
		}
		else
		{
			std::cout << u->Data;
			return true;
		}
	}
	return false;
}

template<typename T, template<typename T> class N>
void BaseTree<T, N>::Print() noexcept
{
	if (this->mLength == 0)
	{
		std::cout << "\n Nothing to Print ;( \n";
		return;
	}
	N<T>* u = this->root, * next, * prev = nullptr;
	while (u != nullptr)
	{
		if (prev == u->parent)
		{
			std::cout << *u->Data;
			if (u->left != nullptr)
			{
				next = u->left;
			}
			else if (u->right != nullptr)
			{
				next = u->right;
			}
			else
			{
				next = u->parent;
			}
		}
		else if (prev == u->left)
		{
			if (u->right != nullptr)
			{
				next = u->right;
			}
			else
			{
				next = u->parent;
			}
		}
		else
		{
			next = u->parent;
		}
		prev = u;
		u = next;
	}
	return;

}

// brief		remove node _node in binary tree
/*

	Divide problem into two main section
	First, if the _noed which is needed to be deleteed has one child
	Second, if the _node which is needed to be deleted has two different children

*/
template<typename T, template<typename T> class N>
void BaseTree<T, N>::RemoveNode(N<T>* _node)
{
	// First IF STATEMENT is for the node (_node) which has no more than one child node.
	if (_node->left == nullptr || _node->right == nullptr)
	{
		// In this case, we can just splice it.
		Splice(_node);
		delete[] _node;
	}
	// And this case would be the case that the node which is needed to be deleted
	// has two different children.
	else
	{
		// So as to understand process below, i need to understand the entire structure of the binary tree.
		// Deleting a node from the binary tree with two different children is done by replacing node with 
		// the smallest value in the right subtree of _node.
		N<T>* w = _node->right;
		while (w->left != nullptr)
		{
			w = w->left;
		}
		*_node->Data = *w->Data;
		Splice(w);
		delete[] w;
	}
}

template<typename T, template<typename T> class N>
N<T>* BaseTree<T, N>::GetNode(T& _item)
{
	N<T>* u = this->root;
	while (u != nullptr)
	{
		if (*u->Data < _item)
		{
			u = u->right;
		}
		else if (*u->Data > _item)
		{
			u = u->left;
		}
		else
		{
			return u;
		}
	}
	return nullptr;
}

// brief		Remove parameter _node from the binary tree.
// pre			Only nodes with no more than one child can be received as parameter.
template<typename T, template<typename T> class N>
void BaseTree<T, N>::Splice(N<T>* _u)
{
	// First IF STATEMENT does the process to hold child of the _node( Will be deleted ) 
	// Hold the child node with node 's'
	N<T>* s, * p;
	if (_u->left != nullptr)
	{
		s = _u->left;
	}
	else
	{
		s = _u->right;
	}
	// 
	// Second IF STATEMENT does the process to check whether the _node ( which will be deleted )
	// is root node or not
	// hold parent node of the _node with the node 'p'
	if (_u == this->root)
	{
		this->root = s;
		p = nullptr; //< if the _node is the root node, parent of the root is nullptr.
	}
	// if _node is not the root node, link the node p to the parent of the _node
	// and then with third IF STATEMENT, link the node p to the child node s.
	else
	{
		p = _u->parent;
		if (p->left == _u)
		{
			p->left = s;
		}
		else
		{
			p->right = s;
		}
	}

	// Final IF STATEMENT link the child node s to the parent node p.
	// The reason why for checking whether the child node s is nullptr or not, 
	// it is because it is likely that the binary tree has only one node : The Root.
	if (s != nullptr)
	{
		s->parent = p;
	}
	this->mLength--;
}

template<typename T, template<typename T> class N>
N<T>* BaseTree<T, N>::FindSmallest(T& _item)
{
	N<T>* u = this->root, * z = nullptr;
	while (u != nullptr)
	{
		if (*u->Data > _item)
		{
			z = u;
			u = u->left;
		}
		else if (*u->Data < _item)
		{
			u = u->right;
		}
		else
		{
			return u;
		}
	}
	return z == nullptr ? nullptr : z;
}

// brief		Find last node of this binary tree.
template<typename T, template<typename T> class N>
N<T>* BaseTree<T, N>::FindLastNode(T& _item)
{
	N<T>* w = this->root, * prev = nullptr;
	while (w != nullptr)
	{
		prev = w;
		if (*w->Data < _item)
		{
			w = w->right;
		}
		else if (*w->Data > _item)
		{
			w = w->left;
		}
		else
		{
			return w;
		}
	}
	return prev;
}

template<typename T, template<typename T> class N>
bool BaseTree<T, N>::AddItemToChild(N<T>* _p, N<T>* _u)
{
	if (_p == nullptr)
	{
		this->root = _u;
	}
	else
	{
		if (*_p->Data < *_u->Data)
		{
			_p->right = _u;
		}
		else if (*_p->Data > * _u->Data)
		{
			_p->left = _u;
		}
		else
		{
			return false;
		}
		_u->parent = _p;
	}
	return true;
}

template<typename T, template<typename T> class N>
bool BaseTree<T,N>::IsFull() const noexcept
{
	if (mLength > 9) return true;
	else return false;
}

template<typename T, template<typename T> class N>
bool BaseTree<T, N>::IsEmpty() const noexcept
{
	if (mLength == 0) return true;
	else return false;
}

template<typename T, template<typename T> class N>
void BaseTree<T, N>::PrintTreeSize1() noexcept
{
	int size(PrintSizeOfNodeNonRecursively());
	std::cout <<
		"\t Node Size ( Non-Recursively Calculated )  :  " << size << "\n";
	return;
}

template <typename T, template<typename T> class N>
int BaseTree<T, N>::GetTreeSize() noexcept
{
	int size(PrintSizeOfNodeRecursively(this->root));
	return size;
}

template <typename T, template<typename T> class N>
void BaseTree<T, N>::PrintTreeHeight() noexcept
{
	int height(PrintHeightOfNodeRecursively(this->root));
	std::cout <<
		"\t Height Of the Node ( Recursively Calculated )  :  " << height << "\n";
	return;
}

template <typename T, template<typename T> class N>
int BaseTree<T, N>::PrintSizeOfNodeNonRecursively() noexcept
{
	int cnt(0);
	N<T>* u = this->root, * next, * prev = nullptr;
	while (u != nullptr)
	{
		if (prev == u->parent)
		{
			cnt++;
			if (u->left != nullptr)
			{
				next = u->left;
			}
			else if (u->right != nullptr)
			{
				next = u->right;
			}
			else
			{
				next = u->parent;
			}
		}
		else if (prev == u->left)
		{
			if (u->right != nullptr)
			{
				next = u->right;
			}
			else
			{
				next = u->parent;
			}
		}
		else
		{
			next = u->parent;
		}
		prev = u;
		u = next;
	}
	return cnt;
}

template <typename T, template<typename T> class N>
int BaseTree<T, N>::PrintSizeOfNodeRecursively(N<T>* _u) noexcept
{
	if (_u == nullptr)
	{
		return 0;
	}
	else
	{
		return 1 + PrintSizeOfNodeRecursively(_u->left) + PrintSizeOfNodeRecursively(_u->right);
	}
}

template <typename T, template<typename T> class N>
int BaseTree<T, N>::PrintHeightOfNodeRecursively(N<T>* _u) noexcept
{
	if (_u == nullptr)
	{
		return -1;
	}
	else
	{
		return 1 + GetMax(PrintHeightOfNodeRecursively(_u->left), PrintHeightOfNodeRecursively(_u->right) );
	}
}

template <typename T, template<typename T> class N>
int BaseTree<T, N>::GetMax(int _x, int _y) const noexcept
{
	if (_x > _y) return _x;
	else if (_x < _y) return _y;
	else return _x;
}

template <typename T, template <typename T> class N>
int BaseTree<T, N>::GetDepthOfNode(N<T>* _u) noexcept
{
	int dep(0);
	N<T>* ptr = _u;
	while (ptr != this->root)
	{
		dep++;
		ptr = ptr->parent;
	}
	return dep;
}

template <typename T, template <typename T> class N>
int BaseTree<T, N>::GetSizeOfNode(N<T>* _u) noexcept
{
	if (_u == nullptr)
	{
		return 0;
	}
	else
	{
		return 1 + GetSizeOfNode(_u->left) + GetSizeOfNode(_u->right);
	}
}
