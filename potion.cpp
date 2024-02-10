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
 *     index2 denotres the index of ingredient 2
 *     amount1 denotes the amount of ingredient 1
 *     amount2 denotes the amount of ingredient 2
 * 
 * Determine the proportions of all the ingredients if unique solution exists.
 * The proportions of all ingredients should add to 1.0 if solution exists
 * If solution does not exist or if there is no unique solution, all the proportions should be zero.
 * 
 * The program should be able to determine if unique solution exists or not.
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <array>

using namespace std;

struct Input
{
	int n=0;
	vector<array<int, 4>> v;
};

istream& operator >> (istream& is, Input& input)
{
	is >> input.n;
	input.v.reserve(input.n-1);
	for(int i=0;i<(input.n-1);++i)
		is >> input.v[i][0] >> input.v[i][1] >> input.v[i][2] >> input.v[i][3];
	return is;
}

bool determinePotionIngredientsProportion(const Input& input, vector<double>& proportions);

class Potion;

ostream& operator << (ostream& os, const Potion& potion);

class Potion
{
	vector<pair<int, int>> v;
	int maxGroup = 1;
	
	public:
	
	Potion(const int N) : v(N) {}
	
	bool isGroupAssigned(const int index)
	{
		return v[index].second != 0;
	}
	
	int getAmount(int index)
	{
		return v[index].first;
	}
	
	int getGroup(int index)
	{
		return v[index].second;
	}
	
	void setGroup(int index, int group)
	{
		v[index].second = group;
	}
	
	void set(int index, int amount, int group)
	{
		v[index].first = amount;
		v[index].second = group;
	}
	
	void addNewGroup(int index1, int amount1, int index2, int amount2)
	{
		set(index1, amount1, maxGroup);
		set(index2, amount2, maxGroup);
		++maxGroup;
	}
	
	bool areGroupsSame(int index1, int index2)
	{
		return v[index1].second == v[index2].second;
	}
	
	void multiply(int m, int group)
	{
		for(auto& pr: v)
		{
			if(group != pr.second)
				continue;
			pr.first *= m;
		}
	}
	
	bool isSingleGroup()
	{
		int group = v[0].second;
		return std::all_of(v.begin(), v.end(), [&group](const pair<int, int>& pr)-> bool{ 
			return pr.second == group;});
	}
	
	friend ostream& operator << (ostream& os, const Potion& potion);
};

ostream& operator << (ostream& os, const Potion& potion)
{
	const int n = potion.v.size();
	os << n << "\n";
	for(int i=0;i<n;++i)
		os << i << " : Group = " << potion.v[i].second << ", Amount = " << potion.v[i].first << "\n";
	os.flush();
	return os;
}

bool determinePotionIngredientsProportion(const Input& input, vector<double>& propotions )
{
	const int N = input.n;
	Potion potion(N);
	for(int i=0;i<(N-1);++i)
	{
		int index1 = input.v[i][0];
		int index2 = input.v[i][1];
		int amount1 = input.v[i][2];
		int amount2 = input.v[i][3];
		
		if(!potion.isGroupAssigned(index1) && !potion.isGroupAssigned(index2))
		{
			potion.addNewGroup(index1, amount1, index2, amount2);
			continue;
		}
		
		bool oneAssigned = false;
		int assignedIndex, unassignedIndex, assignedAmount, unassignedAmount;
		
		if(potion.isGroupAssigned(index1) && !potion.isGroupAssigned(index2))
		{
			oneAssigned = true;
			assignedIndex = index1;
			unassignedIndex = index2;
			assignedAmount = amount1;
			unassignedAmount = amount2;
		}
		else if(!potion.isGroupAssigned(index1) && potion.isGroupAssigned(index2))
		{
			oneAssigned = true;
			assignedIndex = index2;
			unassignedIndex = index1;
			assignedAmount = amount2;
			unassignedAmount = amount1;
		}
		
		if(oneAssigned)
		{
			int existingAssignedAmount = potion.getAmount(assignedIndex);
			potion.multiply(assignedAmount, potion.getGroup(assignedIndex));
			potion.set(unassignedIndex, unassignedAmount*existingAssignedAmount, potion.getGroup(assignedIndex));
			continue;
		}
		
		else if(potion.isGroupAssigned(index1) && potion.isGroupAssigned(index2))
		{
			if(potion.getGroup(index1) == potion.getGroup(index2))
				break;
			
			int value1 = potion.getAmount(index1);
			int value2 = potion.getAmount(index2);
			
			potion.multiply(amount1*value2, potion.getGroup(index1));
			potion.multiply(amount2*value1, potion.getGroup(index2));
		}
	}
	
	//cout << potion;

	if(potion.isSingleGroup())
	{
		int sm = 0;
		for(int i=0;i<N;++i)
			sm += potion.getAmount(i);
		
		for(int i=0;i<N;++i)
			propotions[i] = (double)potion.getAmount(i)/sm;
		
		return true;
	}
	
	return false;
}

int main()
{
	Input input;
	cin >> input;
	vector<double> proportions(input.n);
	determinePotionIngredientsProportion(input, proportions);
	
	for(int i=0;i<input.n;++i)
		cout << proportions[i] << " ";
	cout << endl;
	
	return 0;
}
