#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include "Solution.hpp"
#include "Data.h"

namespace BestImprovementOrOpt
{
    void Swap(Solution *s, int i, int j, double costDelta, int size)
    {
        std::vector<int> aux(s->sequence.begin()+i, s->sequence.begin()+i+size);
        s->sequence.erase(s->sequence.begin()+i, s->sequence.begin()+i+size);
        s->sequence.insert(s->sequence.begin()+j, aux.begin(), aux.end());
        s->cost += costDelta;
    }

    double CalculateDelta(int i, int j, Solution *s, Data *data, int size)
    {
        if(std::abs(i - j) <= size)
            return INFINITY;

        if(i > j)
            std::swap(i, j);

        int vi = s->sequence[i];
        int vi_next = s->sequence[i + 1];
        int vj = s->sequence[j];
        int vj_prev = s->sequence[j - 1];
        int vj_plus_size = s->sequence[j+size];
        int vj_plus_size_prev = s->sequence[j+size-1];

        double to_subtract = data->getDistance(vi, vi_next) + data->getDistance(vj_prev, vj) + data->getDistance(vj_plus_size_prev, vj_plus_size);
        double to_add = data->getDistance(vj_prev, vj_plus_size) + data->getDistance(vi, vj_plus_size_prev) + data->getDistance(vi_next, vj);

        return to_add - to_subtract;
    }   

    bool WasImproved(Solution *s, Data *data, int size)
    {
        double bestDelta = 0;
        int best_i = -1, best_j = -1;

        for (int i = 1; i < s->sequence.size() - size; i++)
        {
            for (int j = 1; j < s->sequence.size() - size; j++)
            {
                if(i == j)
                    continue;

                double delta = CalculateDelta(i, j, s, data, size);

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
            Swap(s, best_i, best_j, bestDelta, size);
            return true;
        }

        // No improvement found
        return false;
    }
}