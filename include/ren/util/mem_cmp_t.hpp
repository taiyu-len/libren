#include <type_traits>
namespace ren::util
{
namespace detail
{
template<typename T, typename F>
struct mem_cmp_t;

template<typename R, typename T, typename F>
struct mem_cmp_t<R T::*, F> : private F
{
	mem_cmp_t(F f, R T::* m):F{std::move(f)}, _member{m} {}
	R T::* _member;
	bool operator()(T const& x, T const& y) const
	{
		return F::operator()(x .* _member, y .* _member);
	}
};

template<typename R, typename T, typename F>
struct mem_cmp_t<R (T::*)() const, F> : private F
{
	mem_cmp_t(F f, R (T::* m)() const):F{std::move(f)}, _member{m} {}
	R (T::* _member)() const;
	bool operator()(T const& x, T const& y) const
	{
		return F::operator()((x .* _member)(), (y .* _member)());
	}
};
} // detail

template<typename R, typename T, typename F>
auto mem_cmp(R T::* member, F f)
{
	static_assert(std::is_invocable_r<bool, F, R, R>::value);
	return detail::mem_cmp_t<R T::*, F>{ std::move(f), member };
}

template<typename R, typename T, typename F>
auto mem_cmp(R (T::* member)() const, F f)
{
	static_assert(std::is_invocable_r<bool, F, R, R>::value);
	return detail::mem_cmp_t<R (T::*)() const, F>{ std::move(f), member };
}
} // ren::util
