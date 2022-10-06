#include <bits/stdc++.h>
using namespace std;

const int MAX = 10001;

// data structures used to implement Kosaraju's
// Algorithm. Please refer
// https://www.geeksforgeeks.org/strongly-connected-components/
vector<int> adj[MAX];
vector<int> adjInv[MAX];
bool visited[MAX];
bool visitedInv[MAX];
stack<int> s;

// this array will store the SCC that the
// particular node belongs to
int scc[MAX];

// counter maintains the number of the SCC
int counter = 1;

void limpa()
{
    for(int i = 0; i < MAX; i++)
    {
        adj[i].clear(); 
        adjInv[i].clear(); 
        visited[i] = false; 
        visitedInv[i] = false; 
    }
    s = stack<int>(); 
}


// adds edges to form the original graph
void addEdges(int a, int b)
{
    adj[a].push_back(b);
}

// add edges to form the inverse graph
void addEdgesInverse(int a, int b)
{
    adjInv[b].push_back(a);
}

// for STEP 1 of Kosaraju's Algorithm
void dfsFirst(int u)
{
    if (visited[u])
        return;

    visited[u] = 1;

    for (int i = 0; i < adj[u].size(); i++)
        dfsFirst(adj[u][i]);

    s.push(u);
}

// for STEP 2 of Kosaraju's Algorithm
void dfsSecond(int u)
{
    if (visitedInv[u])
        return;

    visitedInv[u] = 1;

    for (int i = 0; i < adjInv[u].size(); i++)
        dfsSecond(adjInv[u][i]);

    scc[u] = counter;
}

// function to check 2-Satisfiability
void is2Satisfiable(int n, int m, vector<int> a, vector<int> b)
{
    // adding edges to the graph
    for (int i = 0; i < m; i++)
    {
        // variable x is mapped to x
        // variable -x is mapped to n+x = n-(-x)

        // for a[i] or b[i], addEdges -a[i] -> b[i]
        // AND -b[i] -> a[i]
        if (a[i] > 0 && b[i] > 0)
        {
            addEdges(a[i] + n, b[i]);
            addEdgesInverse(a[i] + n, b[i]);
            addEdges(b[i] + n, a[i]);
            addEdgesInverse(b[i] + n, a[i]);
        }

        else if (a[i] > 0 && b[i] < 0)
        {
            addEdges(a[i] + n, n - b[i]);
            addEdgesInverse(a[i] + n, n - b[i]);
            addEdges(-b[i], a[i]);
            addEdgesInverse(-b[i], a[i]);
        }

        else if (a[i] < 0 && b[i] > 0)
        {
            addEdges(-a[i], b[i]);
            addEdgesInverse(-a[i], b[i]);
            addEdges(b[i] + n, n - a[i]);
            addEdgesInverse(b[i] + n, n - a[i]);
        }

        else
        {
            addEdges(-a[i], n - b[i]);
            addEdgesInverse(-a[i], n - b[i]);
            addEdges(-b[i], n - a[i]);
            addEdgesInverse(-b[i], n - a[i]);
        }
    }

    // STEP 1 of Kosaraju's Algorithm which
    // traverses the original graph
    for (int i = 1; i <= 2 * n; i++)
        if (!visited[i])
            dfsFirst(i);

    // STEP 2 of Kosaraju's Algorithm which
    // traverses the inverse graph. After this,
    // array scc[] stores the corresponding value
    while (!s.empty())
    {
        int n = s.top();
        s.pop();

        if (!visitedInv[n])
        {
            dfsSecond(n);
            counter++;
        }
    }

    for (int i = 1; i <= n; i++)
    {
        // for any 2 variable x and -x lie in
        // same SCC
        if (scc[i] == scc[i + n])
        {
            cout << "The given expression "
                    "is unsatisfiable."
                 << endl;
            return;
        }
    }

    // no such variables x and -x exist which lie
    // in same SCC
    cout << "The given expression is satisfiable."
         << endl;
    return;
}



int main()
{
    // n is the number of variables
    // 2n is the total number of nodes
    // m is the number of clauses
    int s, p;

    while (true)
    {
        cin >> s >> p;

        if(s == 0) break; 

        vector<int> a;
        vector<int> b;

        for (int i = 0; i < s; i++)
        {
            int x1, x2, y1, y2;
            cin >> x1 >> x2 >> y1 >> y2;
            if (x1 != 0 && x2 != 0)
            {
                a.push_back(x1);
                b.push_back(x2);
            }
            else
            {
                if (x1 == 0)
                {
                    a.push_back(x2);
                    b.push_back(x2);
                }
                else
                {
                    a.push_back(x1);
                    b.push_back(x1);
                }
            }
            if (y1 != 0 && y2 != 0)
            {
                a.push_back(y1 * -1);
                b.push_back(y2 * -1);
            }
            else
            {
                if (y1 == 0)
                {
                    a.push_back(y2 * -1);
                    b.push_back(y2 * -1);
                }
                else
                {
                    a.push_back(y1 * -1);
                    b.push_back(y1 * -1);
                }
            }
        }

        is2Satisfiable(s, p * 2, a, b);
        limpa(); 
    }
    return 0;
}