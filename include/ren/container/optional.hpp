#ifndef REN_OPTIONAL_HPP
#define REN_OPTIONAL_HPP
// lmao, this is terrible
// policy object is useful, but too much code to make it work nicely
#include <cstddef>
#include <memory>
namespace ren
{

// default optional policy.
template<typename T>
struct optional_policy {
	enum {
		// if true, then optional uses optional_policy::empty_value as
		// empty state.
		has_empty_value = false,

		// if true, then optional will assign to existing value instead
		// of destruct/construct on rebinding.
		has_value_semantics = false,
	};
};

namespace detail {
template<typename T, typename P, bool has_empty_value = P::has_empty_value>
struct optional_base;

struct no_construct {};

template<typename T, typename P>
struct optional_base<T, P, true>
{
private:
	std::byte _value[sizeof(T)];
public:
	auto value() & -> T& { return *static_cast<T*>(_value); }
	auto value() && -> T&& { return *static_cast<T*>(_value); }
	auto value() const& -> T const& { return *static_cast<T*>(_value); }
	auto value() const&& -> T const&& { return *static_cast<T*>(_value); }

	auto has_value() const -> bool
	{
		static_assert(P::has_empty_value);
		return value() != P::empty_value;
	}
	// Common constructors
	optional_base(no_construct) {};
	optional_base(T const& x) { new (_value) {x}; }
	optional_base(T && x)     { new (_value) {x}; }

	// Empty_value constructors
	optional_base()
	{
		static_assert(P::has_empty_value);
		new (_value) { P::empty_value };
	}
	optional_base(optional_base const& x)
	{
		static_assert(P::has_empty_value);
		new (_value) { x.value(); }
	}
	optional_base(optional_base && x)
	{
		static_assert(P::has_empty_value);
		new (_value) { std::move(x).value(); }
	}
	auto operator=(optional_base const& x) -> optional_base&
	{
		static_assert(P::has_empty_value);
		std::destroy_at(_value);
		new (_value) { x.value(); }
		return *this;
	}
	auto operator=(optional_base && x) -> optional_base&
	{
		static_assert(P::has_empty_value);
		std::destroy_at(_value);
		new (_value) { std::move(x).value(); }
		return *this;
	}
};

template<typename T, typename P>
struct optional_base<T, false> : public optional_base<T, P, true>
{
private:
	using super = optional_base<T, P, true>;
	bool _has_value : 1;
public:
	auto has_value() const -> bool { return _has_value; }
	
	optional_base()
	: super{ no_construct{} }
	, _has_value{false} {};

	optional_base(T const& x)
	: super{ x }
	, _has_value{true} {}

	optional_base(T && x)
	: super{ std::move(x) }
	, _has_value{true} {}

	optional_base(optional_base const& x)
	: super{ no_construct{} }
	, _has_value{x.has_value() }
	{
		if (x.has_value())
		{
			new (_value) { x.value(); }
		}
	}

	optional_base(optional_base && x)
	{
		if (x.has_value())
		{
			new (_value) { std::move(x).value(); }
		}
	}

	auto operator=(optional_base const& x) -> optional_base&
	{
		if (_has_value = x.has_value())
		{
			new (_value) { x.value(); }
		}
		return *this;
	}
	auto operator=(optional_base && x) -> optional_base&
	{
		if (_has_value = x.has_value())
		{
			new (_value) { std::move(x).value(); }
		}
		return *this;
	}
};
}

template<typename T, typename P = optional_policy<T>>
struct optional
: detail::optional_base<T, P>
{
private:
	using optional_base = detail::optional_base<T, P::has_empty_value>;
public:
	optional()
	: optional_base{}
	{
		if constexpr (P::has_empty_value)
		{
			value() = P::empty_value;
		}
		else
		{
			_has_value = true;
		}
	}
	~optional()
	{
		if (has_value())
		{
			value().~T();
		}
	}

	optional(optional const& o)
	{
	}
	optional(optional && o);
	explicit optional(T const& x);
	explicit optional(T && x);
	optional &operator=(optional const& o);
	optional &operator=(optional && o);
	optional &operator=(T const& o);
	optional &operator=(T && o);

	bool has_value() const {
		if constexpr (P::has_empty_value) {
			return value() != P::empty_value;
		} else {
			return _has_value;
		}
	}
	explicit operator bool() const {
		return has_value();
	}
	
	auto operator*() -> T& {
		return value();
	}
	auto operator*() const -> T const& {
		return value();
	}
	auto operator->() -> T* {
		return &value();
	}
	auto operator->() const -> T const* {
		return &value();
	}

	auto value() -> T& {
		return *static_cast<T*>(_value);
	}
	auto value() const -> T const& {
		return *static_cast<T const*>(_value);
	}




};

}
#endif
