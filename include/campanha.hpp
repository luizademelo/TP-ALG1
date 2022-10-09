
#ifndef CAMPANHA_HPP
#define CAMPANHA_HPP

#include <bits/stdc++.h>

using namespace std;


void test(int S, int P, vector<int> a, vector<int> b); 
void leEntrada(int S, vector<int> *a, vector<int> *b); 
void limpa(vector<int> a, vector<int> b); 
void addEdges(int v1, int v2); 
void dfsFirst(int u); 
void dfsSecond(int u); 
void escreveResultado(int P);
void dfsFullGraph(int P);
void calculaCFC();
void constroiGrafo(int S, int P, vector<int> a, vector<int> b); 


#endif