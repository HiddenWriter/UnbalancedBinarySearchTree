#include "pch.h"
#include "App.h"
App::~App()
{
	
}
void App::Run()
{
	bool s(false);
	while (!s)
	{
		std::cout <<
			"\t-----------------------------------------------\n" <<
			"\t Press button \n" <<
			"\t 1. Unbalanced Binary Search Tree \n" <<
			"\t 2. Treap \n" <<
			"\t 0. Exit \n" <<
			"\t-----------------------------------------------\n" <<
			"\t : ";
		std::cin >> mCommand;
		switch (mCommand)
		{
		case 1:
			vt = new BaseTree<SimpleData, Node>[1];
			GetType() = TYPE::UnBalBST;
			s = true;
			break;
		case 2:
			vt = new Treap<SimpleData, TreapNode>[1];
			GetType() = TYPE::Treap;
			s = true;
			break;
		case 0:
			return;
		default:
			break;
		}
	}
	s = false;
	mCommand = -1;
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

void App::Add()
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
	if (GetType() == TYPE::Treap)
	{
		if (static_cast<BaseTree<SimpleData, TreapNode>*>(vt)->AddItem(sd))
		{
			std::cout <<
				"\t Successfully done. \n";
		}
		else
		{
			std::cout <<
				"\t Error \n";
		}
	}
	else if (GetType() == TYPE::UnBalBST)
	{
		if (static_cast<BaseTree<SimpleData, Node>*>(vt)->AddItem(sd))
		{
			std::cout <<
				"\t Successfully done. \n";
		}
		else
		{
			std::cout <<
				"\t Error \n";
		}
	}
	return;
}

void App::Delete()
{
	int id(0);
	std::cout <<
		"\t ID    : ";
	std::cin >> id;
	SimpleData sd(id, "Default");
	if (GetType() == TYPE::UnBalBST)
	{
		if (static_cast<BaseTree<SimpleData, Node>*>(vt)->DeleteItem(sd))
		{
			std::cout <<
				"\t Successfully done. \n";
		}
		else
		{
			std::cout <<
				"\t Error \n";
		}
	}
	else if (GetType() == TYPE::Treap)
	{
		if (static_cast<BaseTree<SimpleData, TreapNode>*>(vt)->DeleteItem(sd))
		{
			std::cout <<
				"\t Successfully done. \n";
		}
		else
		{
			std::cout <<
				"\t Error \n";
		}
	}
	return;
}

void App::Print() noexcept
{
	if (GetType() == TYPE::UnBalBST)
	{
		static_cast<BaseTree<SimpleData, Node>*>(vt)->Print();
	}
	else if (GetType() == TYPE::Treap)
	{
		static_cast<BaseTree<SimpleData, TreapNode>*>(vt)->Print();
	}
	return;
}

void App::Height() noexcept
{
	if (GetType() == TYPE::UnBalBST)
	{
		static_cast<BaseTree<SimpleData, Node>*>(vt)->PrintTreeHeight();
	}
	else if (GetType() == TYPE::Treap)
	{
		static_cast<BaseTree<SimpleData, TreapNode>*>(vt)->PrintTreeHeight();
	}
	return;
}

void App::ShowSize() noexcept
{
	if (GetType() == TYPE::UnBalBST)
	{
		static_cast<BaseTree<SimpleData, Node>*>(vt)->PrintTreeSize1();
	}
	else if (GetType() == TYPE::Treap)
	{
		static_cast<BaseTree<SimpleData, TreapNode>*>(vt)->PrintTreeSize1();
	}
	return;
}

TYPE& App::GetType(void) noexcept
{
	static TYPE type(TYPE::UNKNOWN);
	return type;
}
