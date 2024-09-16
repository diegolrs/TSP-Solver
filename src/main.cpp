#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Data.h"
#include "Solution.hpp"
#include "ILS.hpp"

#define RANDOM_SEED 42 //time(NULL)

using namespace std;

void ShowSolution(Solution *s)
{
    std::cout << "Solution: ";
    for(int i = 0; i < s->sequence.size()-1; i++)
        std::cout << s->sequence[i] << " ";
    std::cout << s->sequence.back() << std::endl;
    std::cout << "Optmized cost: " << s->cost << std::endl;
}

void CalculateSolutionValue(Solution *s, Data *data)
{
    s->cost = 0;
    for(int i = 0; i < s->sequence.size(); i++)
        s->cost += data->getDistance(s->sequence[i], s->sequence[i+1]);
}

int main(int argc, char** argv) 
{
    srand((unsigned int)RANDOM_SEED);

    Data* data = new Data(argc, argv[1]);
    data->read();
    size_t n = data->getDimension();

    // Original Cost
    double cost = 0.0;
    for (size_t i = 0; i < n-1; i++) 
    {
        cost += data->getDistance(i, i+1);
    }
    cost += data->getDistance(n-1, 0);
    cout << "Original cost of " << argv[1] << ": " << cost << endl;

    int maxIter = 50;
    int maxIterILS = data->getDimension() >= 150 ? data->getDimension()/2 : data->getDimension();
    Solution tsp = ILS(maxIter, maxIterILS, data);
    CalculateSolutionValue(&tsp, data);
    ShowSolution(&tsp);

    return 0; 
}