#include "ren/io/parse.hpp"
#include <doctest/doctest.h>
#include <string>
#include <sstream>
#include <type_traits>
namespace ren::io
{
TEST_CASE("ren::io::parse")
{
	auto iss = std::istringstream("1 2.5 cats");
	SUBCASE("specified")
	{
		auto i = parse<int>(iss);
		auto d = parse<double>(iss);
		auto s = parse<std::string>(iss);
		REQUIRE(i == 1);
		REQUIRE(std::is_same_v<decltype(i), int>);
		REQUIRE(d == 2.5);
		REQUIRE(std::is_same_v<decltype(d), double>);
		REQUIRE(s == "cats");
		REQUIRE(std::is_same_v<decltype(s), std::string>);
	}
	SUBCASE("void")
	{
		// automatically parses left hand value,
		int i = parse(iss);
		// stores a parser type
		auto p = parse(iss);

		auto d = (double)p;
		std::string s = p;
		REQUIRE(i == 1);
		REQUIRE(std::is_same_v<decltype(i), int>);
		REQUIRE(d == 2.5);
		REQUIRE(std::is_same_v<decltype(d), double>);
		REQUIRE(s == "cats");
		REQUIRE(std::is_same_v<decltype(s), std::string>);
	}
}

} // ren::io
