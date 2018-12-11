#include <ren/iterator/binary_accumulate.hpp>
#include <algorithm>
#include <functional>
#include <string>
#include <doctest/doctest.h>

TEST_CASE("ren::iterator::binary_accumulate")
{
	auto a = ren::iterator::binary_accumulate<std::string, std::plus<>>{};
	std::string arr[] = {"foo", " ", "bar", " ", "baz", "!"};
	a = std::copy(std::begin(arr), std::end(arr), a);
	REQUIRE(a.value() == "foo bar baz!");

	a.reset();
	REQUIRE(a.value() == "");

	a.reset("cats");
	REQUIRE(a.value() == "cats");
}
