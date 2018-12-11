#include <ren/util/mem_cmp.hpp>
#include <functional>
#include <doctest/doctest.h>
namespace
{
struct foo
{
	int x, y;
	int sum() const { return x + y; }
};
TEST_CASE("ren::util::mem_cmp")
{
	foo a = { 3, 6 };
	foo b = { 7, 5 };
	using namespace ren::util;
	REQUIRE(mem_cmp(&foo::x)(a, b));
	REQUIRE(mem_cmp(&foo::y)(a, b) == false);
	REQUIRE(mem_cmp(&foo::x, std::greater<>{})(a, b) == false);
	REQUIRE(mem_cmp(&foo::y, std::greater<>{})(a, b));
	REQUIRE(mem_cmp(&foo::sum)(a, b));
	REQUIRE(mem_cmp(&foo::sum, std::greater<>{})(a, b) == false);
}
}
