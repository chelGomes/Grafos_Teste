#ifndef GRAPH_H
#define GRAPH_H
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <vector>
#include <unordered_map>
#include "No.h"
#include "Aresta.h"
#include <vector>
using namespace std;

class No;
class Aresta;

struct Aresta_aux
{
    int origem;
    int destino;
    int peso;
};

class Grafo
{
public:
    //--- Construtor e Destrutor ---
    Grafo(bool isDigrafo, bool weightArc, bool weightNo);
    virtual ~Grafo();

    //--- Seters ---
    void incOrdem();
    void decOrdem();

    //--- Funcoes do No ---
    bool procurarNoPeloId(int idFindNo);
    No *getNo(int idFindNo);
    No *insereNo(int idNo, int pesoNo);
    bool removeNo(int idNo, bool isDigrafo);

    //--- Funcoes de Aresta ---
    bool insertAresta(int idNoOrigem, int idNoDestino, int pesoAresta, bool weigthArc, bool isDirected);
    bool removeAresta(int idNoOrigem, int idNoDestino, bool isDirected);
    void incrementaNumAresta() { numAresta++; };
    void decrementaNumAresta() { numAresta--; };


    //--- Caracteristica do Grafo ---
    int getNumAresta();
    No *getNoRaiz();
    int getOrdem();
    int getGrauEntrada();
    int getGrauSaida();
    bool isDigraph();

    //--- Ordenacao ---
    void mergeSort(vector<Aresta_aux> &vet, int fIndex, int lIndex);
    void merge(vector<Aresta_aux> &vet, int fIndex, int mIndex, int lIndex);
    //--- Algoritmos ---
    void agmKruskal();
    void buscaProfundidade(int v); // busca em profundidade
    void buscaLargura(int v);   // busca em largura
    void ordenacaoTopologica();
    void imprimeComponentesConexas();
    void verticesArticulacao();
private:
    int ordem;
    int numAresta;
    bool digrafo;
    bool weigthNo;
    bool weightArc;
    string indexAresta(int v, int w); // Funcao auxiliar - cria index para mapear as arestas visitadas
    void bpDir(int v, unordered_map<int,bool> &visitado, unordered_map<string,bool> &arestas_exploradas);
    void bfs(int v, unordered_map<int,bool>&visitado);
    //Componentes conexas
    vector<vector<int>>componetesConexas();
    void buscaComponentes(int v, unordered_map<int,bool> &visitado, vector<int> &componente);
    //Vertices de articulacao
    void encontrarArticulacao(No *noAtual, int pai, unordered_map<int,int> &tempoDescoberta, unordered_map<int,int> &menorTempoDescoberta, unordered_map<int,bool> &visitado, int tempo);
    No *noRaiz;
};

#endif // GRAPH_H
