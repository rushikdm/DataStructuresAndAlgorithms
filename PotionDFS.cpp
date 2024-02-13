/**
 * @author : Rushikesh Keshavrao Deshmukh
 * @email  : rushissv@gmail.com
 * @date   : 10-Feb-2024

This program is written to solve the following problem:
Consider a potion(recipe) with N ingredients. 
The objective is to determine the proportions of all the N ingredients in the potion.
Input consists of (N-1) lines. Each line has four integer values as follows:

      index_i, index_j, amount_i, amount_j

index_i denotes the index of ingredient i
index_j denotes the index of ingredient j
amount_i denotes the relative proportionate amount of ingredient i
amount_j denotes the relative proportionate amount of ingredient j

Where
0 <= i, j < N
0 < amount_i, amount_j < 10
2 < N < 200

Above four integer values indicate the relative proportions of the two ingredients i, j.
Like this (N-1) inputs are given for different pair of ingredients.

The objective is to determine the proportions of all the N ingredients in potion. 
If unique solution exists, then, the output for proportions of all N ingredients should add to 1.0

The inputs may be invalid or are not sufficient to determine the unique solution.
In such cases, the program should report that unique solution does not exist.
Otherwise program should output the proportion values for all N ingredients.

If solution exists, the final proportion values of all the N ingredients must satisfy all the (N-1) relative proportions given in the inputs.

Sample input:

3
0 1 9 4
2 1 1 2

First line in the input (3 in this case) indicates the total number of ingredients in potion.
After the first line, (N-1) lines follow. In this case, (3-1) = 2 lines follow.
Each line that follows specifies the relative proportion of two ingredients.
Second line mentioned above specifies that the relative proportion of ingredients 0, 1 must be 9:4
Similarly, last line specifies that the relative proportion of ingredients 2, 1 must be 1:2

The answer to above problem is as follows:
(9/15)    (4/15)    (2/15)
0.6000    0.2667    0.1333

Above final proportion values satisfy all the relative proportion values mentioned in the inputs.

Solution approach : Depth first search traversal (DFS) algorithm on the graph of ingradients.

A graph is formed with ingredients as nodes and relative proportions given in input as edges between the nodes.
Since there are N nodes and (N-1) edges, following properties can be deduced:
   - For valid inputs, it must form a tree without cycles.
   - For valid inputs, it must form a single connected graph.

If above conditions are satisfied, then, problem can be solved and it has unique solution.
Otherwise, unique solution does not exists.

To perform DFS traversal, adjacency list graph data-structure needs to be formed using the given inputs.
DFS graph traversal begins with node for ingredient with zero index. 
And the initial solution contains proportion value of 1 for this ingredient with zero index.
As the nodes are visited, the new ingredient is added to the solution.
The nodes are visited via the edges that represent relative proportions for pair of ingredients.
DFS traversal is done in such a way that one of the ingredients from the edge is already present in the solution.
The other ingredient will be added to the solution during the traversal.
While adding the new ingredient to the solution, the relative proportion values for the ingredients already existing in the solution must be maintained.
Also, the new ingredient needs to be added by maintaining its relative proportion value contained in the edge of the graph.

If the total number of nodes visited after DFS graph traversal is equal to N, then solution exists.
Otherwise, solution does not exists. 

The DFS graph traversal algorithm to solve this problem is implemented in determineProportionsUsingDFS() function in this file.

*/
#include <algorithm>
#include <assert.h>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Ingredient
{
	int index = 0;
	int amount = 0;
};

struct Proportion
{
	Ingredient one;
	Ingredient two;
};

static istream& operator >> (istream& is, Proportion& proportion)
{
	is >> proportion.one.index;
	is >> proportion.two.index;
	is >> proportion.one.amount;
	is >> proportion.two.amount;

	return is;
}

static bool determineProportionsUsingDFS
(
	const int N,
	const vector<Proportion>& iProportions,
	vector<double>& oProportions
)
{
	assert(iProportions.size() == (oProportions.size() - 1));
	assert(N == (int)oProportions.size());

	vector<vector<int>> connections(N);
	for (int i = 0; i < (N - 1); ++i)
	{
		connections[iProportions[i].one.index].push_back(i);
		connections[iProportions[i].two.index].push_back(i);
	}

	vector<Ingredient> ingredients;
	ingredients.reserve(N);
	ingredients.push_back({ 0,1 });

	vector<bool> visited(N);
	visited[0] = true;

	queue<int> q;
	q.push(0);

	int count = 1;
	while (!q.empty())
	{
		const int index = q.front();
		q.pop();

		for (int i = 0; i < (int)connections[index].size(); ++i)
		{
			const Proportion& proportion = iProportions[connections[index][i]];

			const Ingredient& current = (index == proportion.one.index) ? proportion.one : proportion.two;
			assert(current.index == index);

			const Ingredient & adj = (index == proportion.one.index) ? proportion.two : proportion.one;

			if (visited[adj.index])
				continue;

			q.push(adj.index);
			visited[adj.index] = true;

			int currentAmount = -1;

			for (int j = 0; j < (int)ingredients.size(); ++j)
			{
				if (ingredients[j].index == index)
					currentAmount = ingredients[j].amount;

				ingredients[j].amount *= current.amount;
			}

			assert(currentAmount > 0);
			ingredients.push_back({ adj.index, adj.amount * currentAmount });

			++count;
		}
	}

	if (count != N)
		return false;

	assert(N == (int)ingredients.size());

	auto sort_lambda = [](const Ingredient & ingredient1, const Ingredient & ingredient2) -> bool {
		return ingredient1.index < ingredient2.index;
	};
	std::sort(ingredients.begin(), ingredients.end(), sort_lambda);

	for (int i = 0; i < N; ++i)
	{
		if (ingredients[i].index != i)
			return false;
	}

	int sum = 0;
	for (int i = 0; i < N; ++i)
		sum += ingredients[i].amount;

	for (int i = 0; i < N; ++i)
		oProportions[i] = (double)ingredients[i].amount / sum;

	return true;
}

int main()
{
	int N;
	cin >> N;

	vector<Proportion> iProportions(N - 1);

	for (int i = 0; i < (N - 1); ++i)
		cin >> iProportions[i];

	vector<double> oProportions(N);
	const bool success = determineProportionsUsingDFS(N, iProportions, oProportions);

	if (!success)
	{
		cout << "No solution exists." << endl;
		return 0;
	}

	cout << "Proportions = \n";
	for (int i = 0; i < N; ++i)
		cout << oProportions[i] << " ";
	cout << endl;

	return 0;
}
