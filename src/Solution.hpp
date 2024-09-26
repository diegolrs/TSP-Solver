#pragma once
#include <vector>
#include <algorithm>
#include "Data.h"

#define INITIAL_NODE_ON_RANDOM 0

typedef struct Solution
{
    Solution()
    {
        sequence = std::vector<int>();
    }

    std::vector<int> sequence;
    double cost;
} Solution;

double CalculateSolutionValue(Solution *s, Data *data)
{
    double cost = 0;
    for(int i = 0; i < s->sequence.size() -1; i++)
        cost += data->getDistance(s->sequence[i], s->sequence[i+1]);
    return cost;
}

bool ContainsNode(std::vector<int> vec, int node)
{
    return std::find(vec.begin(), vec.end(), node) != vec.end();
}

std::vector<int> GenerateRandomNodes(int quantityToGenerate, int minNumber, int maxNumber)
{
    std::vector<int> randomNumbers = std::vector<int>();
    randomNumbers.push_back(INITIAL_NODE_ON_RANDOM);

    for(int i = 0; i < quantityToGenerate; i++)
    {
        int random = rand()%(maxNumber-minNumber +1) + minNumber;

        if(!ContainsNode(randomNumbers, random))
            randomNumbers.push_back(random);
        else
            i--;
    }
    
    //randomNumbers.push_back(INITIAL_NODE_ON_RANDOM); // make solution be a cycle
    return randomNumbers;
}

// Returns all nodes that is not in vector n
std::vector<int> GetReamingNodes(std::vector<int> currentNodes, int quantityOfAllNodes)
{
    std::vector<int> remainingNodes = std::vector<int>();
    for(int i = 0; i < quantityOfAllNodes; i++)
    {
        if(!ContainsNode(currentNodes, i))
            remainingNodes.push_back(i);
    }
    return remainingNodes;
}