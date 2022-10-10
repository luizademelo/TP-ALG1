
#ifndef CAMPANHA_HPP
#define CAMPANHA_HPP

#include <bits/stdc++.h>

using namespace std;

class Vertice{
    public: 
        int id;
        int t; // tempo de termino da dfs pra esse vertice
        Vertice(int id); 
}; 

class Grafo
{
public:
    vector<Vertice> adj[20001];
    vector<Vertice> adjInv[20001];
    bool visitado[20001];
    bool visitadoInv[20001];
}; 

void
test(int S, int P, vector<Vertice> a, vector<Vertice> b);
void leEntrada(int S, vector<Vertice> *a, vector<Vertice> *b);
void limpa(vector<Vertice> a, vector<Vertice> b);
void addEdges(int v1, int v2);
void dfsFirst(int u);
void dfsCFC(int u);
void escreveResultado(int P);
void dfsFullGraph(int P);
void calculaCFC();
void constroiGrafo(int S, int P, vector<Vertice> a, vector<Vertice> b);

#endif