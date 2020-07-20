#include "SparseTable.h"
#include <assert.h>

SparseTable::SparseTable(std::vector<int>& iv): n(iv.size())
{
	int p = Log2(n);
	int sz = GetCumSize(p);

	v.resize(sz);
	copy(iv.begin(), iv.end(), v.begin());

	int beg = 0, end = n, pw2;
	for(int i=1;i<=p;++i)
	{
		sz = n - (1 << i) + 1;
		pw2 = 1 << (i-1);
		for(int j=0;j<sz;++j)
			v[end+j] = std::min(v[beg+j], v[beg+j+pw2]);

		beg = end;
		end += sz;
	}
}

int SparseTable::Min(const int beg, const int end)
{
	auto pr = GetIndices(beg, end);
	
	int mn = v[pr.first];
	if(pr.first != pr.second)
		mn = std::min(mn, v[pr.second]);

	return mn;
}

// Returns the indices of elements in sparse table given the indices of elements in static array
std::pair<int, int> SparseTable::GetIndices(const int beg, const int end)
{	
	assert(beg >= 0);
	assert(beg < n);
	assert(end >= beg);
	assert(end < n);

	int sz = end - beg + 1;
	int p = Log2(sz);
	int ind = GetCumSize(p-1);
	int b = ind + beg;
	int e = ind + end - (1 << p) + 1;

	assert(b >= 0);
	assert(b < v.size());
	assert(e >= b);
	assert(e < v.size());

	return {b, e};
}

// Returns the highest possible power over 2 such that 2 ^ p <= sz
int SparseTable::Log2(int sz)
{
	assert(sz > 0);

	int p = 0, pw2 = 1;
	while( (pw2 << 1) < sz)
	{
		++p;
		pw2 = pw2 << 1;
	}

	return p;
}

// Returns the total number of elements in (conceptual) rows of sparse table from 0 to p
// The number of elements in a row with power p = n - 2^p + 1
int SparseTable::GetCumSize(int p)
{
	int csz = 0;
	for(int I = 0; I <= p; ++I)
		csz += (n - (1 << I) + 1);

	return csz;
}

