#ifndef REN_CONTAINER_LIST_POOL_T_HPP
#define REN_CONTAINER_LIST_POOL_T_HPP
namespace ren::container
{
template<typename T, template<typename...> typename C>
auto list_pool<T, C>::free(list_type x) -> list_type
{
	auto cdr = next(x);
	next(x) = _free_list;
	value(x).~T();
	_free_list = x;
	return cdr;
}

template<typename T, template<typename...> typename C>
auto list_pool<T, C>::allocate(value_type const& x, list_type y) -> list_type
{
	if (_free_list == empty())
	{
		_free_list = new_node();
	}
	auto r = _free_list;
	_free_list = next(_free_list);
	new (&value(r)) T(x);
	next(r)  = y;
	return r;
}

// Iterators
template<typename T, template<typename...> typename C>
struct list_pool<T, C>::iterator
{
	using value_type      = list_pool::value_type;
	using difference_type = list_type;
	using reference       = value_type&;
	using pointer         = value_type*;
	using iterator_category = std::forward_iterator_tag;

	list_pool *_pool{ nullptr };
	list_type  _node{ list_pool::empty() };
	iterator() = default;
	explicit iterator(list_pool &p): _pool{&p} {};
	iterator(list_pool &p, list_type i): _pool{&p}, _node{i} {};

	// [[expects: pool && node]]
	auto operator*() const -> reference { return _pool->value(_node); }

	// [[expects: pool && node]]
	auto operator->() const -> pointer { return &**this; }

	// [[expects: pool]]
	explicit operator bool() const { return _pool->is_empty(_node); }

	auto operator++() -> iterator&
	// [[expects: pool]]
	{
		_node = _pool->next(_node);
		return *this;
	}

	auto operator++(int) -> iterator
	{
		return iterator{
			*_pool,
			std::exchange(_node, _pool->next(_node))
		};
	}

	friend
	auto operator==(iterator const& x, iterator const& y) -> bool
	// [[expects x.pool == y.pool]]
	{
		return x._node == y._node;
	}

	friend
	auto operator!=(iterator const& x, iterator const& y) -> bool
	// [[expects x.pool == y.pool]]
	{
		return !(x == y);
	}

	// given lists x:xs and y:ys make x:xs into x:y:ys
	friend
	auto set_successor(iterator x, iterator y) -> iterator
	{
		auto tmp = x._pool->next(x._node);
		x._pool->next(x._node) = y._node;
		return iterator{*x._pool, tmp};
	}

	// given list x:xs and value v, make x:xs into v:x:xs
	friend
	void push_front(iterator &x, value_type const& value)
	{
		x._node = x._pool->allocate(value, x._node);
	}

	// given list x:xs and value v, make x:xs into x:v:xs
	friend
	void push_back(iterator &x, value_type const& value)
	{
		auto tmp = x._pool->allocate(value, x._pool->next(x._node));
		x._pool->next(x._node) = tmp;
	}
};

template<typename T, template<typename...> typename C>
auto list_pool<T, C>::begin(list_type x) -> iterator
{
	return iterator{*this, x};
}

template<typename T, template<typename...> typename C>
auto list_pool<T, C>::end() -> iterator
{
	return iterator{*this};
}
} // ren::container
#endif // REN_CONTAINER_LIST_POOL_T_HPP
