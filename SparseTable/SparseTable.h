#ifndef SparseTable_H
#define SparseTable_H

#include <vector>

class SparseTable
{
	const int n;
	std::vector<int> v;

	public:

		SparseTable(std::vector<int>& iv);
		int Min(const int beg, const int end);

	private:

		std::pair<int, int> GetIndices(const int beg, const int end);
		int Log2(int sz);
		int GetCumSize(int p);
};

#endif

