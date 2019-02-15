#include <memory>
#include <utility>
#include <cassert>
namespace ren::util
{
template<typename R, typename...Args>
class function<R(Args...)>
{
public:
	function() noexcept = default;
	function(std::nullptr_t) noexcept {};
	function(function &&) noexcept = default;
	function(const function &o)
	: _ptr(o._ptr->clone()) {};
	function& operator=(function &&) noexcept = default;
	function& operator=(const function &o)
	{
		_ptr = o._ptr->clone();
	}
	function& operator=(std::nullptr_t) noexcept { _ptr.reset(); };

	template<typename T>
	function(T&& x);

	R operator()(Args... args) const
	{
		assert(_ptr != nullptr);
		return _ptr->operator()(std::move(args)...);
	};

	operator bool() const noexcept
	{
		return bool(_ptr);
	}

	friend void swap(function& x, function& y)
	{
		std::swap(x._ptr, y._ptr);
	}

	friend bool operator==(function const& x, function const& y)
	{
		return x._ptr == y._ptr;
	}

	friend bool operator!=(function const& x, function const& y)
	{
		return !(x == y);
	}

private:
	struct concept_t
	{
		virtual ~concept_t() noexcept = default;
		virtual R operator()(Args... args) = 0;
		virtual std::unique_ptr<concept_t> clone() const = 0;
	};

	template<typename T>
	struct model_t : concept_t
	{
		model_t(T&& x): _data(std::move(x)) {};
		model_t(T const& x): _data(std::move(x)) {};
		R operator()(Args... args) override
		{
			return _data(std::move(args)...);
		}
		std::unique_ptr<concept_t> clone() const override
		{
			return std::make_unique<model_t>(_data);
		}
		T _data;
	};
	std::unique_ptr<concept_t> _ptr {};
};

template<typename R, typename... Args>
template<typename T>
function<R(Args...)>::function(T&& fn)
{
	constexpr bool x = std::is_invocable_r<R, T, Args...>::value;
	static_assert(x, "ren::util::function constructed with invalid type");
	if constexpr (x)
	{
		_ptr = std::make_unique<model_t<std::decay_t<T>>>(std::forward<T>(fn));
	}
}
} // ren::util
