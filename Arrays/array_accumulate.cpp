/* author: Rushikesh Keshavrao Deshmukh
 * date  : 01-Dec-2019
 * email : rushi.dm@gmail.com
 *
 * Code illustrating usage of std::accumulate function to sum all elements of integer array.
*/

#include <iostream>
#include <numeric>

int main()
{
	const int len = 5;
	int numbers[len]{1,2,3,4,5};
	int sum = std::accumulate(numbers, numbers+len, 0);
	std::cout << sum; // outputs 15
	return 0;
}
