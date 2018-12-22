#include <type_traits>
namespace ren::util
{
namespace detail
{
template<typename T, typename F>
struct cmp_by_t;

template<typename R, typename T, typename F>
struct cmp_by_t<R T::*, F> : private F
{
	using is_transparent = void;

	cmp_by_t(F f, R T::* m):F{std::move(f)}, _member{m} {}
	R T::* _member;
	bool operator()(T const& x, T const& y) const
	{
		return F::operator()(x .* _member, y .* _member);
	}
	bool operator()(R const& x, T const& y) const
	{
		return F::operator()(x, y .* _member);
	}
	bool operator()(T const& x, R const& y) const
	{
		return F::operator()(x.*_member, y);
	}
};

template<typename R, typename T, typename F>
struct cmp_by_t<R (T::*)() const, F> : private F
{
	using is_transparent = void;

	cmp_by_t(F f, R (T::* m)() const):F{std::move(f)}, _member{m} {}
	R (T::* _member)() const;
	bool operator()(T const& x, T const& y) const
	{
		return F::operator()((x .* _member)(), (y .* _member)());
	}
	bool operator()(R const& x, T const& y) const
	{
		return F::operator()(x, (y .* _member)());
	}
	bool operator()(T const& x, R const& y) const
	{
		return F::operator()((x.*_member)(), y);
	}
};
} // namespace detail

template<typename R, typename T, typename F>
auto cmp_by(R T::* member, F f)
{
	static_assert(std::is_invocable_r<bool, F, R, R>::value);
	return detail::cmp_by_t<R T::*, F>
	{
		std::move(f), member
	};
}

template<typename R, typename T, typename F>
auto cmp_by(R (T::* member)() const, F f)
{
	static_assert(std::is_invocable_r<bool, F, R, R>::value);
	return detail::cmp_by_t<R (T::*)() const, F>
	{
		std::move(f), member
	};
}
} // namespace ren::util
