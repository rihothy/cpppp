#ifndef _CPPPP_DETAIL_ZIP_HPP_
#define _CPPPP_DETAIL_ZIP_HPP_

#include <type_traits>
#include <tuple>

template<class Containers>
class Zip
{
public:

	template<class Iterators>
	class const_iterator
	{
	protected:

		Iterators iterators;

	public:

		const_iterator(Iterators&& iterators) :iterators(std::forward<Iterators>(iterators))
		{

		}

		inline const auto& operator*(void) const
		{
			return traverse(iterators, [](auto& iterator)->decltype(*iterator) {return *iterator; },
				[](const auto&... args) {return std::tie(args...); },
				std::make_index_sequence<std::tuple_size<decltype(iterators)>::value>());
		}

		inline auto& operator++(void)
		{
			traverse(iterators, [](auto& iterator) {return ++iterator; },
				[](auto&&... args) { },
				std::make_index_sequence<std::tuple_size<decltype(iterators)>::value>());

			return *this;
		}

		inline auto operator!=(const const_iterator& another) const
		{
			return traverse(iterators, another.iterators, [](auto& iterator1, auto& iterator2) {return iterator1 != iterator2; },
				[&](auto&&... args) {return (args && ...); },
				std::make_index_sequence<std::tuple_size<decltype(iterators)>::value>());
		}
	};

	template<class Iterators>
	class iterator :public const_iterator<Iterators>
	{
	public:

		iterator(Iterators&& iterators) :const_iterator<Iterators>(std::forward<Iterators>(iterators))
		{

		}

		inline auto operator*(void) const
		{
			return traverse(const_iterator<Iterators>::iterators, [](auto& iterator)->decltype(*iterator) {return *iterator; },
				[](auto&&... args) {return std::tie(args...); },
				std::make_index_sequence<std::tuple_size<decltype(const_iterator<Iterators>::iterators)>::value>());
		}
	};

private:

	Containers containers;

public:

	Zip(Containers&& containers) :containers(std::move(containers))
	{

	}

	auto begin(void) noexcept
	{
		return traverse(containers, [](auto&& container) {return container.begin(); }, 
			[](auto... args) {return iterator(std::tuple(args...)); },
			std::make_index_sequence<std::tuple_size<decltype(containers)>::value>());
	}

	auto begin(void) const noexcept
	{
		return traverse(containers, [](const auto& container) {return container.begin(); },
			[](auto... args) {return const_iterator(std::tuple(args...)); },
			std::make_index_sequence<std::tuple_size<decltype(containers)>::value>());
	}

	auto end(void) noexcept
	{
		return traverse(containers, [](auto&& container) {return container.end(); },
			[](auto... args) {return iterator(std::tuple(args...)); },
			std::make_index_sequence<std::tuple_size<decltype(containers)>::value>());
	}

	auto end(void) const noexcept
	{
		return traverse(containers, [](const auto& container) {return container.end(); },
			[](auto... args) {return const_iterator(std::tuple(args...)); },
			std::make_index_sequence<std::tuple_size<decltype(containers)>::value>());
	}

	auto operator=(const Zip& another) = delete;

private:

	template<class Arg, class Func_in, class Func_out, size_t... I>
	inline static auto traverse(Arg&& arg, Func_in func_in, Func_out func_out, std::index_sequence<I...>)
	{
		return func_out(func_in(std::get<I>(arg))...);
	}

	template<class Arg1, class Arg2, class Func_in, class Func_out, size_t... I>
	inline static auto traverse(Arg1&& arg1, Arg2&& arg2, Func_in func_in, Func_out func_out, std::index_sequence<I...>)
	{
		return func_out(func_in(std::get<I>(arg1), std::get<I>(arg2))...);
	}
};

template<class... Args>
auto zip(Args&&... args)
{
	return Zip(std::tuple<Args...>(std::forward<Args>(args)...));
}

#endif