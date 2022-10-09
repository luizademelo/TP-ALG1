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


int counter = 1;

void leEntrada(int S, vector<int> *a, vector<int> *b)
{
    for (int i = 0; i < S; i++)
        {
            int x1, x2, y1, y2;
            cin >> x1 >> x2 >> y1 >> y2;
            if (x1 != 0 && x2 != 0)
            {
                a->push_back(x1);
                b->push_back(x2);
            }
            else
            {
                if (x1 == 0)
                {
                    a->push_back(x2);
                    b->push_back(x2);
                }
                else
                {
                    a->push_back(x1);
                    b->push_back(x1);
                }
            }
            if (y1 != 0 && y2 != 0)
            {
                a->push_back(y1 * -1);
                b->push_back(y2 * -1);
            }
            else
            {
                if (y1 == 0)
                {
                    a->push_back(y2 * -1);
                    b->push_back(y2 * -1);
                }
                else
                {
                    a->push_back(y1 * -1);
                    b->push_back(y1 * -1);
                }
            }
        }
}


void limpa(vector<int> a, vector<int> b)
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
    counter = 1;
}

void addEdges(int v1, int v2)
{
    adj[v1].push_back(v2);
}

void addEdgesInverse(int v1, int v2)
{
    adjInv[v2].push_back(v1);
}

void dfsFirst(int u)
{
    if (visitado[u])
        return;

    visitado[u] = 1;

    for (int i = 0; i < adj[u].size(); i++)
        dfsFirst(adj[u][i]);

    s.push(u);
}

void dfsSecond(int u)
{
    if (visitadoInv[u])
        return;

    visitadoInv[u] = 1;

    for (int i = 0; i < adjInv[u].size(); i++)
        dfsSecond(adjInv[u][i]);

    cfc[u] = counter;
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
            dfsFirst(i);
}

void calculaCFC()
{
    while (!s.empty())
    {
        int S = s.top();
        s.pop();

        if (!visitadoInv[S])
        {
            dfsSecond(S);
            counter++;
        }
    }
}

void constroiGrafo(int S, int P, vector<int> a, vector<int> b)
{
    for (int i = 0; i < S * 2; i++)
    {
        if (a[i] > 0 && b[i] > 0)
        {
            addEdges(a[i] + P, b[i]);
            addEdgesInverse(a[i] + P, b[i]);
            addEdges(b[i] + P, a[i]);
            addEdgesInverse(b[i] + P, a[i]);
        }

        else if (a[i] > 0 && b[i] < 0)
        {
            addEdges(a[i] + P, P - b[i]);
            addEdgesInverse(a[i] + P, P - b[i]);
            addEdges(-b[i], a[i]);
            addEdgesInverse(-b[i], a[i]);
        }

        else if (a[i] < 0 && b[i] > 0)
        {
            addEdges(-a[i], b[i]);
            addEdgesInverse(-a[i], b[i]);
            addEdges(b[i] + P, P - a[i]);
            addEdgesInverse(b[i] + P, P - a[i]);
        }

        else
        {
            addEdges(-a[i], P - b[i]);
            addEdgesInverse(-a[i], P - b[i]);
            addEdges(-b[i], P - a[i]);
            addEdgesInverse(-b[i], P - a[i]);
        }
    }
}

void test(int S, int P, vector<int> a, vector<int> b)
{
    constroiGrafo(S, P, a, b); 

    dfsFullGraph(P);

    calculaCFC(); 

    escreveResultado(P);
}
