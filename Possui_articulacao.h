#ifndef POSSUI_ARTICULACAO_H
#define POSSUI_ARTICULACAO_H

class Grafo {
    int V; // Número de vértices
    int** adj; // Matriz de adjacência

    // Função auxiliar para encontrar vértices de articulação usando DFS
    bool possuiArticulacaoUtil(int v, bool visitado[], int visit[], int low[], int parent[]);

public:
    Grafo(int V); // Construtor
    ~Grafo(); // Destrutor
    void adicionarAresta(int v, int w); // Adiciona arestas
    bool possuiArticulacao(); // Verifica se há ao menos um vértice de articulação
};
