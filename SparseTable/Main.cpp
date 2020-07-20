#include "SparseTable.h"
#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include <iostream>
#include <assert.h>
#include <time.h>
#include <chrono>
#include <stdlib.h>

void Generate(std::vector<int>& v)
{
	srand(time(NULL));
	const int sz = v.size();
	for(int I = 0; I < sz; ++I)
		v[I] = rand() % 10000;
}

void time_test(std::vector<int>& v, std::function<int(int, int)> fn, std::string msg)
{
	auto start = std::chrono::steady_clock::now();

	const int sz = v.size();
	int mn;
	for(int I = 0; I < sz; ++I)
		for(int J = I; J < sz; ++J)
			mn = fn(I, J);

	auto end = std::chrono::steady_clock::now();
	auto tm = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();

	std::cout << "\n" << msg << tm << " milli-seconds" << std::endl;
}

void validate(std::vector<int>& v, std::function<int(int,int)> fun1, std::function<int(int,int)> fun2)
{
	const int sz = v.size();
	for(int I = 0; I < sz; ++I)
	{
		for(int J = I; J < sz; ++J)
		{
			int mn1 = fun1(I, J);
			int mn2 = fun2(I, J);
			assert(mn1 == mn2);
		}
	}
}

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);
	std::cout.tie(NULL);

	std::vector<int> v{45,4,9,-3,7,8,75,12};
	SparseTable st(v);
	int mn = st.Min(1, 5);
	assert(mn == -3);

	std::cout << "\nBasic Test for Range Minimum query using Sparse Table successful\n";

	int n;
	std::cout << std::endl << "Enter size: ";
	std::cout.flush();
	std::cin >> n;

	std::vector<int> v1(n);
	Generate(v1);

	auto naive_fn = [&v1](const int b, const int e)->int{
		return *std::min_element(v1.begin()+b, v1.begin()+e+1);
	};

	time_test(v1, naive_fn, "Time with naive approach = ");

	SparseTable st1(v1);

	auto st_fn = [&st1](const int b, const int e)->int{
		return st1.Min(b, e);
	};

	time_test(v1, st_fn, "Time with Sparse Table = ");

	validate(v1, naive_fn, st_fn);

	std::cout << "\nValidation for Sparse Table successful" << std::endl;

	return 0;
}

