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


* 
* Analysis:
*
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

 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <assert.h>

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

static bool determineProportions
(
	const int N, 
	const vector<Proportion>& iProportions, 
	vector<double>& oProportions
);

class Potion;

static ostream& operator << (ostream& os, const Potion& potion);

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
		const int index1  = iProportion.one.index;
		const int index2  = iProportion.two.index;
		const int amount1 = iProportion.one.amount;
		const int amount2 = iProportion.two.amount;
		
		if(!isGroupAssigned(index1) && !isGroupAssigned(index2))
		{
			addNewGroup(iProportion);
			return true;
		}
		
		bool oneAssigned = false;
		int assignedIndex, unassignedIndex, assignedAmount, unassignedAmount;
		
		if(isGroupAssigned(index1) && !isGroupAssigned(index2))
		{
			oneAssigned = true;
			assignedIndex = index1;
			unassignedIndex = index2;
			assignedAmount = amount1;
			unassignedAmount = amount2;
		}
		else if(!isGroupAssigned(index1) && isGroupAssigned(index2))
		{
			oneAssigned = true;
			assignedIndex = index2;
			unassignedIndex = index1;
			assignedAmount = amount2;
			unassignedAmount = amount1;
		}
		
		if(oneAssigned)
		{
			int existingAssignedAmount = getAmount(assignedIndex);
			multiply(assignedAmount, getGroup(assignedIndex));
			set({unassignedIndex, unassignedAmount*existingAssignedAmount}, getGroup(assignedIndex));
			return true;
		}
		
		if(isGroupAssigned(index1) && isGroupAssigned(index2))
		{
			if(getGroup(index1) == getGroup(index2))
				return false;
			
			const int value1 = getAmount(index1);
			const int value2 = getAmount(index2);
			
			multiply(amount1*value2, getGroup(index1));
			multiply(amount2*value1, getGroup(index2));
			modifyGroup(getGroup(index2), getGroup(index1));
			
			return true;
		}
		
		return false;
	}
	
	bool isSingleGroup() const
	{
		const int group = ingredients[0].group;
		return std::all_of(ingredients.begin(), ingredients.end(), [&group](const Ingredient& ingredient)-> bool{ 
			return ingredient.group == group;});
	}
	
	void getProportions(vector<double>& oProportions) const
	{
		assert(oProportions.size() == ingredients.size());
		const int N = oProportions.size();
		
		int sm = 0;
		for(int i=0; i<N;++i)
			sm+= ingredients[i].amount;
		
		for(int i=0; i<N;++i)
			oProportions[i] = (double)ingredients[i].amount/sm;
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
	
	void set(const Proportion::Ingredient& ingredient, const int group)
	{
		ingredients[ingredient.index].amount = ingredient.amount;
		ingredients[ingredient.index].group = group;
	}
	
	void addNewGroup(const Proportion& proportion)
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
		for(auto& ingredient: ingredients)
		{
			if(group != ingredient.group)
				continue;
			ingredient.amount *= m;
		}
	}
	
	void modifyGroup(const int fromGroup, const int toGroup)
	{
		for(auto& ingredient: ingredients)
		{
			if(ingredient.group == fromGroup)
				ingredient.group = toGroup;
		}
	}
	
	friend ostream& operator << (ostream& os, const Potion& potion);
};

ostream& operator << (ostream& os, const Potion& potion)
{
	const int n = potion.ingredients.size();
	os << n << "\n";
	for(int i=0;i<n;++i)
		os << i << " : Group = " << potion.ingredients[i].group << ", Amount = " << potion.ingredients[i].amount << "\n";
	os.flush();
	return os;
}

bool determineProportions
(
	const int N,
	const vector<Proportion>& iProportions, 
	vector<double>& oProportions
)
{
	assert(iProportions.size() == (oProportions.size()-1));
	assert(N == (int)oProportions.size());
	
	Potion potion(N);
	for(int i=0;i<(N-1);++i)
	{
		if(!potion.addProportion(iProportions[i]))
			return false;
	}
	
	//cout << potion;

	if(!potion.isSingleGroup())
		return false;
		
	potion.getProportions(oProportions);
	return true;
}
	

int main()
{
	int N;
	cin >> N;
	
	vector<Proportion> iProportions(N-1);
	
	for(int i=0;i<(N-1);++i)
		cin >> iProportions[i];

	vector<double> oProportions(N);
	const bool success = determineProportions(N, iProportions, oProportions);
	
	if(!success)
	{
		cout << "No solution exists." << endl;
		return 0;
	}
	
	cout << "Proportions = \n";
	for(int i=0;i<N;++i)
		cout << oProportions[i] << " ";
	cout << endl;
	
	return 0;
}
