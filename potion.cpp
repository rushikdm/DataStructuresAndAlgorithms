/**
 * @author : Rushikesh Keshavrao Deshmukh
 * @email  : rushissv@gmail.com
 *
 * Write a program to determine proportions for a potion.
 * The potion has n ingredients.
 * (n-1) inputs for the relative proportions of two ingredients are given as follows:
 *     index1, index2, amount1, amount2
 *
 *     index1 denotes the index of ingredient 1
 *     index2 denotes the index of ingredient 2
 *     amount1 denotes the amount of ingredient 1
 *     amount2 denotes the amount of ingredient 2
 *
 * Determine the proportions of all the ingredients if unique solution exists.
 * The proportions of all ingredients should add to 1.0 if solution exists
 * If solution does not exist or if there is no unique solution, all the proportions should be zero.
 *
 * The program should be able to determine if unique solution exists or not.

Sample input:

3
0 1 9 4
2 1 1 2

3 value mentioned in first line is the total number of ingredients in potion.
Second line indicates that the relative proportions of ingredients 0, 1 should be 9:4
Similarly last line indicates that the relative proportions of ingredients 2, 1 should be 1:2
The final proportions of all ingredients should respect all the given relative proportions if solution exists.
The answer to above problem is as follows:
(9/15)    (4/15)    (2/15)
0.6000    0.2667    0.1333


Constraints:
2 < N < 200
0 < P < 10

Where N is the number of ingredients in potion.
P is the proportion amount for the ingredient specified in the inputs.

* Approach 1 : Depth first search traversal (DFS) algorithm on the graph of ingradients.

This graph has ingredients as nodes and relative proportions given in input as edges between the nodes.
Since there are N nodes and (N-1) edges, following properties can be deduced:
   - For valid inputs, it must form a tree without cycles.
   - For valid inputs, all the nodes must be connected.
If above conditions are satisfied, then, problem can be solved and has unique solution.
Otherwise, unique solution cannot be found.
To perform depth first traversal, connections data-structure needs to be built using the inputs.
This DFS algorithm is implemented using determineProportionsUsingDFS() function in this file.

* Approach 2: Incremental formation & merging of disjoint sets for ingredients.

Assume the mathematical inductive step k where the existing proportions of all the ingredients in potion are properly defined.
These ingredients may belong to one or multiple disjoint groups.
The potion may contain some ingredients for which the proportions are not yet defined and they don't belong to any group.

Now we need to add new proprtion entry for two ingredients.

Following are the various possibilities:

1. Both the ingredients don't belong to any group.
   Form a new group and add both ingredients to this new group.

2. One of the ingredients don't belong to any group and the other belongs to existing group.
   Add the ingredient with missing group to the existing group.
   Modify the proportion values to match all the proportion constraints.

3. Both ingredients belong to already existing different groups.
   Modify the proportion values for both the groups to match all the proportion constraints.
   Merge both these groups.

4. Both ingredients belong to already existing same group.
   Invalid input. This leads to disjoint groups because we only have (N-1) entries and N ingredients.

At the end if the the total number of unique groups in potion is not equal to one, report that no solution exists.
Otherwise determine the proportions for each ingredient in potion based on its amount in potion.

Approach 2 is implemented using determineProportions() function in this file.
    Time complexity  = O(N^2)
    Space complexity = O(N)

*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <assert.h>
#include <queue>

using namespace std;

struct Proportion
{
	struct Ingredient
	{
		int index;
		int amount;
	};

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
);

static bool determineProportions
(
	const int N,
	const vector<Proportion>& iProportions,
	vector<double>& oProportions
);

class Potion
{
	struct Ingredient
	{
		int amount;
		int group;
	};

	vector<Ingredient> ingredients;
	int maxGroup = 1;

public:

	Potion(const int N) : ingredients(N) {}

	bool addProportion(const Proportion& iProportion)
	{
		const Proportion::Ingredient one = iProportion.one;
		const Proportion::Ingredient two = iProportion.two;

		if (!isGroupAssigned(one.index) && !isGroupAssigned(two.index))
		{
			addNewGroup(iProportion);
			return true;
		}

		bool oneAssigned = false;
		Proportion::Ingredient assigned;
		Proportion::Ingredient unassigned;

		if (isGroupAssigned(one.index) && !isGroupAssigned(two.index))
		{
			oneAssigned = true;
			assigned = one;
			unassigned = two;
		}
		else if (!isGroupAssigned(one.index) && isGroupAssigned(two.index))
		{
			oneAssigned = true;
			assigned = two;
			unassigned = one;
		}

		if (oneAssigned)
		{
			int existingAssignedAmount = getAmount(assigned.index);
			multiply(assigned.amount, getGroup(assigned.index));
			set({ unassigned.index, unassigned.amount * existingAssignedAmount }, getGroup(assigned.index));
			return true;
		}

		if (isGroupAssigned(one.index) && isGroupAssigned(two.index))
		{
			if (areGroupsSame(one.index, two.index))
				return false;

			const int value1 = getAmount(one.index);
			const int value2 = getAmount(two.index);

			multiply(one.amount * value2, getGroup(one.index));
			multiply(two.amount * value1, getGroup(two.index));
			modifyGroup(getGroup(two.index), getGroup(one.index));

			return true;
		}

		return false;
	}

	bool isSingleGroup() const
	{
		const int group = ingredients[0].group;
		return std::all_of(ingredients.begin(), ingredients.end(), [&group](const Ingredient & ingredient)-> bool {
			return ingredient.group == group; });
	}

	void getProportions(vector<double>& oProportions) const
	{
		assert(oProportions.size() == ingredients.size());
		const int N = oProportions.size();

		int sm = 0;
		for (int i = 0; i < N; ++i)
			sm += ingredients[i].amount;

		for (int i = 0; i < N; ++i)
			oProportions[i] = (double)ingredients[i].amount / sm;
	}

private:

	bool isGroupAssigned(const int index) const
	{
		return ingredients[index].group != 0;
	}

	int getAmount(const int index) const
	{
		return ingredients[index].amount;
	}

	int getGroup(const int index) const
	{
		return ingredients[index].group;
	}

	void setGroup(const int index, const int group)
	{
		ingredients[index].group = group;
	}

	void set(const Proportion::Ingredient & ingredient, const int group)
	{
		ingredients[ingredient.index].amount = ingredient.amount;
		ingredients[ingredient.index].group = group;
	}

	void addNewGroup(const Proportion & proportion)
	{
		set(proportion.one, maxGroup);
		set(proportion.two, maxGroup);
		++maxGroup;
	}

	bool areGroupsSame(const int index1, const int index2) const
	{
		return ingredients[index1].group == ingredients[index2].group;
	}

	void multiply(const int m, const int group)
	{
		for (auto& ingredient : ingredients)
		{
			if (group != ingredient.group)
				continue;
			ingredient.amount *= m;
		}
	}

	void modifyGroup(const int fromGroup, const int toGroup)
	{
		for (auto& ingredient : ingredients)
		{
			if (ingredient.group == fromGroup)
				ingredient.group = toGroup;
		}
	}

	friend ostream& operator << (ostream & os, const Potion & potion);
};

bool determineProportions
(
	const int N,
	const vector<Proportion> & iProportions,
	vector<double> & oProportions
)
{
	assert(iProportions.size() == (oProportions.size() - 1));
	assert(N == (int)oProportions.size());

	Potion potion(N);
	for (int i = 0; i < (N - 1); ++i)
	{
		if (!potion.addProportion(iProportions[i]))
			return false;
	}

	if (!potion.isSingleGroup())
		return false;

	potion.getProportions(oProportions);
	return true;
}

bool determineProportionsUsingDFS
(
	const int N,
	const vector<Proportion> & iProportions,
	vector<double> & oProportions
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

	vector<Proportion::Ingredient> ingredients;
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

			const Proportion::Ingredient& current = (index == proportion.one.index) ? proportion.one : proportion.two;
			assert(current.index == index);

			const Proportion::Ingredient & adj = (index == proportion.one.index) ? proportion.two : proportion.one;

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
	auto sort_lambda = [](const Proportion::Ingredient & ingredient1, const Proportion::Ingredient & ingredient2) -> bool {
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
	//const bool success = determineProportions(N, iProportions, oProportions);
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
