#ifndef REN_UTIL_KEY_HPP
#define REN_UTIL_KEY_HPP
#include <iosfwd>

/** Strongly typed keys */

namespace ren::util
{

// Defines a key type with a given domain
template<typename Domain>
// requires Domain::value_type
struct key;

// Constructs type T from F::value
template<typename T, typename F>
T cast(key<F> const& x);

} // ren::util

#include <ren/util/key_t.hpp>
#endif // REN_UTIL_KEY_HPP
