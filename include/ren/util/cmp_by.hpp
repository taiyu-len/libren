#ifndef REN_UTIL_CMP_BY_HPP
#define REN_UTIL_CMP_BY_HPP
#include <functional>
/** Binary comparison function for sorting objects by member variables, or
 *  functions.
 *
 * Provides transparent comparisons to lookup via the type.
 */
namespace ren::util {
template<typename R, typename T, typename Fn = std::less<R>>
auto cmp_by(R T::* member, Fn fn = Fn{});

template<typename R, typename T, typename Fn = std::less<R>>
auto cmp_by(R (T::* member)() const, Fn fn = Fn{});
} // ren::util
#include <ren/util/cmp_by_t.hpp>
#endif // REN_UTIL_CMP_BY_HPP
