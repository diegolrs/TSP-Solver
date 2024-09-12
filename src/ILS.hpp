#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include "Solution.hpp"
#include "Insertion.hpp"
#include "Data.h"

//#define INFINITY ((float)(1e+300 * 1e+300))
#define RANDOM_SOLUTION_AMOUNT 3 

void LocalSearch(Solution *s){}

Solution Disturbance(Solution s)
{
    int minAmount = 2;
    int maxAmount = s.sequence.size()/10;
    int amountToApply = rand()%(maxAmount-minAmount +1) + minAmount;

    for(int i = 0; i < amountToApply; i++)
    {
        // two different numbers
        int a = rand()%(s.sequence.size()+1);
        int b = a;
        while(b == a)
            b = rand()%(s.sequence.size()+1);

        std::swap(s.sequence[a], s.sequence[b]);
    }

    return s;
}

Solution ConstructSolution(Data* data)
{
    Solution s;
    s.sequence = GenerateRandomNodes(RANDOM_SOLUTION_AMOUNT, 0, data->getDimension());
    std::vector<int> CL = GetReamingNodes(s.sequence, data->getDimension());

    while(!CL.empty())
    {
        std::vector<InsertionInfo> insertionCost = CalculateInsertionCost(s, CL, data);
        std::sort(insertionCost.begin(), insertionCost.end(), CompareInsertionInfo);
        double alpha = (double) rand() / RAND_MAX;
        int selected = rand() % ((int) ceil(alpha * insertionCost.size()));
        s.sequence.push_back(insertionCost[selected].insertedNode);
    }

    return s;
}

// Note: ILS means Iterated Local Search
Solution ILS(int maxIter, int maxIterIls, Data* data)
{
    Solution bestOfAll;
    bestOfAll.value = INFINITY;

    for(int i = 0; i < maxIter; i++)
    {
        Solution s = ConstructSolution(data);
        Solution bestLocalSolution = s;

        int iterIls = 0;
        while(iterIls <= maxIterIls)
        {
            LocalSearch(&s);

            if(s.value < bestLocalSolution.value)
            {
                bestLocalSolution = s;
                iterIls = 0;
            }

            s = Disturbance(bestLocalSolution);
            iterIls++;
        }

        if (bestLocalSolution.value < bestOfAll.value)
            bestOfAll = bestLocalSolution;
    }

    return bestOfAll;
}