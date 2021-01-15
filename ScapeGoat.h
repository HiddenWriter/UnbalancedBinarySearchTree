static int const log32(int _n)
{
	double const log23(2.4663034623764317);
	return (int)std::ceil(log23 * std::log(_n));
}

#pragma once
template <typename T, template <typename T> class N>
class ScapeGoat : public BaseTree<T, N>
{
public:
	
	bool AddItem(T& _item) override;
	
	bool DeleteItem(T& _item) override;

	void Rebuild(N<T>* _u);
	
	int PackIntoArray(N<T>* _u, N<T>** _a, int _i);

	N<T>* BuildBalanced(N<T>** _a, int _i, int _n);

private:

	int q = 0;

};

template <typename T, template <typename T> class N>
bool ScapeGoat<T, N>::AddItem(T& _item)
{
	std::cout << "\n\t\t ScapeGoat Addtion \n";
	N<T>* p = BaseTree<T, N>::FindLastNode(_item);
	N<T>* u = new N<T>[1];
	*u->Data = _item;
	if (BaseTree<T, N>::AddItemToChild(p, u))
	{
		this->mLength++;
		q++;
		int height(BaseTree<T, N>::GetDepthOfNode(u));

		if (height > log32(q))
		{
			while (3 * BaseTree<T, N>::GetSizeOfNode(p) <= 2 * BaseTree<T, N>::GetSizeOfNode(p->parent))
			{
				p = p->parent;
			}
			Rebuild(p);
		}
		
		return true;
	}
	else
	{
		return false;
	}
}

template <typename T, template <typename T> class N>
bool ScapeGoat<T, N>::DeleteItem(T& _item)
{
	std::cout << "\n\t\t ScapeGoat Deletion \n";
	if (BaseTree<T, N>::DeleteItem(_item))
	{
		if (this->mLength < 1) return true;
		if (2 * this->mLength < q)
		{
			Rebuild(this->root);
			q = this->mLength;
		}
		return true;
	}
	return false;
}

template <typename T, template <typename T> class N>
void ScapeGoat<T, N>::Rebuild(N<T>* _u)
{
	int ns(BaseTree<T, N>::GetSizeOfNode(_u));
	N<T>* p = _u->parent;
	N<T>** a = new N<T>*[ns];
	PackIntoArray(_u, a, 0);

	if (p == nullptr)
	{
		this->root = BuildBalanced(a, 0, ns);
		this->root->parent = nullptr;
	}
	else if (p->right == _u)
	{
		p->right = BuildBalanced(a, 0, ns);
		p->right->parent = p;
	}
	else
	{
		p->left = BuildBalanced(a, 0, ns);
		p->left->parent = p;
	}
	delete[] a;

	return;
}


template <typename T, template <typename T> class N>
int ScapeGoat<T, N>::PackIntoArray(N<T>* _u, N<T>** _a, int _i)
{
	if (_u == nullptr)
	{
		return _i;
	}
	
	_i = PackIntoArray(_u->left, _a, _i);
	_a[_i++] = _u;
	return PackIntoArray(_u->right, _a, _i);
}

template <typename T, template <typename T> class N>
N<T>* ScapeGoat<T, N>::BuildBalanced(N<T>** _a, int _i, int _n)
{
	if (_n == 0)
	{
		return nullptr;
	}
	int m = _n / 2;

	_a[_i + m]->left = BuildBalanced(_a, _i, m);

	if (_a[_i + m]->left != nullptr)
	{
		_a[_i + m]->left->parent = _a[_i + m];
	}

	_a[_i + m]->right = BuildBalanced(_a, _i + m + 1, _n - m - 1);

	if (_a[_i + m]->right != nullptr)
	{
		_a[_i + m]->right->parent = _a[_i + m];
	}

	return _a[_i + m];
}

