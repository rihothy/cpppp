#ifndef _CPPPP_DETAIL_PRINT_HPP_
#define _CPPPP_DETAIL_PRINT_HPP_

#include <iostream>

template<class... Args>
constexpr auto print(Args... args)
{
	auto first = true;

	((std::cout << (first ? "" : " ") << args, first = false), ...);

	std::cout << std::endl;
}

#endif