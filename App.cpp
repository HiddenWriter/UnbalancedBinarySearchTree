#include "pch.h"
#include "App.h"
App::~App()
{
	
}
void App::Run()
{
	bool s(false);
	while (true)
	{
		while (!s)
		{

			std::cout <<
				"\t-----------------------------------------------\n" <<
				"\t Press button \n" <<
				"\t 1. Unbalanced Binary Search Tree \n" <<
				"\t 2. Treap \n" <<
				"\t 3. ScapeGoat \n"
				"\t 4. Red-Black Tree \n"
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
			case 3:
				vt = new ScapeGoat<SimpleData, Node>[1];
				GetType() = TYPE::SCAPEGOAT;
				s = true;
				break;
			case 4:
				vt = new RedBlackTree<SimpleData, RBTNode>[1];
				GetType() = TYPE::RBT;
				s = true;
				break;
			case 0:
				return;
			default:
				break;
			}
		}
		mCommand = -1;
		std::cout << "\t Basic Binary Search Tree Practice \n\n\n";
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
				"\|\t 9 : Exit Programme. \n"
				"\|\t 0 : Return to Select Menu. \n" <<
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
			case 9:
				Destroy();
				return;
			case 0:
				s = false;
				isDone = false;
				Destroy();
				break;
			default:
				break;
			}
		}
	}
}

void App::Add()
{
	std::pair<std::string, std::string> msg =
	{
		"\t Successfully Done. \n", "\t Error \n"
	};
	bool sux(false);
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
		if (static_cast<BaseTree<SimpleData, TreapNode>*>(vt)->AddItem(sd)) sux = true;
	}
	else if (GetType() == TYPE::UnBalBST)
	{
		if (static_cast<BaseTree<SimpleData, Node>*>(vt)->AddItem(sd)) sux = true;
	}
	else if (GetType() == TYPE::SCAPEGOAT)
	{
		if (static_cast<BaseTree<SimpleData, Node>*>(vt)->AddItem(sd)) sux = true;
	}
	else if (GetType() == TYPE::RBT)
	{
		if (static_cast<BaseTree<SimpleData, RBTNode>*>(vt)->AddItem(sd)) sux = true;
	}

	if (sux)
	{
		std::cout << msg.first;
	}
	else
	{
		std::cout << msg.second;
	}
	return;
}

void App::Delete()
{
	int id(0);
	std::pair<std::string, std::string> msg =
	{
		"\t Successfully Done. \n", "\t Error \n"
	};
	bool sux(false);
	std::cout <<
		"\t ID    : ";
	std::cin >> id;
	SimpleData sd(id, "Default");
	if (GetType() == TYPE::UnBalBST)
	{
		if (static_cast<BaseTree<SimpleData, Node>*>(vt)->DeleteItem(sd)) sux = true;
	}
	else if (GetType() == TYPE::Treap)
	{
		if (static_cast<BaseTree<SimpleData, TreapNode>*>(vt)->DeleteItem(sd)) sux = true;
	}
	else if (GetType() == TYPE::SCAPEGOAT)
	{
		if (static_cast<BaseTree<SimpleData, Node>*>(vt)->DeleteItem(sd)) sux = true;
	}
	else if (GetType() == TYPE::RBT)
	{
		if (static_cast<BaseTree<SimpleData, RBTNode>*>(vt)->DeleteItem(sd)) sux = true;
	}
	if (sux)
	{
		std::cout << msg.first;
	}
	else 
	{
		std::cout << msg.second;
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
	else if (GetType() == TYPE::SCAPEGOAT)
	{
		static_cast<BaseTree<SimpleData, Node>*>(vt)->Print();
	}
	else if (GetType() == TYPE::RBT)
	{
		static_cast<BaseTree<SimpleData, RBTNode>*>(vt)->Print();
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
	else if (GetType() == TYPE::SCAPEGOAT)
	{
		static_cast<BaseTree<SimpleData, Node>*>(vt)->PrintTreeHeight();
	}
	else if (GetType() == TYPE::RBT)
	{
		static_cast<BaseTree<SimpleData, RBTNode>*>(vt)->PrintTreeHeight();
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
	else if (GetType() == TYPE::SCAPEGOAT)
	{
		static_cast<BaseTree<SimpleData, Node>*>(vt)->PrintTreeSize1();
	}
	else if (GetType() == TYPE::RBT)
	{
		static_cast<BaseTree<SimpleData, RBTNode>*>(vt)->PrintTreeSize1();
	}
	return;
}

TYPE& App::GetType(void) noexcept
{
	static TYPE type(TYPE::UNKNOWN);
	return type;
}

void App::Destroy()
{
	switch (GetType())
	{
	case TYPE::UnBalBST:
		delete[] static_cast<BaseTree<SimpleData, Node>*>(vt);
		break;
	case TYPE::Treap:
		delete[] static_cast<BaseTree<SimpleData, TreapNode>*>(vt);
		break;
	case TYPE::SCAPEGOAT:
		delete[] static_cast<BaseTree<SimpleData, Node>*>(vt);
		break;
	case TYPE::RBT:
		delete[] static_cast<BaseTree<SimpleData, RBTNode>*>(vt);
		break;
	default:
		break;
	}
}
