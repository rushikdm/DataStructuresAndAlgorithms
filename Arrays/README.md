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

**Quick syntax for C++ arrays**

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
