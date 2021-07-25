#pragma once
template <typename T, template <typename T> class N>
class RedBlackTree : public BaseTree<T, N>
{
public:
	
	RedBlackTree<T, N>()
	{
		nil = new N<T>[1];
		nil->colour = black;
		this->root = nil;
	}
	bool AddItem(T& _item) override;
	bool DeleteItem(T& _item) override;

private:

	void RemoveFixUp(N<T>* _u);
	void AddFixUp(N<T>* _u);
	void PushBlack(N<T>* _u);
	void PullBlack(N<T>* _u);
	void RotateLeft(N<T>* _u);
	void RotateRight(N<T>* _u);
	void FlipLeft(N<T>* _u);
	void FlipRight(N<T>* _u);
	void SwapColours(N<T>* _x, N<T>* _y) noexcept;
	N<T>* RemoveFixUpCase1(N<T>* _u);
	N<T>* RemoveFixUpCase2(N<T>* _u);
	N<T>* RemoveFixUpCase3(N<T>* _u);

private:
	
	using BaseTree<T, N>::nil;
	const int red = 0;
	const int black = 1;
};

template <typename T, template <typename T> class N>
bool RedBlackTree<T, N>::AddItem(T& _item)
{
	N<T>* u = new N<T>[1];
	*u->Data = _item;
	u->colour = red;
	u->left = u->right = u->parent = nil;
	N<T>* p = BaseTree<T, N>::FindLastNode(_item);
	if (BaseTree<T, N>::AddItemToChild(p, u))
	{
		this->mLength++;
		AddFixUp(u);
		return true;
	}
	else
	{
		delete[] u;
		return false;
	}
}

template <typename T, template <typename T> class N>
bool RedBlackTree<T, N>::DeleteItem(T& _item)
{
	N<T>* u = BaseTree<T, N>::FindLastNode(_item);
	if (u == nil || *u->Data != _item)
	{
		return false;
	}

	N<T>* w = u->right;
	// Now, node w points what used to node u pointed
	// u points u->left
	if (w == nil)
	{
		w = u;
		u = w->left;
	}
	else
	{
		while (w->left != nil)
		{
			w = w->left;
		}
		*u->Data = *w->Data;
		u = w->right;
	}

	BaseTree<T, N>::Splice(w);
	u->colour += w->colour;
	u->parent = w->parent;
	delete[] w;
	RemoveFixUp(u);
	return true;
}

// param		_x cannot be a null-pointer
// param		_y another node to swap colour
template <typename T, template <typename T> class N>
void RedBlackTree<T, N>::SwapColours(N<T>* _x, N<T>* _y) noexcept
{
	char temp(_x->colour);
	_x->colour = _y->colour;
	_y->colour = temp;
	return;
}

template <typename T, template <typename T> class N>
void RedBlackTree<T, N>::PushBlack(N<T>* _u)
{
	_u->colour--;
	_u->left->colour++;
	_u->right->colour++;
	return;
}

template <typename T, template <typename T> class N>
void RedBlackTree<T, N>::PullBlack(N<T>* _u)
{
	_u->colour++;
	_u->left->colour--;
	_u->right->colour--;
	return;
}

template <typename T, template <typename T> class N>
void RedBlackTree<T, N>::RotateLeft(N<T>* _u)
{
	N<T>* w = _u->right;
	w->parent = _u->parent;
	if (w->parent != nil)
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
	if (_u->right != nil)
	{
		_u->right->parent = _u;
	}

	_u->parent = w;
	w->left = _u;
	if (_u == this->root)
	{
		this->root = w;
		this->root->parent = nil;
	}

	return;
}

template <typename T, template <typename T> class N>
void RedBlackTree<T, N>::RotateRight(N<T>* _u)
{
	N<T>* w = _u->left;
	w->parent = _u->parent;
	if (w->parent != nil)
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
	if (_u->left != nil)
	{
		_u->left->parent = _u;
	}
	
	_u->parent = w;
	w->right = _u;
	if (_u == this->root)
	{
		this->root = w;
		this->root->parent = nil;
	}
	return;
}

template <typename T, template <typename T> class N>
void RedBlackTree<T, N>::FlipLeft(N<T>* _u)
{
	SwapColours(_u, _u->right);
	RotateLeft(_u);
	return;
}

template <typename T, template <typename T> class N>
void RedBlackTree<T, N>::FlipRight(N<T>* _u)
{
	SwapColours(_u, _u->left);
	RotateRight(_u);
	return;
}

template <typename T, template <typename T> class N>
void RedBlackTree<T, N>::AddFixUp(N<T>* _u)
{
	while (_u->colour == red)
	{
		if (_u == this->root)
		{
			_u->colour = black;
			return;
		}
		N<T>* w = _u->parent;

		if (w->left->colour == black )
		{
			FlipLeft(w);
			_u = w;
			w = _u->parent;
		}
		if (w->colour == black)
		{
			return;
		}
		N<T>* g = w->parent;
		if (g->right->colour == black)
		{
			FlipRight(g);
			return;
		}
		else
		{
			PushBlack(g);
			_u = g;
		}
	}
}

template <typename T, template <typename T> class N>
void RedBlackTree<T, N>::RemoveFixUp(N<T>* _u)
{
	while (_u->colour > black)
	{
		if (_u == this->root)
		{
			_u->colour = black;
		}
		else if (_u->parent->left->colour == red)
		{
			_u = RemoveFixUpCase1(_u);
		}
		else if (_u == _u->parent->left)
		{
			_u = RemoveFixUpCase2(_u);
		}
		else
		{
			_u = RemoveFixUpCase3(_u);
		}
	}

	if (_u != this->root)
	{
		N<T>* w = _u->parent;
		if (w->right->colour == red && w->left->colour == black)
		{
			FlipLeft(w);
		}
	}

	return;
}

template <typename T, template <typename T> class N>
N<T>* RedBlackTree<T, N>::RemoveFixUpCase1(N<T>* _u)
{
	FlipRight(_u->parent);
	return _u;
}

template <typename T, template <typename T> class N>
N<T>* RedBlackTree<T, N>::RemoveFixUpCase2(N<T>* _u)
{
	N<T>* w = _u->parent;
	N<T>* v = w->right;
	PullBlack(w);
	FlipLeft(w);
	N<T>* q = w->right;

	if (q->colour == red)
	{
		RotateLeft(w);
		FlipRight(v);
		PushBlack(q);

		if (v->right->colour == red)
		{
			FlipLeft(v);
		}

		return q;
	}
	else
	{
		return v;
	}
}

template <typename T, template <typename T> class N>
N<T>* RedBlackTree<T, N>::RemoveFixUpCase3(N<T>* _u)
{	
	N<T>* w = _u->parent;
	N<T>* v = w->left;
	PullBlack(w);
	FlipRight(w);
	N<T>* q = w->left;

	if (q->colour == red)
	{
		RotateRight(w);
		FlipLeft(v);
		PushBlack(q);
		return q;
	}
	else
	{
		if (v->left->colour == red)
		{
			PushBlack(v);
			return v;
		}
		else
		{
			FlipLeft(v);
			return w;
		}
	}
	return _u;
}


