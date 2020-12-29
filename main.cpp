#include <iostream>

class SimpleData
{
public:
	SimpleData()
		: mID(0),mName("STRING")
	{}
	SimpleData(int _id, std::string _name)
		: mID(_id), mName(_name)
	{}
	std::string GetName() const noexcept
	{
		return this->mName;
	}
	int GetID() const noexcept
	{
		return this->mID;
	}
	void SetID(int _id)
	{
		mID = _id;
		return;
	}
	void SetName(std::string _name)
	{
		mName = _name;
		return;
	}
	void PrintDataInfo() const noexcept
	{
		std::cout <<
			"\t ID   : " << this->mID << "\n"
			"\t NAME : " << this->mName << "\n";
		return;
	}
public:
	bool operator>(const SimpleData& _data)
	{
		if (this->mID > _data.mID) return true;
		else return false;
	}
	bool operator>=(const SimpleData& _data)
	{
		if (this->mID >= _data.mID) return true;
		else return false;
	}
	bool operator<(const SimpleData& _data)
	{
		if (this->mID < _data.mID) return true;
		else return false;
	}
	bool operator<=(const SimpleData& _data)
	{
		if (this->mID <= _data.mID) return true;
		else return false;
	}
	bool operator==(const SimpleData& _data)
	{
		if (this->mID == _data.mID) return true;
		else return false;
	}

	friend std::ostream& operator<<(std::ostream& _os, const SimpleData& _data)
	{
		std::cout <<
			"\t ID    : " << _data.mID << "\n"
			"\t Name  : " << _data.mName << "\n";
		return _os;
	}
protected:
	std::string mName;
	int mID;
};

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

class BinaryTree
{
public:
	BinaryTree()
		: mLength(0)
	{
		root = nullptr;
	}
	BinaryTree(const BinaryTree&) = delete;
	void operator=(const BinaryTree&) = delete;
	~BinaryTree()
	{
		return;
	}
	// Brief		Search the item.
	// Param		_item		Item to search
	// return		return true if it is found
	bool SearchItem(SimpleData _item)
	{
		Node<SimpleData>* u = this->root;
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
	
	// brief		Add the item to the binary tree
	/*
	*							< Caution >
		the most time-consuming part of this process is the initial search for _item,
		which takes an amount of time proportional to the height of the newly added node, _u.
		In the worst case, this is equal to the heigth of the BinaryTree.
	*/
	bool AddItem(SimpleData& _item)
	{
		Node<SimpleData>* p = FindLastNode(_item);
		Node<SimpleData>* u = new Node<SimpleData>[1];
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

	bool DeleteItem(SimpleData& _item)
	{
		Node<SimpleData>* temp = GetNode(_item);
		if (temp == nullptr) return false;
		RemoveNode(temp);
		return true;
	}

	void Traverse1()
	{
		Node<SimpleData>* u = this->root, * next, * prev = nullptr;
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

	void Traverse2() const noexcept
	{
		
	}

	void PrintTreeSize1() const noexcept
	{
		int size(PrintSizeOfNodeNonRecursively());
		std::cout <<
			"\t Node Size ( Non-Recursively Calculated )  :  " << size << "\n";
		return;
	}

	void PrintTreeSize2() const noexcept
	{
		int size(PrintSizeOfNodeRecursively(this->root));
		std::cout << 
			"\t Node Size ( Recursively Calculated )  :  "  << size << "\n";
		return;
	}

	void PrintTreeHeight() noexcept
	{
		int height(PrintHeightOfNodeRecursively(this->root));
		std::cout <<
			"\t Height Of the Node ( Recursively Calculated )  :  " << height << "\n";
		return;
	}

private:

	void TraverseRecursively(Node<SimpleData>* _u)
	{
		if (_u == nullptr) return;
		else
		{
			TraverseRecursively(_u->left);
			TraverseRecursively(_u->right);
			return;
		}
	}

	// brief		remove node _node in binary tree
	/*
	
		Divide problem into two main section
		First, if the _noed which is needed to be deleteed has one child
		Second, if the _node which is needed to be deleted has two different children

	*/
	void RemoveNode(Node<SimpleData>* _node)
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
			Node<SimpleData>* w = _node->right;
			while (w->left != nullptr)
			{
				w = w->left;
			}
			*_node->Data = *w->Data;
			Splice(w);
			delete[] w;
		}
	}

	Node<SimpleData>* GetNode(SimpleData& _item)
	{
		Node<SimpleData>* u = this->root;
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
	void Splice(Node<SimpleData>* _u)
	{
		// First IF STATEMENT does the process to hold child of the _node( Will be deleted ) 
		// Hold the child node with node 's'
		Node<SimpleData>* s, * p;
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

	Node<SimpleData>* FindSmallest(SimpleData& _item)
	{
		Node<SimpleData>* u = this->root, * z = nullptr;
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
	Node<SimpleData>* FindLastNode(SimpleData& _item)
	{
		Node<SimpleData>* w = this->root, * prev = nullptr;
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

	bool AddItemToChild(Node<SimpleData>* _p, Node<SimpleData>* _u)
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

	int PrintSizeOfNodeNonRecursively() const noexcept
	{
		int cnt(0);
		Node<SimpleData>* u = this->root, * next, * prev = nullptr;
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

	int PrintSizeOfNodeRecursively(Node<SimpleData>* _u) const noexcept
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

	int PrintHeightOfNodeRecursively(Node<SimpleData>* _u) const noexcept
	{
		if (_u == nullptr)
		{
			return -1;
		}
		else
		{
			return 1 + std::max(PrintHeightOfNodeRecursively(_u->left), PrintHeightOfNodeRecursively(_u->right));
		}
	}

	bool IsFull() const noexcept
	{
		if (mLength > 9) return true;
		else return false;
	}

	bool IsEmpty() const noexcept
	{
		if (mLength == 0) return true;
		else return false;
	}

private:
	Node<SimpleData>* root;
	int mLength;
};

class Application
{
public:
	Application()
		: mCommand(-1)
	{}
	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;
	~Application() = default;

public:
	void Run()
	{
		std::cout << "\t Basic Unbalanced Binary Search Tree \n\n\n";
		bool isDone(true);
		while (isDone)
		{
			std::cout <<
				"\t-----------------------------------------------\n" <<
				"\|\t Press number. \n\n" <<
				"\|\t 1 : Add Item \n" <<
				"\|\t 2 : Delete Item \n" <<
				"\|\t 3 : Print Item ( Non-Recursive ) \n" <<
				"\|\t 4 : Show the Height of this binary tree \n"
				"\|\t 5 : Show the Size of the Binary tree \n" <<
				"\|\t 0 : Exit Programme. \n" <<
				"\t-----------------------------------------------\n";
			std::cin >> mCommand;
			switch (mCommand)
			{
			case 1:
				Add();
				break;
			case 2:
				Delete();
				break;
			case 3:
				Print();
				break;
			case 4:
				Height();
				break;
			case 5:
				ShowSize();
				break;
			case 0:
				isDone = false;
				break;
			default:
				break;
			}
		}
	}
	void Add()
	{
		int id(0);
		std::string name("");
		std::cout <<
			"\t ID    : ";
		std::cin >> id;
		std::cout <<
			"\t Name  : ";
		std::cin >> name;
		SimpleData sd(id, name);
		if (bt->AddItem(sd))
		{
			std::cout <<
				"\t Successfully done. \n";
		}
		else
		{
			std::cout <<
				"\t Error \n";
		}
		return;
	}

	void Delete()
	{
		int id(0);
		std::cout <<
			"\t ID    : ";
		std::cin >> id;
		SimpleData sd(id, "Default");
		if (bt->DeleteItem(sd))
		{
			std::cout <<
				"\t Successfully done. \n";
		}
		else
		{
			std::cout <<
				"\t Error \n";
		}
		return;
	}

	void Print() const noexcept
	{
		bt->Traverse2();
		return;
	}
	
	void Height() const noexcept
	{
		bt->PrintTreeHeight();
		return;
	}

	void ShowSize() const noexcept
	{
		bt->PrintTreeSize1();
		return;
	}
private:

	std::unique_ptr<BinaryTree> bt = std::make_unique<BinaryTree>();
	int mCommand;
};
int main(void)
{
	std::unique_ptr<Application> app = std::make_unique<Application>();
	app->Run();
	return 0;
}