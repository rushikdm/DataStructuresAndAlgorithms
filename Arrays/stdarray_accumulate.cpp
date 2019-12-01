/* author: Rushikesh Keshavrao Deshmukh
 * date  : 01-Dec-2019
 * email : rushi.dm@gmail.com
 *
 * Code illustrating usage of std::accumulate function to sum all elements of std::array of integer type.
*/

#include <iostream>
#include <array>
#include <numeric>

int main()
{
	std::array<int, 5> numbers{1, 2, 3, 4, 5};
	int sum = std::accumulate(numbers.begin(), numbers.end(), 0);
	std::cout << sum; // outputs 15
	return 0;
}
