#include <ren/util/cmp_by.hpp>
#include <ren/util/chain_cmp.hpp>
#include <functional>
#include <doctest/doctest.h>


namespace
{
struct foo
{
	int x, y;
	int sum() const { return  x + y; }
};
TEST_CASE("ren::util::chain_cmp")
{
	foo a = { 1, 2 };
	foo b = { 1, 3 };
	foo c = { 2, 2 };
	using namespace ren::util;
	auto cmp_xy = chain_cmp(
		cmp_by(&foo::x),
		cmp_by(&foo::y));
	REQUIRE(cmp_xy(a, b));
	REQUIRE(cmp_xy(a, c));
	REQUIRE(cmp_xy(b, c));
}
} // namespace
