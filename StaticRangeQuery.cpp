#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

class StaticRangeQuery
{
	const int n;
	vector<pair<int, int>> v;
	
	public:
	StaticRangeQuery(vector<int>& iv) : n(iv.size())
	{
		int p = Log2(n);
		int sz = GetCumSize(p);
		
		v.resize(sz);
		for(int i=0;i<n;++i)
			v[i] = {iv[i], iv[i]};
		
		int beg=0, end=n;
		std::pair<int, int> val1, val2;
		for(int i=1;i<=p;++i)
		{
			sz = n - (1 << i) + 1;
			for(int j=0;j<sz;++j)
			{
				val1 = v[beg+j];
				val2 = v[beg+j+(1<<(i-1))];
				v[end+j] = {std::min(val1.first, val2.first), std::max(val1.second, val2.second)};
			}
			
			beg = end;
			end += sz;
		}
	}
	
	int size()
	{
		return n;
	}
	
	int Log2(const int num)
	{
		int p=-1;
		while( (1<<(p+1)) <= num)
			++p;
		return p;
	}
	
	int GetCumSize(const int p)
	{
		int sz = 0;
		for(int i=0;i<=p;++i)
			sz += (n-(1<<i)+1);
		return sz;
	}
	
	std::pair<int, int> GetIndices(const int beg, const int end)
	{
		assert(0 <= beg);
		assert(beg < n);
		assert(beg <= end);
		assert(0 <= end);
		assert(end < n);

		if(beg == end)
			return {beg, end};

		int sz = end - beg + 1;
		int p = Log2(sz);
		int ind = GetCumSize(p-1);
		int b = ind+beg;
		int e = ind+end-(1<<p)+1;
		return {b, e};
	}
	
	int Min(const int beg, const int end)
	{
		auto pr = GetIndices(beg, end);
		int ans = v[pr.first].first;
		if(pr.first != pr.second)
			ans = std::min(ans, v[pr.second].first);
		
		return ans;
	}
	
	int Max(const int beg, const int end)
	{
		auto pr = GetIndices(beg, end);
		int ans = v[pr.first].second;
		if(pr.first != pr.second)
			ans = std::max(ans, v[pr.second].second);
		
		return ans;
	}
	
	void print()
	{
		cout << "\n [ ";
		for(int i=0;i<n;++i)
			cout << v[i].first << " ";
		cout << "]\n";
		
		cout << "\nMin: " << v.size() << " [ ";
		for(const auto& i: v)
			cout << i.first << " ";
		cout << "]\n";
		
		cout << "\nMax: " << v.size() << " [ ";
		for(const auto& i: v)
			cout << i.second<< " ";
		cout << "]\n";
	}
};

void test(StaticRangeQuery& srq, vector<int>& v)
{
	for(int i=0;i<v.size();++i)
	{
		for(int j=i;j<v.size();++j)
		{
			int mn1 = srq.Min(i, j);
			int mn2 = *std::min_element(v.begin()+i, v.begin()+j+1);
			if(mn1 != mn2)
			{
				srq.print();
				cout << "\nQuery = [" << i << ", " << j << "]\n";
				cout << "\nsrq.Min(i, j) = " << mn1 << "\n";
				cout << "\nActual Min(i, j) = " << mn2 << "\n";
				assert(mn1 == mn2);
			}
			
			int mx1 = srq.Max(i, j);
			int mx2 = *std::max_element(v.begin()+i, v.begin()+j+1);
			if(mx1 != mx2)
			{
				srq.print();
				cout << "\nQuery = [" << i << ", " << j << "]\n";
				cout << "\nsrq.Max(i, j) = " << mx1 << "\n";
				cout << "\nActual Max(i, j) = " << mx2 << "\n";
				assert(mx1 == mx2);
			}
		}
	}
}

void Generate(vector<int>& v)
{
	srand(time(NULL));
	int sz = 500 + rand() % 500;
	v.resize(sz);
	for(int i=0;i<sz;++i)
		v[i] = rand() % 100000;
}

void test()
{
	for(int i=0;i<=100;++i)
	{
		vector<int> v;
		Generate(v);
		StaticRangeQuery srq(v);
		test(srq, v);
	}
	
	cout << "\nStatic Range Query successful !!!";
}

int main()
{
	test();
	cin.get();
	
	return 0;
}
