#ifndef REN_UTIL_MEM_CMP_HPP
#define REN_UTIL_MEM_CMP_HPP
#include <functional>
/** binary comparison function for comparing parts of structures.
 *
 * Comparsion utility function taking a pointer to member
 * and a comparison type
 */
namespace ren::util {
template<typename R, typename T, typename Fn = std::less<R>>
auto mem_cmp(R T::* member, Fn fn = Fn{});

template<typename R, typename T, typename Fn = std::less<R>>
auto mem_cmp(R (T::* member)() const, Fn fn = Fn{});
} // ren::util
#include <ren/util/mem_cmp_t.hpp>
#endif // REN_UTIL_MEM_CMP_HPP
