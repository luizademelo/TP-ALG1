#include <stdio.h>
#include <stdlib.h>
#include "../include/campanha.hpp"

const int MAX = 20001;

vector<int> adj[MAX];
vector<int> adjInv[MAX];
bool visitado[MAX];
bool visitadoInv[MAX];
stack<int> s;

int cfc[MAX];

int numComponente = 1;

Vertice::Vertice(int id)
{
    this->id = id;
}

void leEntrada(int S, vector<Vertice> *a, vector<Vertice> *b)
{
    for (int i = 0; i < S; i++)
    {
        int x1, x2, y1, y2;
        cin >> x1 >> x2 >> y1 >> y2;
        Vertice v1(x1);
        Vertice v2(x2);
        if (x1 != 0 && x2 != 0)
        {
            a->push_back(v1);
            b->push_back(v2);
        }
        else
        {
            if (x1 == 0)
            {
                a->push_back(v2);
                b->push_back(v2);
            }
            else
            {
                a->push_back(v1);
                b->push_back(v1);
            }
        }
        if (y1 != 0 && y2 != 0)
        {
            v1.id = -y1;
            v2.id = -y2;
            a->push_back(v1);
            b->push_back(v2);
        }
        else
        {
            if (y1 == 0)
            {
                v2.id = -y2;
                a->push_back(v2);
                b->push_back(v2);
            }
            else
            {
                v1.id = -y1;
                a->push_back(v1);
                b->push_back(v1);
            }
        }
    }
}

void limpa(vector<Vertice> a, vector<Vertice> b)
{
    for (int i = 0; i < MAX; i++)
    {
        adj[i].clear();
        adjInv[i].clear();
        visitado[i] = false;
        visitadoInv[i] = false;
        cfc[i] = 1;
    }
    s = stack<int>();
    a.clear();
    b.clear();
    numComponente = 1;
}

void criaAresta(int v1, int v2)
{
    adj[v1].push_back(v2);
    adjInv[v2].push_back(v1);
}

void dfs(int u)
{
    if (visitado[u])
        return;

    visitado[u] = 1;

    for (long unsigned int i = 0; i < adj[u].size(); i++)
        dfs(adj[u][i]);

    s.push(u);
}

void dfsCFC(int u)
{
    if (visitadoInv[u])
        return;

    visitadoInv[u] = 1;

    for (long unsigned int i = 0; i < adjInv[u].size(); i++)
        dfsCFC(adjInv[u][i]);

    cfc[u] = numComponente;
}

void escreveResultado(int P)
{
    for (int i = 1; i <= P; i++)
    {
        if (cfc[i] == cfc[i + P])
        {
            cout << "nao\n";
            return;
        }
    }

    cout << "sim\n";
    return;
}

void dfsFullGraph(int P)
{
    for (int i = 1; i <= 2 * P; i++)
        if (!visitado[i])
            dfs(i);
}

void calculaCFC()
{
    while (!s.empty())
    {
        int S = s.top();
        s.pop();

        if (!visitadoInv[S])
        {
            dfsCFC(S);
            numComponente++;
        }
    }
}

void constroiGrafo(int S, int P, vector<Vertice> a, vector<Vertice> b)
{
    for (int i = 0; i < S * 2; i++)
    {
        if (a[i].id > 0 && b[i].id > 0)
        {
            criaAresta(a[i].id + P, b[i].id);
            criaAresta(b[i].id + P, a[i].id);
        }

        else if (a[i].id > 0 && b[i].id < 0)
        {
            criaAresta(a[i].id + P, P - b[i].id);
            criaAresta(-b[i].id, a[i].id);
        }

        else if (a[i].id < 0 && b[i].id > 0)
        {
            criaAresta(-a[i].id, b[i].id);
            criaAresta(b[i].id + P, P - a[i].id);
        }

        else
        {
            criaAresta(-a[i].id, P - b[i].id);
            criaAresta(-b[i].id, P - a[i].id);
        }
    }
}

void test(int S, int P, vector<Vertice> a, vector<Vertice> b)
{
    constroiGrafo(S, P, a, b);

    dfsFullGraph(P);

    calculaCFC();

    escreveResultado(P);
}