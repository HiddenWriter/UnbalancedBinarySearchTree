#pragma once
template <typename T, template<typename T> class N>
class Treap : public BaseTree<T, N>
{
public:
	
	void RotationLeft(N<T>* _u);
	void RotationRight(N<T>* _u);

	bool AddItem(T& _item) override;
	bool DeleteItem(T& _item) override;

private:

	void BubbleUp(N<T>* _u);
	void TrickleDown(N<T>* _u);

};

template <typename T, template<typename T> class N>
void Treap<T, N>::RotationLeft(N<T>* _u)
{
	N<T>* w = _u->right;
	w->parent = _u->parent;
	if(w->parent != nullptr)
	{
		if (w->parent->left == _u)
		{
			w->parent->left = w;
		}
		else
		{
			w->parent->right = w;
		}
	}

	_u->right = w->left;
	if (_u->right != nullptr)
	{
		_u->right->parent = _u;
	}

	_u->parent = w;
	w->left = _u;
	if (_u == this->root)
	{
		this->root = w;
		this->root->parent = nullptr;
	}

	return;
}

template <typename T, template<typename T> class N>
void Treap<T, N>::RotationRight(N<T>* _u)
{
	N<T>* w = _u->left;
	w->parent = _u->parent;

	if (w->parent != nullptr)
	{
		if (w->parent->left == _u)
		{
			w->parent->left = w;
		}
		else
		{
			w->parent->right = w;
		}
	}

	_u->left = w->right;

	if (_u->left != nullptr)
	{
		_u->left->parent = _u;
	}
	_u->parent = w;
	w->right = _u;

	if (_u == this->root)
	{
		this->root = w;
		this->root->parent = nullptr;
	}
	
	return;
}

template <typename T, template <typename T> class N>
bool Treap<T, N>::AddItem(T& _item)
{
	N<T>* p = BaseTree<T, N>::FindLastNode(_item);
	N<T>* u = new N<T>[1];
	*u->Data = _item;
	u->pri = std::rand() % 100;

	if (BaseTree<T, N>::AddItemToChild(p, u))
	{
		BubbleUp(u);
		this->mLength++;
		return true;
	}
	else
	{
		delete[] u;
		return false;
	}
}

template <typename T, template <typename T> class N>
bool Treap<T, N>::DeleteItem(T& _item)
{
	N<T>* u = BaseTree<T, N>::FindLastNode(_item);
	if (u != nullptr && *u->Data == _item)
	{
		TrickleDown(u);
		BaseTree<T, N>::Splice(u);
		delete[] u;
		return true;
	}
	return false;
}

template <typename T, template <typename T> class N>
void Treap<T, N>::BubbleUp(N<T>* _u)
{
	while (_u->parent != nullptr && _u->parent->pri > _u->pri)
	{
		if (_u->parent->right == _u)
		{
			RotationLeft(_u->parent);
		}
		else
		{
			RotationRight(_u->parent);
		}
	}
	if (_u->parent == nullptr)
	{
		this->root = _u;
	}

	return;
}

template <typename T, template <typename T> class N>
void Treap<T, N>::TrickleDown(N<T>* _u)
{
	while (_u->left != nullptr || _u->right != nullptr)
	{
		if (_u->left == nullptr)
		{
			RotationLeft(_u);
		}
		else if (_u->right == nullptr)
		{
			RotationRight(_u);
		}
		else if (_u->left->pri < _u->right->pri)
		{
			RotationRight(_u);
		}
		else
		{
			RotationLeft(_u);
		}
	}
	return;
}
