#ifndef REN_UTIL_CHAIN_CMP_T_HPP
#define REN_UTIL_CHAIN_CMP_T_HPP
namespace ren::util
{
namespace detail
{
template<typename T, typename... Ts>
struct chain_cmp_t : chain_cmp_t<Ts...>
{
	using base = chain_cmp_t<Ts...>;
	T cmp;
	chain_cmp_t(T &&x, Ts&&...xs): base{xs...}, cmp{x} {}
	template<typename X, typename Y>
	bool operator()(X const& x, Y const& y) const
	{
		if (cmp(x, y)) return true;
		if (cmp(y, x)) return false;
		return base::operator()(x, y);
	}
};

template<typename T>
struct chain_cmp_t<T>
{
	T cmp;
	template<typename X, typename Y>
	bool operator()(X const& x, Y const& y) const
	{
		return cmp(x, y);
	}
};
} // namespace detail

template<typename... Ts>
auto chain_cmp(Ts&&... xs)
{
	return detail::chain_cmp_t<Ts...>
	{
		std::forward<Ts>(xs)...
	};
}
} // namespace ren::util
#endif // REN_UTIL_CHAIN_CMP_T_HPP
