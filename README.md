# cpppp
Some Python features are implemented on C + + to make C + + easier to use. Since most of them are implemented with templates, there is almost no additional cost.
## Examples
```cpp
#include <cpppp/cpppp>
#include <vector>
#include <string>

using namespace std;

int main(void)
{
	auto vec_a = vector{ ("hello"), ("world"), ("then"), ("byebye") };
	auto vec_b = vector{ 19, 26, 8, 17 };

	for (auto [a, b] : zip(vec_a, vec_b))
	{
		print(a, b);
	}

	print(string(16, '-'));

	for (auto [i, ele] : enumerate(vec_a))
	{
		print(i, ele);
	}

	print(string(16, '-'));

	for (auto [i, a, b] : enumerate(zip(vec_a, vec_b), 1))
	{
		print(i, a, b);
	}

	print(string(16, '-'));

	for (auto i : range(5))
	{
		print(i);
	}

	return 0;
}
```
