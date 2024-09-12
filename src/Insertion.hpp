#pragma once
#include <vector>
#include <algorithm>
#include "Solution.hpp"
#include "Data.h"

typedef struct InsertionInfo
{
    int insertedNode;
    int removedEdge;
    double cost;
} InsertionInfo;

bool CompareInsertionInfo(InsertionInfo a, InsertionInfo b)
{
    return a.cost < b.cost;
}

std::vector<InsertionInfo> CalculateInsertionCost(Solution& s, std::vector<int>& CL, Data *data)
{
    std::vector<InsertionInfo> insertionCost = std::vector<InsertionInfo>((s.sequence.size()-1)*CL.size());
    int l = 0;

    for(int a = 0; a < s.sequence.size() -1; a++)
    {
        int i = s.sequence[a];
        int j = s.sequence[a+1];

        for(auto k : CL) 
        {
            insertionCost[l].cost = data->getDistance(i, k) + data->getDistance(j, k) - data->getDistance(i, j);
            insertionCost[l].insertedNode = k;
            insertionCost[l].removedEdge = a;
            l++;
        }
    }
    return insertionCost;
}