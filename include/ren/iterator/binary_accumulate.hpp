#ifndef REN_ITERATOR_BINARY_ACCUMULATE_HPP
#define REN_ITERATOR_BINARY_ACCUMULATE_HPP
#include <array>
#include <type_traits>
namespace ren::iterator
{
template<typename T, typename F, size_t S = 32>
// requires T{}
class binary_accumulate : private F
{
public:
	static_assert(std::is_invocable_r_v<T, F, T, T>);
	using container_type    = std::array<T, S>;
	using value_type        = void;
	using difference_type   = void;
	using pointer           = void;
	using reference         = void;
	using iterator_category = std::output_iterator_tag;

	explicit binary_accumulate(): binary_accumulate(T{}, F{}) {};
	explicit binary_accumulate(T const& x): binary_accumulate(x, F{}) {};
	explicit binary_accumulate(T const& x, F const& y): F{y}, zero{x}, values{} {};

	void operator=(T x)
	{
		for (auto& value : values)
		{
			if (value == zero) { value = std::move(x); return; }
			else x = (*this)(std::exchange(value, zero), std::move(x));
		}
		// entire range has been set to zero, so restart
		values[0] = std::move(x);
	}
	auto operator*() -> binary_accumulate&  { return *this; }
	auto operator++() -> binary_accumulate& { return *this; }
	auto operator++(int) -> binary_accumulate& { return *this; }

	[[nodiscard]]
	auto value() -> T const& {
		T x = zero;
		for (auto& value : values)
		{
			x = (*this)(std::exchange(value, zero), std::move(x));
		}
		return values[0] = std::move(x);
	}
	void reset() {
		for (auto& value: values)
		{
			value = zero;
		}
	}
	void reset(T const& x) {
		reset();
		values[0] = x;
	}
private:
	T zero;
	container_type values{};
};
} // ren::iterator
#endif // REN_ITERATOR_BINARY_ACCUMULATE_HPP
