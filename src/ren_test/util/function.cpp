#include <ren/util/function.hpp>
#include <ren/util/unique_function.hpp>
#include <doctest/doctest.h>

namespace
{
int fp(int x, int y) { return x + y; }
struct fo {
	int operator()(int x, int y) const { return x + y; }
};
const auto lambda = [](int x, int y) -> int { return x + y; };

TEST_CASE("ren::util::function")
{
	using F = ren::util::function<int(int, int)>;
	F fs[3] = {fp, lambda, fo{}};
	for (auto& f : fs)
		REQUIRE(f(1, 2) == 3);
}


TEST_CASE("ren::util::unique_function")
{
	using F = ren::util::unique_function<int(int, int)>;
	F fs[3] = {fp, lambda, fo{}};
	for (auto& f : fs)
		REQUIRE(f(1, 2) == 3);
}

}
