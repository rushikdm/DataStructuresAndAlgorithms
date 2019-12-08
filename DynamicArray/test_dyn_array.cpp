/* author : Rushikesh Keshavrao Deshmukh
*  email  : rushi.dm@gmail.com
*  date   : 08-Dec-2019
*
* Testing the dynamic array data-structure. 
* 
* This test code demonstrates the possibility of using already existing C++ standard library functions such as std::sort, std::find etc with the custom data-structure and its iterators.
*
* 
*/ 
#include <assert.h>
#include <iostream>
#include "DynamicArray.h"
#include <string>
#include <algorithm>

using namespace std;

int main()
{
	DynamicArray<int> idynarr{1, 2, 3, 4};
	assert(idynarr.size() == 4);
	assert(idynarr[0] == 1);

	DynamicArray<string> names {"Ramesh"};
	assert(names.size() == 1);

	names.append({"Kavitha", "Mahesh"});
	assert(names.size() == 3);
	assert(names[2] == "Mahesh");

	names.append({"Tom"});
	assert(names.size() == 4);

	names[3] = "Robert";

	cout << endl;
	cout << "names before sotring = [ ";
	for(auto& element: names)
		cout << element << " " ;
	cout << "]";

	std::sort(names.begin(), names.end());

	cout << endl << "\nnames after sorting = [ ";
	auto itr = names.begin();
	while(itr != names.end())
	{
		cout << *itr << " ";
		itr++;
	}

	cout << "]";

	auto itr1 = std::find(names.begin(), names.end(), "Kavitha");
	cout << "\n\nresult of find = " << *itr1;

	itr1+=2;
	cout << "\n\nname after incrementing iterator with 2 = " << *itr1;

	itr1--;
	cout << "\n\n name after decrementing iterator = " << *itr1;
}
