#pragma once
#include "Solution.hpp"
#include "Insertion.hpp"
#define INFINITY ((float)(1e+300 * 1e+300))

Solution ConstructSolution(Data* data)
{
    Solution s;
    s.sequence = ChooseRandomNodes(3);
    std::vector<int> CL = reaminingNodes();

    while(!CL.empty())
    {
        std::vector<InsertionInfo> insertionCost = CalculateInsertionCost(s, CL, data);
        OrderInsertionInfos();
        double alpha = (double) rand() / RAND_MAX;
        int selected = rand() % ((int) ceil(alpha * insertionCost.size()));
        insertOnSolution(s, insertionCost[selected].insertedNode); // WARN
    }

    return s;
}

void LocalSearch(Solution *s);
Solution Disturbance(Solution s);

// Note: ILS means Iterated Local Search
Solution ILS(int maxIter, int maxIterIls)
{
    Solution bestOfAll;
    bestOfAll.value = INFINITY;

    for(int i = 0; i < maxIter; i++)
    {
        Solution s = ConstructSolution();
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