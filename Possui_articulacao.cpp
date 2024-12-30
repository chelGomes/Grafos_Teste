#include "Possui_articulacao.h"
#include <iostream>
#include <algorithm> // Para std::min

using namespace std;

// Construtor do grafo
Grafo::Grafo(int V) : V(V) {
    adj = new int*[V];
    for (int i = 0; i < V; ++i) {
        adj[i] = new int[V](); // Inicializa a matriz com zeros
    }
}

// Destrutor do grafo
Grafo::~Grafo() {
    for (int i = 0; i < V; ++i) {
        delete[] adj[i];
    }
    delete[] adj;
}

// Função para adicionar uma aresta ao grafo
void Grafo::adicionarAresta(int v, int w) {
    adj[v][w] = 1; // Marca a aresta (v, w)
    adj[w][v] = 1; // Marca a aresta (w, v) para grafo não direcionado
}

// Função utilitária que verifica se há vértices de articulação usando DFS
bool Grafo::possuiArticulacaoUtil(int v, bool visitado[], int visit[], int low[], int parent[]) {
    static int tempo = 0; // Variável estática para rastrear o tempo de descoberta
    visitado[v] = true;   // Marca o vértice como visitado

    // Define o tempo de descoberta e o valor inicial de "low" para o vértice atual
    visit[v] = low[v] = ++tempo;
    int filhos = 0; // Contador para o número de filhos do vértice na DFS

    // Percorre todos os vértices adjacentes ao vértice atual
    for (int u = 0; u < V; ++u) {
        if (adj[v][u]) { // Se existe aresta (v, u)
            if (!visitado[u]) {
                // Caso o vértice adjacente não tenha sido visitado
                filhos++;
                parent[u] = v; // Define o pai do vértice adjacente como o vértice atual

                // Recursivamente chama a função para o vértice adjacente
                if (possuiArticulacaoUtil(u, visitado, visit, low, parent)) {
                    return true;
                }

                // Atualiza o valor de "low" do vértice atual com base no vértice adjacente
                low[v] = min(low[v], low[u]);

                // Verifica as condições para o vértice de articulação
                if (parent[v] == -1 && filhos > 1) return true; // Raiz com mais de um filho
                if (parent[v] != -1 && low[u] >= visit[v]) return true; // Caso geral
            } else if (u != parent[v]) {
                // Atualiza "low" para vértices já visitados que não são o pai
                low[v] = min(low[v], visit[u]);
            }
        }
    }

    return false; // Nenhum vértice de articulação encontrado
}

// Função principal para verificar se há pelo menos um vértice de articulação
bool Grafo::possuiArticulacao() {
    bool* visitado = new bool[V](); // Marca os vértices visitados
    int* visit = new int[V];        // Armazena o tempo de descoberta de cada vértice
    int* low = new int[V];          // Armazena o menor tempo acessível para cada vértice
    int* parent = new int[V];       // Armazena o pai de cada vértice na DFS

    fill_n(visit, V, -1);
    fill_n(low, V, -1);
    fill_n(parent, V, -1);

    // Itera por todos os vértices para cobrir grafos desconexos
    for (int i = 0; i < V; i++) {
        if (!visitado[i]) {
            if (possuiArticulacaoUtil(i, visitado, visit, low, parent)) {
                delete[] visitado;
                delete[] visit;
                delete[] low;
                delete[] parent;
                return true; // Retorna verdadeiro se encontrar algum vértice de articulação
            }
        }
    }

    delete[] visitado;
    delete[] visit;
    delete[] low;
    delete[] parent;
    return false; // Não encontrou vértices de articulação
}
