#ifndef REN_IO_PARSE_T_HPP
#define REN_IO_PARSE_T_HPP
#include <istream>
namespace ren::io
{
struct parser_t
{
	template<typename T>
	operator T() { return parse<T>(*_is); }
	operator std::istream&() { return *_is; }

	std::istream* _is;
};

template<typename T>
auto parse(std::istream& is)
-> std::conditional_t<std::is_void_v<T>, parser_t, T>
{
	if constexpr (std::is_void_v<T>) {
		return parser_t{&is};
	} else {
		T x;
		is >> x;
		return x;
	}
}

} // ren::io
#endif // REN_IO_PARSE_T_HPP
