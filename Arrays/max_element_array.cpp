/* author: Rushikesh Keshavrao Deshmukh
 * date  : 01-Dec-2019
 * email : rushi.dm@gmail.com
 *
 * Code illustrating usage of std::max_element function to find the maximum number from an unsorted integer array.
*/

#include <iostream>
#include <algorithm>

int main()
{
  const int len = 5;
  int numbers[len]{6,3,9,4,8};
  int * pmax = std::max_element(numbers, numbers+len);
  std::cout << *pmax; // outputs 9
  return 0;
}
