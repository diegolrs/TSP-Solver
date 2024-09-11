#include <iostream>
#include "Data.h"
#include "Solution.hpp"
#include "ILS.hpp"

using namespace std;

void exibirSolucao(Solution *s)
{
    for(int i = 0; i < s->sequence.size() -1; i++)
        std::cout << s->sequence[i] << " -> ";
    std::cout << s->sequence.back() << std::endl;
    std::cout << "Valor: " << s->value << std::endl;
}

void calcularValorObj(Solution *s, Data *data)
{
    s->value = 0;
    for(int i = 0; i < s->sequence.size() - 1; i++)
        s->value += data->getDistance(s->sequence[i], s->sequence[i+1]);
}

int main(int argc, char** argv) 
{
    Data* data = new Data(argc, argv[1]);
    data->read();
    size_t n = data->getDimension();

    // cout << "Dimension: " << n << endl;
    // cout << "DistanceMatrix: " << endl;
    // data.printMatrixDist();

    // cout << "Exemplo de Solucao s = ";
    double cost = 0.0;
    for (size_t i = 1; i < n; i++) 
    {
        //cout << i << " -> ";
        cost += data->getDistance(i, i+1);
    }
    cost += data->getDistance(n, 1);
    // cout << n << " -> " << 1 << endl;

    cout << "Custo de " << argv[1] << ": " << cost << endl;

    return 0;
}