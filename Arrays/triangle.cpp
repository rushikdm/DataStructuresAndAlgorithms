/* author: Rushikesh Keshavrao Deshmukh
 * date  : 01-Dec-2019
 * email : rushi.dm@gmail.com
 *
 * Code illustrating usage of std::min_element and std::max_element functions to find left most and right most vertex of a triangle.
*/

#include <iostream>
#include <algorithm>

struct Point 
{
	double x;
	double y;
};

class Triangle
{
	Point vertices[3];

	public:
	  
	  Triangle(Point v1, Point v2, Point v3):vertices{v1, v2, v3} { }

	  Point GetLeftMostVertex()
	  {
		auto leftmostPt_lambda = [](const Point & p1, const Point & p2) { return p1.x < p2.x; };
		Point * leftmostPt = std::min_element(vertices, vertices+3, leftmostPt_lambda);
		return *leftmostPt;
	  }

	  Point GetRightMostVertex()
	  {
		  auto rightmostPt_lambda = [](const Point & p1, const Point & p2) { return p1.x < p2.x; };
		  Point * rightmostPt = std::max_element(vertices, vertices+3, rightmostPt_lambda);
		  return * rightmostPt;
	  }
};

int main()
{
	Triangle tri{{0, 0}, {-2, 6}, {3, 3}};
	Point pt = tri.GetLeftMostVertex();
	std::cout << "\nLeft most vertex of triangle = [ " << pt.x << " " << pt.y << " ]";

	pt = tri.GetRightMostVertex();
	std::cout << "\nRight most vertex of triangle = [ " << pt.x << " " << pt.y << " ]";
}

