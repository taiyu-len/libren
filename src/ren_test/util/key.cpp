#include <ren/util/key.hpp>
#include <doctest/doctest.h>
namespace {
struct foo
{
	using value_type = int;
};
struct bar
{
	using value_type = double;
};
TEST_CASE("ren::util::key")
{
	using foo_key = ren::util::key<foo>;
	using bar_key = ren::util::key<bar>;
	// must be constructed explicitly
	auto x = foo_key(12514);
	auto y = bar_key(9.9);
	// value can be accessed directly
	CHECK_EQ(x.value, 12514);
	CHECK_EQ(y.value, 9.9);
	// can cast ot other types/domains
	CHECK_EQ(ren::util::cast<int>(x), 12514);
	CHECK_EQ(ren::util::cast<foo_key>(y), foo_key(9));
	// can compare keys
	CHECK_EQ(x, x);
}
}
