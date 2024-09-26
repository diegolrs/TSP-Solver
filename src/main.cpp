#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include "ILS.hpp"

#define RANDOM_SEED time(NULL) // 42

using namespace std;

void ShowSolution(Solution *s)
{
    std::cout << "Solution: ";
    for(int i = 0; i < s->sequence.size()-1; i++)
        std::cout << s->sequence[i] << " ";
    std::cout << s->sequence.back() << std::endl;
    std::cout << "Optmized cost: " << s->cost << std::endl;
}

int main(int argc, char** argv) 
{
    auto start = std::chrono::high_resolution_clock::now();
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
    tsp.cost = CalculateSolutionValue(&tsp, data);
    ShowSolution(&tsp);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> float_ms = end - start;
    std::cout << "Execution Time: " << float_ms.count() / 1000.0000000000000 << " seconds." << std::endl;

    return 0; 
}