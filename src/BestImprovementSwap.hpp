#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include "Solution.hpp"
#include "Data.h"

namespace BestImprovementSwap
{
    void Swap(Solution *s, int i, int j, double costDelta)
    {
        std::swap(s->sequence[i], s->sequence[j]);
        s->cost = s->cost + costDelta;
    }

    double CalculateDelta(int i, int j, Solution *s, Data *data)
    {
        int vi = s->sequence[i];
        int vi_next = s->sequence[i + 1];
        int vi_prev = s->sequence[i - 1];

        int vj = s->sequence[j];
        int vj_next = s->sequence[j + 1];
        int vj_prev = s->sequence[j - 1];

        double to_subtract = data->getDistance(vi_prev, vi) + data->getDistance(vj, vj_next);
        double to_add = data->getDistance(vi_prev, vj) + data->getDistance(vi, vj_next);

        if(j != i+1)
        {
            to_subtract += data->getDistance(vi, vi_next)  + data->getDistance(vj_prev, vj);
            to_add += data->getDistance(vj, vi_next) + data->getDistance(vj_prev, vi);
        }

        return to_add - to_subtract;
    }   

    bool WasImproved(Solution *s, Data *data)
    {
        double bestDelta = 0;
        int best_i, best_j;

        for(int i = 1; i < s->sequence.size() - 1; i++)
        {
            int vi = s->sequence[i];
            int vi_next = s->sequence[i + 1];
            int vi_prev = s->sequence[i - 1];

            for(int j = i + 1; j < s->sequence.size() - 1; j++)
            {
                int vj = s->sequence[j];
                int vj_next = s->sequence[j + 1];
                int vj_prev = s->sequence[j - 1];

                double delta = CalculateDelta(i, j, s, data);
            
                if (delta < bestDelta)
                {
                    bestDelta = delta;
                    best_i = i;
                    best_j = j;
                }
            }
        }
        
        if(bestDelta < 0)
        {
            Swap(s, best_i, best_j, bestDelta);
            return true;
        }
        return false;
    }
}