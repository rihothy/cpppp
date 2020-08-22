#ifndef _CPPPP_DETAIL_ENUMERATE_HPP_
#define _CPPPP_DETAIL_ENUMERATE_HPP_

#include <type_traits>
#include <tuple>

template<class Container>
class Enumerate
{
public:

	template<class Iterator>
	class const_iterator
	{
	protected:

		size_t index;
		Iterator iterator;

	public:

		const_iterator(size_t index, Iterator iterator) :index(index), iterator(iterator)
		{

		}

		inline const auto& operator*(void) const
		{
			return std::tuple_cat(std::tuple(index), make_tuple(*iterator));
		}

		inline auto& operator++(void)
		{
			++index;
			++iterator;

			return *this;
		}

		inline auto operator!=(const const_iterator& another) const
		{
			return iterator != another.iterator;
		}

		template<class Value>
		requires requires(Value value)
		{
			std::get<0>(value);
		}
		static decltype(auto) make_tuple(Value&& value)
		{
			return std::forward<Value>(value);
		}

		template<class Value>
		requires requires(Value value)
		{
			std::get<0>(value);
		}
		static decltype(auto) make_tuple(const Value& value)
		{
			return (value);
		}

		template<class Value>
		static auto make_tuple(Value& value)
		{
			return std::tie(value);
		}

		template<class Value>
		static auto make_tuple(const Value& value)
		{
			return std::tie(value);
		}
	};

	template<class Iterator>
	class iterator :public const_iterator<Iterator>
	{
	public:

		iterator(size_t index, Iterator iterator) :const_iterator<Iterator>(index, iterator)
		{

		}

		inline auto operator*(void) const
		{
			return std::tuple_cat(std::tuple(const_iterator<Iterator>::index), const_iterator<Iterator>::make_tuple(*const_iterator<Iterator>::iterator));
		}
	};

private:

	size_t start;
	Container container;

public:

	Enumerate(Container&& container, size_t start) :container(std::forward<Container>(container)), start(start)
	{

	}

	auto begin(void) noexcept
	{
		return iterator(start, container.begin());
	}

	auto begin(void) const noexcept
	{
		return const_iterator(start, container.begin());
	}

	auto end(void) noexcept
	{
		return iterator(-1ull, container.end());
	}

	auto end(void) const noexcept
	{
		return const_iterator(-1ull, container.end());
	}
};

template<class Container>
auto enumerate(Container&& container, size_t start = 0ull)
{
	return Enumerate<Container>(std::forward<Container>(container), start);
}

#endif