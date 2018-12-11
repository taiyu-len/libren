#ifndef REN_BUILDER_HPP
#define REN_BUILDER_HPP
#pragma once
/** Generate Composite buildable Object.
 *
 * The object template takes components to be used in the real object.
 *
 * using FB = ren::Object<Foo, Bar>;
 * FB x = FB::create()
 *   .foo().set(3)
 *   .bar().is(5);
 *
 * and such.
 */
#include <utility>
namespace ren
{

template<typename ...T>
struct Object : T... {
private:
	Object() = default;
public:
	// Copy/Move Constructors.
	Object(Object const&) = default;
	Object(Object &&) noexcept = default;
	Object& operator=(Object const&) = default;
	Object& operator=(Object &&) noexcept = default;

	~Object() = default;

	// Create object using builders provided via templates
	struct BuilderBase : T::template BuilderBase<Object>... {
		Object &object;
		operator Object() { return std::move(object); }
		BuilderBase(Object &o):object(o){}
	};
	struct Builder : BuilderBase {
		Object _o;
		Builder() : BuilderBase{_o}, _o{} {};
		Builder(Object const& o):BuilderBase{_o}, _o{o} {};

		// prevent _o from being moved around and having references to 
		// the wrong object.
		Builder(Builder const&) = delete;
		Builder(Builder &&) = delete;
	};
	static Builder create() {
		return {};
	}

	// Create object based on *this and modify via builders
	Builder but() const {
		return {*this};
	}
};
}
#endif
