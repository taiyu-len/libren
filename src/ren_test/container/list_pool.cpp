#include <ren/container/list_pool.hpp>
#include <doctest/doctest.h>
#include <iterator>
TEST_CASE("ren::container::list_pool")
{
	auto pool = ren::container::list_pool<int>{ 32 };
	auto x = pool.begin(pool.allocate(4));
	push_front(x, 3); // x = 3:4
	push_front(x, 2); // x = 2:3:4
	push_front(x, 1); // x = 1:2:3:4
	push_front(x, 0); // x = 0:1:2:3:4
	int j = 0;
	for (auto i = x; i != pool.end(); ++i, ++j) {
		REQUIRE(*i == j);
	}
	auto y = std::next(x);
	set_successor(x, pool.begin(pool.allocate(5))); // x = 0:5
	REQUIRE(*x == 0);
	REQUIRE(*std::next(x) == 5);
	(void) y;
}
