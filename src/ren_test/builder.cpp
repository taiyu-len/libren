#include "ren/builder.hpp"
#include <doctest/doctest.h>

namespace ren
{
struct Foo {
	template<typename T>
	struct Builder : T::BuilderBase {
		Builder &is(int i) {
			this->object.foo = i;
			return *this;
		}
	};
	template<typename T>
	struct BuilderBase {
		Builder<T> foo() {
			return { static_cast<typename T::BuilderBase*>(this)->object };
		}
	};
	// Data
	int foo;
};
struct Bar {
	template<typename T>
	struct Builder : T::BuilderBase {
		Builder &is(int i) {
			this->object.bar = i;
			return *this;
		}
	};
	template<typename T>
	struct BuilderBase {
		Builder<T> bar() {
			return { static_cast<typename T::BuilderBase*>(this)->object };
		}
	};
	// Data
	int bar;
};

TEST_CASE("Builder Object") {
	using FB = Object<Foo, Bar>;
	FB entity = FB::create()
		.foo().is(9)
		.bar().is(6);
	CHECK(entity.foo == 9);
	CHECK(entity.bar == 6);
	FB copy = entity.but()
		.foo().is(999);
	CHECK(copy.foo == 999);
	CHECK(copy.bar == 6);
}
} // namespace ren
