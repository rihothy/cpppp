#ifndef _CPPPP_DETAIL_RANGE_HPP_
#define _CPPPP_DETAIL_RANGE_HPP_

#include <type_traits>

template<typename T>
requires std::is_integral_v<T> class range
{
	class iterator
	{
		T step;
		T current;

	public:

		iterator(T current, T step) :current(current), step(step)
		{

		}

		auto operator*(void)
		{
			return current;
		}

		auto& operator++(void)
		{
			current += step;
			return *this;
		}

		auto operator!=(const iterator& another)
		{
			return current != another.current;
		}
	};

	T start;
	T stop;
	T step;

public:

	range(T start, T stop, T step = 1) :start(start), stop(stop), step(step)
	{

	}

	range(T stop) :range(0, stop, 1)
	{

	}

	auto begin(void) const
	{
		return iterator(start, step);
	}

	auto end(void) const
	{
		auto new_stop = (step < 0 ? (stop - start + step + 1) / step * step : (stop - start + step - 1) / step * step) + start;
		return iterator(new_stop, step);
	}
};

#endif