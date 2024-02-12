/*
 * Copyright (c) 2024.
 * @author : Rushikesh Keshavrao Deshmukh
 * @email: rushissv@gmail.com
 *
 * This file contains program to solve problem to determine proportions for a potion (recipe).
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


* Approach : Depth first search traversal (DFS) algorithm on the graph of ingradients.
This graph has ingredients as nodes and relative proportions given in input as edges between the nodes.
Since there are N nodes and (N-1) edges, following properties can be deduced:
  - For valid inputs, it must form a tree without cycles.
  - For valid inputs, all the nodes must be connected.
If above conditions are satisfied, then, problem can be solved and has unique solution.
Otherwise, unique solution cannot be found.

To perform depth first traversal, connections data-structure needs to be built using the inputs.
This DFS algorithm is implemented using determineProportionsUsingDFS() function in this file.
 */

package potion;

import java.text.NumberFormat;
import java.util.*;

public class Potion
{
    public static void main(String[] args)
    {
        List<Proportion> iProportions = readInputs();
        final int N = iProportions.size() + 1;

        Optional<List<Double>> oProportions = determineProportionsUsingDFS(N, iProportions);
        if (oProportions.isEmpty())
        {
            System.out.println("No solution exists.");
            return;
        }

        printSolution(oProportions.get());
    }

    private static Optional<List<Double>> determineProportionsUsingDFS(final int N, final List<Proportion> iProportions)
    {
        assert iProportions.size() == (N - 1);

        List<Double> proportions = Arrays.asList(new Double[N]);
        Collections.fill(proportions, 0.0);

        List<List<Integer>> connections = new ArrayList<>(N);
        for (int i = 0; i < N; ++i)
            connections.add(new ArrayList<>());

        for (int i = 0; i < (N - 1); ++i)
        {
            connections.get(iProportions.get(i).one.index).add(i);
            connections.get(iProportions.get(i).two.index).add(i);
        }

        List<Ingredient> ingredients = new ArrayList<>(N);
        ingredients.add(new Ingredient(0, 1));

        List<Boolean> visited = Arrays.asList(new Boolean[N]);
        Collections.fill(visited, false);
        visited.set(0, true);

        Queue<Integer> q = new ArrayDeque<>(N);
        q.add(0);
        int count = 1;

        while (!q.isEmpty())
        {
            final int index = q.remove();

            for (int i = 0; i < connections.get(index).size(); ++i)
            {
                final Proportion proportion = iProportions.get(connections.get(index).get(i));
                final Ingredient current = (proportion.one.index == index) ? proportion.one : proportion.two;

                assert current.index == index;

                final Ingredient adj = (proportion.one.index == index) ? proportion.two : proportion.one;

                if (visited.get(adj.index))
                    continue;

                visited.set(adj.index, true);
                q.add(adj.index);

                int currentAmount = -1;

                for (int j = 0; j < ingredients.size(); ++j)
                {
                    if(ingredients.get(j).index == index)
                        currentAmount = ingredients.get(j).amount;

                    ingredients.get(j).amount *= current.amount;
                }

                assert currentAmount > 0;
                
                ingredients.add(new Ingredient(adj.index, adj.amount * currentAmount));

                ++count;
            }
        }

        if (count != N)
            return Optional.empty();

        assert ingredients.size() == N;

        Collections.sort(ingredients, (ingredient1, ingredient2) -> ingredient1.index - ingredient2.index);
        for (int i = 0; i < ingredients.size(); ++i)
        {
            if (ingredients.get(i).index != i)
                return Optional.empty();
        }

        int sum = 0;
        for (int i = 0; i < ingredients.size(); ++i)
            sum += ingredients.get(i).amount;

        for (int i = 0; i < ingredients.size(); ++i)
            proportions.set(i, (double) ingredients.get(i).amount / sum);

        return Optional.of(proportions);
    }

    private static void printSolution(List<Double> proportions)
    {
        NumberFormat nf = NumberFormat.getInstance();
        nf.setMaximumFractionDigits(3);

        System.out.println();
        System.out.print("Proportions = [");

        for (int i = 0; i < (proportions.size() - 1); ++i)
            System.out.print(nf.format(proportions.get(i)) + ", ");

        System.out.print(nf.format(proportions.get(proportions.size() - 1)));
        System.out.println("]");
    }

    private static List<Proportion> readInputs()
    {
        Scanner scanner = new Scanner(System.in);
        final int N = scanner.nextInt();

        List<Proportion> iProportions = new ArrayList<>(N - 1);

        for (int i = 0; i < (N - 1); ++i)
        {
            final int index1 = scanner.nextInt();
            final int index2 = scanner.nextInt();
            final int amount1 = scanner.nextInt();
            final int amount2 = scanner.nextInt();

            Proportion proportion = new Proportion(index1, index2, amount1, amount2);
            iProportions.add(proportion);
        }

        return iProportions;
    }
}

class Ingredient
{
    Ingredient(int iIndex, int iAmount)
    {
        this.index = iIndex;
        this.amount = iAmount;
    }

    int index;
    int amount;
}

class Proportion
{
    Proportion(int index1, int index2, int amount1, int amount2)
    {
        one = new Ingredient(index1, amount1);
        two = new Ingredient(index2, amount2);
    }

    Ingredient one;
    Ingredient two;
}
