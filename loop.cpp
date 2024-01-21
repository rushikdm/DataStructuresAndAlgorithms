/* @author : Rushikesh Keshavrao Deshmukh
 * @email  : rushissv@gmail.com
 * @date   : 21-Jan-2024
 *
 * Question : Find the loop containing given line. Implement the following function:
 * void find_loop(vector<Line>& lines, Line line1, vector<Point>& loopPoints)
 * 
 * Approach:
 * Form adjacency list graph data structure from the given data i.e. vector<Line> lines;
 * Remove the edge for line1 from the graph.
 * Find the indices of vertices belonging to the line1 points.
 * Find the path between the vertices of line1 using breadth first search graph traversal algorithm.
 * Return the points for the path.
 * 
 * Input data for this program:
 11
2 2 0 3 5 0 
3 5 0 6 6 0 
6 6 0 8 4 0 
8 4 0 8 2 0
8 2 0 5 3 0
5 3 0 2 2 0
3 5 0 5 3 0
5 3 0 6 6 0
8 4 0 10 5 0 
5 3 0 5 1 0
5 1 0 8 2 0

8 2 0 8 4 0
*/

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
#include <assert.h>

using namespace std;

struct Point
{
	double x;
	double y;
	double z;

	bool same(Point& pt)
	{
		const double dx = x - pt.x;
		const double dy = y - pt.y;
		const double dz = z - pt.z;

		const double dist = sqrt(dx*dx+dy*dy+dz*dz);
		const double tolerance = 0.001;
		return dist < tolerance;
	}
};

struct Line
{
	Point pt1;
	Point pt2;
};

istream& operator >> (istream& is, Point& pt)
{
	is >> pt.x >> pt.y >> pt.z;
	return is;
}

ostream& operator << (ostream& os, Point& pt)
{
	os << pt.x << " " << pt.y << " " << pt.z;
	return os;
}

ostream& operator << (ostream& os, Line& line)
{
	os << line.pt1 << " to " << line.pt2;
	return os;
}

istream& operator >> (istream& is, Line& line)
{
	is >> line.pt1 >> line.pt2;
	return is;
}

struct AdjInfo
{
	int adj_point_index;
	int adj_line_index;
};

struct Vertex
{
	Point pt;
	vector<AdjInfo> adj;
};

struct Graph
{
	vector<Vertex> vertices;

	Point get_point(const int index)
	{
		return vertices[index].pt;
	}

	int get_point_index(Point& pt)
	{
		for(int i=0;i<vertices.size();++i)
		{
			if(pt.same(vertices[i].pt))
				return i;
		}

		return -1;
	}

	void add_line(Line& line, int line_index)
	{
		int index1 = get_point_index(line.pt1);
		if(index1 < 0)
		{
			index1 = vertices.size();
			Vertex v;
			v.pt = line.pt1;
			vertices.push_back(v);
		}

		int index2 = get_point_index(line.pt2);
		if(index2 < 0)
		{
			index2 = vertices.size();
			Vertex v;
			v.pt = line.pt2;
			vertices.push_back(v);
		}

		vertices[index1].adj.push_back({index2, line_index});
		vertices[index2].adj.push_back({index1, line_index});
	}

	void remove_edge(const int index1, const int index2)
	{
		auto itr = std::remove_if(vertices[index1].adj.begin(), vertices[index1].adj.end(), [&index2](AdjInfo& adj)->bool{return adj.adj_point_index == index2;});

		vertices[index1].adj.erase(itr, vertices[index1].adj.end());
	}

	bool find_path(int index1, int index2, vector<int>& path)
	{
		vector<bool> visited(vertices.size(), false);
		vector<int> prev(vertices.size(), -1);
		queue<int> q;
		q.push(index1);
		visited[index1] = true;
		bool found = false;
		while(!q.empty())
		{
			const int index = q.front();
			if(index == index2)
			{
				found = true;
				break;
			}
			q.pop();
			for(AdjInfo& adj: vertices[index].adj)
			{
				if(visited[adj.adj_point_index])
					continue;
				visited[adj.adj_point_index] = true;
				prev[adj.adj_point_index] = index;
				q.push(adj.adj_point_index);
			}
		}

		if(!found)
			return false;

		path.push_back(index1);
		int index = index2;
		while(index != index1)
		{
			assert(index != -1);
			path.push_back(index);
			index = prev[index];
		}

		return found;
	}
};

void create_adj_list_graph(vector<Line>& lines, Graph& graph)
{
	for(int i=0;i<lines.size();++i)
		graph.add_line(lines[i], i);
}

bool find_loop(vector<Line>& lines, Line line, vector<Point>& loop)
{
	Graph graph;
	create_adj_list_graph(lines, graph);

	int index1 = graph.get_point_index(line.pt1);
	if(index1 < 0)
		return false;
	int index2 = graph.get_point_index(line.pt2);
	if(index2 < 0)
		return false;

	graph.remove_edge(index1, index2);

	vector<int> path;
	if(!graph.find_path(index1, index2, path) || path.size() < 1)
		return false;
	
	loop.resize(path.size());
	std::transform(path.begin(), path.end(), loop.begin(), [&graph](int index) -> Point {return graph.get_point(index);});

	return true;
}

int main()
{
	int nLines;
	cin >> nLines;
	cout << "Number of lines = " << nLines << "\n";

	vector<Line> lines(nLines);
	Line line;
	while(nLines--)
	{
		cin >> line;
		cout << line << "\n";
		lines.push_back(line);
	}

	cin >> line;
	cout << "given line = " << line << "\n";
	vector<Point> loop;
	if(!find_loop(lines, line, loop) || loop.size() < 1)
	{
		cout << "\nNo loop found\n";
		return 0;
	}

	cout << "\nLoop points are:\n";
	for(Point& pt: loop)
		cout << pt << "\n";
	
	return 0;
}


