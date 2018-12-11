#ifndef REN_CONTAINER_LIST_POOL_HPP
#define REN_CONTAINER_LIST_POOL_HPP
#include <vector>
#include <iterator>
namespace ren::container
{
// pool of T*s
template<typename T, template<typename...> typename C = std::vector>
struct list_pool
{
private:
	using value_type = T;
	using list_type  = size_t;
	static constexpr list_type empty_val = -1;

	struct node_t {
		list_type  next = empty();
		union {
			value_type value;
			char _[0];
		};
	};

	auto node(list_type x) -> node_t& { return _list[x-1]; }
	auto node(list_type x) const -> node_t const& { return _list[x-1]; }
	auto new_node() -> list_type {
		_list.push_back(node_t{});
		return _list.size();
	}

	list_type _free_list { empty() };
	C<node_t> _list {};
public:
	list_pool() = default;
	explicit list_pool(size_t size) { _list.reserve(size); }

	auto value(list_type x) -> value_type& { return node(x).value; }
	auto value(list_type x) const -> value_type const& { return node(x).value; }

	auto next(list_type x) -> list_type& { return node(x).next; }
	auto next(list_type x) const -> list_type const& { return node(x).next; }

	auto is_empty(list_type x) const -> bool { return x == empty(); }
	static auto empty() -> list_type { return list_type(0); }

	auto free(list_type x) -> list_type;
	auto allocate(value_type const& x, list_type y = empty()) -> list_type;

	// iterators
	struct iterator;
	auto begin(list_type x) -> iterator;
	auto end() -> iterator;
};
} // ren::container
#include <ren/container/list_pool_t.hpp>
#endif // REN_CONTAINER_LIST_POOL
