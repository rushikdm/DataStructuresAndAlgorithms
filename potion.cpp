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

Solution Approach: Incremental formation & merging of disjoint sets for ingredients.

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

This approach is implemented in determineProportions() function in this file.
    Time complexity  = O(N^2)
    Space complexity = O(N)
*/
#include <algorithm>
#include <assert.h>
#include <iostream>
#include <queue>
#include <vector>

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
};

static bool determineProportions
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

int main()
{
	int N;
	cin >> N;

	vector<Proportion> iProportions(N - 1);

	for (int i = 0; i < (N - 1); ++i)
		cin >> iProportions[i];

	vector<double> oProportions(N);
	const bool success = determineProportions(N, iProportions, oProportions);

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
