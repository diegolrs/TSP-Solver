#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include "Solution.hpp"
#include "Insertion.hpp"
#include "Data.h"

bool BestImprovementSwap(Solution *s, Data *data)
{
    double bestDelta = 0;
    int best_i, best_j;

    for(int i = 0; i < s->sequence.size() -1; i++)
    {
        int vi = s->sequence[i];
        int vi_next = s->sequence[i+1];
        int vi_prev = s->sequence[i-1];

        for(int j = i+1; j < s->sequence.size() -1; j++)
        {
            int vj = s->sequence[j];
            int vj_next = s->sequence[j+1];
            int vj_prev = s->sequence[j-1];

            // simulate trading nodes i and j positions
            double delta = -data->getDistance(vi_prev, vi) -data->getDistance(vi, vi_next)
                           +data->getDistance(vi_prev, vj) +data->getDistance(vj, vi_next)
                           -data->getDistance(vj_prev, vj) -data->getDistance(vj, vj_next)
                           +data->getDistance(vj_prev, vi) +data->getDistance(vi, vj_next);

            if(delta < bestDelta)
            {
                bestDelta = delta;
                best_i = i;
                best_j = j;
            }
        }
    }

    if(bestDelta < 0)
    {
        std::swap(s->sequence[best_i], s->sequence[best_j]);
        s->cost = s->cost + bestDelta;
        return true;
    }
    return false;
}

bool BestImprovement2Opt(Solution *s, Data *data) { return false; }
bool BestImprovementOrOpt(Solution *s, int n, Data *data) { return false; }
bool BestImprovementOrOpt2(Solution *s, int n, Data *data) { return false; }