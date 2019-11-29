# Arrays

## When to use arrays in C++

	1. The program needs to manage multiple elements of same type. 

	2. The size of the elements is fixed and known at compile time. 

There are several scenario in which multiple elements of same type needs to be managed and size of the elements is fixed. In such cases C++ arrays can be used. Following are some such examples along with possible C++ implementation using arrays:

### Triangle always has 3 vertices.

```cpp
class Triangle
{
	Point vertices[3];

	// rest of the implementation . . . 
};
```
	
### Calendar application needs to have 7 weekdays and 12 months.

```cpp
string weekdays[7] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
string months[12] = {"January", "February","March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
```

### Any GUI application that needs to display buttons for digits from 0 to 9.

```cpp
Button digits[10] = {Button("0"), Button("1"), Button("2"), Button("3"), Button("4"), Button("5"), Button("6"), Button("7"), Button("8"), Button("9")};
```

### 15 puzzle game

```cpp
class Puzzle15
{
	short cells[4][4];
	
	// rest of the implementation . . . 
};
```

### Homogeneous 3D transformation matrix in computer graphics application

```cpp
class Transformation3D
{
	double mat[4][4];
	
	// rest of the implementation . . . 
};
