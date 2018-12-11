#ifndef REN_ITERATOR_ACCUMULATE_HPP
#define REN_ITERATOR_ACCUMULATE_HPP
#include <iterator>
#include <type_traits>
namespace ren::iterator
{
template<typename T, typename F>
struct accumulate : private F
{
	static_assert(std::is_invocable_r_v<T, F, T, T>);

	using value_type        = void;
	using difference_type   = void;
	using pointer           = void;
	using reference         = void;
	using iterator_category = std::output_iterator_tag;

	explicit accumulate(T const& x): F{}, _value{x} {};
	explicit accumulate(T const& x, F const& y): F{y}, _value{x} {};

	// assignment to accumulators with other functions
	template<typename F2>
	void operator=(accumulate<T, F2> const& x) { _value = x._value; }

	// Iterator methods
	void operator=(T const& x) { _value = (*this)(_value, x); }
	auto operator*() -> accumulate&  { return *this; }
	auto operator++() -> accumulate& { return *this; }
	auto operator++(int) -> accumulate& { return *this; }

	// value methods
	[[nodiscard]]
	auto value() const -> T const& { return _value; }

	void reset() { _value = T{}; }
	void reset(T const& x) { _value = x; }

private:
	T _value {};
};
} // ren::iterator
#endif // REN_ITERATOR_ACCUMULATE_HPP
