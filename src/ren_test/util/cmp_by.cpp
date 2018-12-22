#include <ren/util/cmp_by.hpp>
#include <functional>
#include <doctest/doctest.h>
namespace
{
struct foo
{
	int x, y;
	int sum() const { return x + y; }
};
TEST_CASE("ren::util::cmp_by")
{
	foo a = { 3, 6 };
	foo b = { 7, 5 };
	using namespace ren::util;
	auto gt = std::greater<>{};
	auto cmp_by_x = cmp_by(&foo::x);
	auto cmp_by_x_r = cmp_by(&foo::x, gt);
	auto cmp_by_y = cmp_by(&foo::y);
	auto cmp_by_sum = cmp_by(&foo::sum);
	CHECK(cmp_by_x(a, b)); // compare by member variable
	CHECK(cmp_by_y(a, b) == false); // again
	CHECK(cmp_by_x(a, 0) == false); // transparent comparator
	CHECK(cmp_by_x_r(a, b) == false); // custom comparison function
	CHECK(cmp_by_sum(a, b)); // compare by member function
}
}
