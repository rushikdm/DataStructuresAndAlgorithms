#include <iostream>
#include <vector>
#include <string>
#include <assert.h>

using namespace std;

class PrefixSumArray
{
	vector<int> v;
	
	public:
	
	PrefixSumArray(vector<int>& iv): v(iv.size())
	{
		if(iv.size() <= 0)
			return;
			
		v[0] = iv[0];
		for(int i=1;i<iv.size();++i)
			v[i] = v[i-1] + iv[i];
	}
	
	int RangeSumQuery(const int l, const int r)
	{
		int rsum = v[r];
		if(l > 0)
			rsum -= v[l-1];
			
		return rsum;
	}
};

int main()
{
		vector<int> v{1,2,3,4,5,6,7,8};
		
		PrefixSumArray psa(v);
		
		vector<pair<int, int>> queries{ {3, 5}, {1, 4}, {0, 7} };
		for(auto& q: queries)
		{
			int rsum = psa.RangeSumQuery(q.first, q.second);
			cout << "\nRange: [" << q.first << " " << q.second << "] sum = " << rsum << endl;
		}
		
		return 0;	
}
