#include <utility>
namespace ren::util
{

template<typename Domain>
struct key
{
	using domain_type = Domain;
	using value_type  = typename domain_type::value_type;

	key() = default;
	explicit key(value_type const& x) : value{x} {};
	explicit key(value_type && x) : value{std::move(x)} {};

	key(key const&) = default;
	key(key &&) = default;
	~key() = default;

	key& operator=(key const&) = default;
	key& operator=(key &&) = default;

	friend
	bool operator==(key const& x, key const& y)
	{
		return x.value == y.value;
	}
	friend
	bool operator!=(key const& x, key const& y)
	{
		return !(x == y);
	}
	friend
	bool operator<(key const& x, key const& y)
	{
		return x.value < y.value;
	}
	friend
	bool operator>(key const& x, key const& y)
	{
		return y < x;
	}
	friend
	bool operator<=(key const& x, key const& y)
	{
		return !(y < x);
	}
	friend
	bool operator>=(key const& x, key const& y)
	{
		return !(x < y);
	}

	key& operator++()
	{
		++value;
		return *this;
	}
	key& operator--()
	{
		--value;
		return *this;
	}

	key operator++(int)
	{
		auto copy = *this;
		++value;
		return copy;
	}
	key operator--(int)
	{
		auto copy = *this;
		--value;
		return copy;
	}

	value_type value;
};

template<typename T, typename F>
T cast(key<F> const& x)
{
	return T(x.value);
}

} // ren::util
