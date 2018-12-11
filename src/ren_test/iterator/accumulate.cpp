#include <ren/iterator/accumulate.hpp>
#include <algorithm>
#include <doctest/doctest.h>

TEST_CASE("ren::iterator::accumulate")
{
	auto a = ren::iterator::accumulate{ 0, std::plus<>{} };
	int arr[] = { 1, 2, 3, 4, 5, 6 };
	a = std::copy(std::begin(arr), std::end(arr), a);
	REQUIRE(a.value() == 1+2+3+4+5+6);

	a.reset();
	REQUIRE(a.value() == 0);

	a.reset(5);
	REQUIRE(a.value() == 5);
}
