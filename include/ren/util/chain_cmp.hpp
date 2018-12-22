#ifndef REN_UTIL_CMP_HPP
#define REN_UTIL_CMP_HPP
/** Function for chaining comparison
 */
namespace ren::util
{
template<typename... Ts>
auto chain_cmp(Ts&&... xs);

} // namespace ren::util
#include <ren/util/chain_cmp_t.hpp>
#endif // REN_UTIL_CMP_HPP
