#include "../include/campanha.hpp"

int main()
{
    while (true)
    {

        int S; // numero de seguidores
        int P; // numero de propostas
        cin >> S >> P;
        vector<Vertice> a;
        vector<Vertice> b;

        if (S == 0)
            break;

        leEntrada(S, &a, &b); 

        test(S, P, a, b);
        limpa(a,b);
    }
    return 0;
}