#include <iostream>

template<typename T>
auto foo(int x)-> decltype(x)
{
	return x*x;
}

int main(int, char**) {
	int x = 4;
	auto y = [&](){
		return foo<int>(x);

	};

	std::cout << y ()<< std::endl;
}