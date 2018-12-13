#ifndef REN_IO_PARSE_HPP
#define REN_IO_PARSE_HPP
#include <iosfwd>
#include <type_traits>
namespace ren::io
{
struct parser_t;

template<typename T = void>
auto parse(std::istream&)
-> std::conditional_t<std::is_void_v<T>, parser_t, T>;
} // ren::io
#include <ren/io/parse_t.hpp>
#endif // REN_IO_PARSE_HPP
