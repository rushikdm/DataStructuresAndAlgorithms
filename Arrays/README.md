# Arrays

## When to use arrays in C++

	1. The program needs to have multiple elements of same type. 

	2. The size of the elements is known at compile time. 

	3. The program does not need to change the size of the array. 

	4. The treatment to be applied is same for all the elements of the array.

Items 1,2,3 mentioned above are enforced by the C++ language. Item 4 is not enforced by the C++ language itself, but, it is mentioned from good design perspective.

For example:

```cpp
class Triangle
{
	Point points[3];
	...
};
```

Triangle class needs to have exactly 3 Point objects in it. In this case there is no need to alter the size of the points array, triangle always needs 3 points only, no more, no less. So having an array of points in this case is a good choice.  

Now let us consider the design of Point class. We will assume 2 dimensional point in this case. There are two possibilities as follows:

```cpp
class Point 
{
	double coordinates[2];
	...
};
```

or 

```cpp
class Point 
{
	double x;
	double y;
};
```
