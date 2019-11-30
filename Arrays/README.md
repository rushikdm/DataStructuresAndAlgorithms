# Arrays

## When to use arrays in C++

	1. The program needs to manage multiple elements of same type. 

	2. The size of the elements is fixed and known at compile time. 

There are several scenario in which multiple elements of same type needs to be managed and size of the elements is fixed. In such cases C++ arrays can be used. Following are some such examples along with C++ code snippet using arrays:

**Triangle always has 3 vertices**

```cpp
class Triangle
{
	Point vertices[3];

	// rest of the implementation . . . 
};
```
	
**Calendar application needs to have 7 weekdays and 12 months**

```cpp
string weekdays[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
string months[] = {"January", "February","March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
```

**Any GUI application that needs to display buttons for digits from 0 to 9**

```cpp
Button digits[] = {Button("0"), Button("1"), Button("2"), Button("3"), Button("4"), Button("5"), Button("6"), Button("7"), Button("8"), Button("9")};
```

**15 puzzle game**

```cpp
class Puzzle15
{
	short cells[4][4];
	
	// rest of the implementation . . . 
};
```

**Homogeneous 3D transformation matrix in computer graphics application**

```cpp
class Transformation3D
{
	double mat[4][4];
	
	// rest of the implementation . . . 
};
```

**Syntax for C++ arrays**

Creates an int array of length 5. All int elements in array have garbage values.
```cpp
int numbers[5]; 
```

Creates a static int array of length 5. All int elements in array are automatically initialized to 0 because of the static declaration.
```cpp
static int numbers[5]; 
```

Creates an int array of length 5. All int elements in array are initialized to zero.
```cpp
int numbers[5] = {}; 
```

Same as above; **=** can be omitted.
```cpp
int numbers[5]{}; 
```

Creates an int array of length 5. All int elements in array are initialized to values specified in right hand side.
```cpp
int numbers[5] = {1, 2, 3, 4, 5}; 
```
Same as above; **=** can be omitted.
```cpp
int numbers[5]{1, 2, 3, 4, 5}; 
```

If array length is not specified, C++ compiler automatically figures out the length from the values specified in right hand side.
```cpp
int numbers[] = {1, 2, 3, 4, 5}; 
```

Same as above; **=** can be omitted.
```cpp
int numbers[]{1, 2, 3, 4, 5}; 
```

If right hand side contains less values than the length of the array, then, rest of the elements are initialized to zero (for basic types such as int, double etc.).
```cpp
int numbers[5] = {1, 2}; // numbers contains {1, 2, 0, 0, 0}
```

Same as above; **=** can be omitted.
```cpp
int numbers[5]{1, 2}; // numbers contains {1, 2, 0, 0, 0}
```
In C++ it is also possible to create arrays of objects. Let us consider a Point class representing a 2 dimensional point as follows:

```cpp
class Point
{
  double x;
  double y;
  
  public:
    Point():x(0), y(0) { }
    Point(const double ix, const double iy) : x(ix), y(iy) { }
    
  // rest of the implementation
};
```
The various ways of creating array of Point objects is mentioned below:

Following expression creates array with 2 Point objects. Default constructor is automatically invoked to create objects.
```cpp
Point points[2];
```
Following expression shows the way to create Point objects by invoking other than default constructor:
```cpp
Point points[2]{Point(0, 0), Point(2,3)};
```

From C++11 onwards, we can have uniform initialization as follows:
```cpp
Point points[2]{{0, 0}, {2,3}};
```
### Advantages of arrays

1. Simple to create and use.
2. The memory allocation for array elements is contineous. Hence fast random access behavior, guarantees O(1) runtime.
3. Contineous memory allocation for array elements also reduces the possibility of cache misses.
4. No need to bother about memory allocation and deallocation, compiler handles it automatically. Hence no chance of memory leaks.

### Disadvantages of arrays

**Array decay problem**
The array length can determined as follows:
```cpp
int numbers[5]{1, 2, 3, 4, 5};
const size_t len = sizeof(numbers)/sizeof(numbers[0]);
std::cout << len ; // outputs 5
```
Above code works fine because the **numbers** array declaration and sizeof operator on it is called in the same scope. But this fails when array is declared and intialized in one scope and sizeof operator is invoked on it in another scope. Consider following such scenario:
```cpp
int numbers[5]{1, 2, 3, 4, 5};
int sum = GetSum(numbers);
```
GetSum is another function defined as follows:
```cpp
int GetSum(int[] numbers)
{
  const size_t len = sizeof(numbers)/sizeof(numbers[0]); // compilation error
}
```

Hence, avoid this problem, it is always required to pass the array length information as well along with the array as follows:
```cpp
const int len{5};
int numbers[len] {1, 2, 3, 4, 5};
int sum = GetSum(numbers, len);
std::cout << sum; // outputs 15
```
GetSum is another function defined as follows:
```cpp
int GetSum(int numbers[], const int len)
{
  int sum{0};
  for(int I=0;I<len;++I)
    sum += numbers[I];
  return sum;
}
```
This works fine; array decay issue is taken care of. But it is combursome to always pass extra information of array length wheneber array needs to be passed as input to some other function.

C++ standard library provides array<> template and it can be used as an alternative to above approach of solving array decay problem. array<> template is a container, hence using it can have some additional benefits compared to using bare array. Following code shows usage of array<> template:

```cpp
#include <array>
int GetSum(array<int, 5> & numbers);

int main()
{
  array<int, 5> numbers {1, 2, 3, 4, 5};
  int sum = GetSum(numbers);
  std::cout << sum; // outputs 15
}

int GetSum(array<int, 5> & numbers)
{
  int sum{0};
  for(int num : numbers)
    sum += num;
  return sum;
}
```
