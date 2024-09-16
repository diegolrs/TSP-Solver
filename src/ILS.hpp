#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include "Solution.hpp"
#include "Insertion.hpp"
#include "Data.h"
#include "SwapOperations.hpp"

//#define INFINITY ((float)(1e+300 * 1e+300))
#define RANDOM_SOLUTION_AMOUNT 3 

void LocalSearch(Solution *s, Data *data)
{
    return;
    std::vector<int> NL = {1, 2, 3, 4, 5};
    bool improved = false;

    while(NL.empty() == false)
    {
        int n = rand() % NL.size();
        switch (n)
        {
            case 0:
                improved = BestImprovementSwap(s, data);
                break;
            case 1:
                improved = BestImprovement2Opt(s, data);
                break;
            case 2:
                improved = BestImprovementOrOpt(s, 1, data); // Reinsertion
                break;
            case 3:
                improved = BestImprovementOrOpt2(s, 2, data); // Or-opt2
                break;
            case 4:
                improved = BestImprovementOrOpt(s, 3, data); // Or-opt2
                break;
        } ;

        if(improved)
            NL = {1, 2, 3, 4, 5};
        else
            NL.erase(NL.begin() + n);
    }
}

Solution Disturbance(Solution s)
{
    return s;
    int minAmount = 2;
    int maxAmount = s.sequence.size()/10.0f;
    int amountToApply = rand()%(maxAmount-minAmount+1) + minAmount;

    for(int i = 0; i < amountToApply; i++)
    {
        // two different numbers
        int a = rand()%(s.sequence.size());
        int b = a;
        while(b == a)
            b = rand()%(s.sequence.size());

        std::swap(s.sequence[a], s.sequence[b]);
    }

    return s;
}

Solution ConstructSolution(Data* data)
{
    Solution s;
    s.sequence = GenerateRandomNodes(RANDOM_SOLUTION_AMOUNT, 0, data->getDimension()-1);
    std::vector<int> CL = GetReamingNodes(s.sequence, data->getDimension());

    while(!CL.empty())
    {
        std::vector<InsertionInfo> insertionCost = CalculateInsertionCost(s, CL, data);
        std::sort(insertionCost.begin(), insertionCost.end(), CompareInsertionInfo);
        double alpha = (double) rand() / RAND_MAX;
        int selected = rand() % ((int) ceil(alpha * insertionCost.size()));
        s.sequence.push_back(insertionCost[selected].insertedNode);

        // remove from CL
        auto it = std::find(CL.begin(), CL.end(), insertionCost[selected].insertedNode);
        if(it != CL.end()) CL.erase(it);
    }

    return s;
}

// Note: ILS means Iterated Local Search
Solution ILS(int maxIter, int maxIterIls, Data* data)
{
    Solution bestOfAll;
    bestOfAll.cost = INFINITY;

    for(int i = 0; i < maxIter; i++)
    {
        Solution s = ConstructSolution(data);
        Solution bestLocalSolution = s;

        int iterIls = 0;
        while(iterIls <= maxIterIls)
        {
            LocalSearch(&s, data);

            if(s.cost < bestLocalSolution.cost)
            {
                bestLocalSolution = s;
                iterIls = 0;
            }

            s = Disturbance(bestLocalSolution);
            iterIls++;
        }

        if (bestLocalSolution.cost < bestOfAll.cost)
            bestOfAll = bestLocalSolution;
    }

    bestOfAll.sequence.push_back(INITIAL_NODE_ON_RANDOM);

    return bestOfAll;
}