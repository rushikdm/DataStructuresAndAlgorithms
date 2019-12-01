/* author: Rushikesh Keshavrao Deshmukh
 * date  : 01-Dec-2019
 * email : rushi.dm@gmail.com
 *
 * Code illustrating usage of std::binary_search function to find if a given number exists in a sorted integer array.
 * The array needs to be sorted before calling binary_search function.
*/

#include <iostream>
#include <algorithm>

int main()
{
	int numbers[]{1, 2, 4, 6, 7, 9, 11, 13, 15, 20};
	const int len = sizeof(numbers)/sizeof(numbers[0]);
	bool found = std::binary_search(numbers, numbers+len, 9);
	if(found)
		std::cout << "Found 9";
	else
		std::cout << "9 not found.";
	
	found = std::binary_search(numbers, numbers+len, 8);
	if(found)
		std::cout << "Found 8";
	else
		std::cout << "\n8 not found.";
	
	return 0;
}
