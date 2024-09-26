#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include "Solution.hpp"
#include "Data.h"

namespace BestImprovement2Opt
{
    // Note: segment between them is inserted inverted
    void Swap(Solution *s, int i, int j, double costDelta)
    {
        std::reverse(s->sequence.begin() + i + 1, s->sequence.begin() + j + 1);
        s->cost += costDelta;
    }

    double CalculateDelta(int i, int j, Solution *s, Data *data)
    {
        int vi = s->sequence[i];
        int vi_next = s->sequence[i + 1];
        
        int vj = s->sequence[j];
        int vj_next = s->sequence[j + 1];

        double to_subtract = data->getDistance(vi, vi_next) + data->getDistance(vj, vj_next);
        double to_add = data->getDistance(vi_next, vj_next) + data->getDistance(vi, vj);

        return to_add - to_subtract;
    }

    bool WasImproved(Solution *s, Data *data)
    {
        double bestDelta = 0;
        int best_i = -1, best_j = -1;

        int n = s->sequence.size();

        // Loop through all pairs of nodes (i, j) where j > i + 1 (because should to be adjacent)
        for(int i = 0; i < n - 2; i++)
        {
            for(int j = i + 2; j < n - 1; j++)
            {
                // Calculate the delta for the 2-Opt swap
                double delta = CalculateDelta(i, j, s, data);
                
                // If this swap improves the solution, record it
                if (delta < bestDelta)
                {
                    bestDelta = delta;
                    best_i = i;
                    best_j = j;
                }
            }
        }

        // If an improving swap is found, apply the 2-Opt swap by reversing the segment
        if (bestDelta < 0)
        {
            Swap(s, best_i, best_j, bestDelta);
            return true;
        }

        // No improvement found
        return false;
    }
}