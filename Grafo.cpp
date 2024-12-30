#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>
#include "Grafo.h"
#include <vector>
#include "Conjunto.h"

using namespace std;
typedef vector<No *> NodeVector;


//------------------------ Construtors and Destrutors ------------------------

/**
 * Grafo Construtor.
 *
 * @param isDigrafo (new valor)
 */
Grafo::Grafo(bool isDigrafo, bool weightArc, bool weightNo)
{
    this->ordem = 0;
    this->noRaiz = NULL;
    this->digrafo = isDigrafo;
    this->weigthNo = weightNo;
    this->weightArc = weightArc;
}

/**
 * Destructor
 */
Grafo::~Grafo()
{
    No *noAux = this->getNoRaiz();
    No *noAuxAnterior;
    while (noAux != NULL)
    {
        noAuxAnterior = noAux->getProxNo();
        delete (noAux);
        noAux = noAuxAnterior;
    }
}

//----------------------------------- Seters -----------------------------------

/**
 * Funcao incrementa Ordem do grafo em um.
 */
void Grafo::incOrdem()
{
    this->ordem++;
}

/**
 * Funcao decrementa Ordem do grafo em um.
 */
void Grafo::decOrdem()
{
    this->ordem--;
}

//------------------------------ Funcoes do No ------------------------------

/**
 * EauxSSa funcao busca o No pelo nome.
 * Para achar o No, faça grafo->getNoAux()
 *
 * @param nome (no nome)
 * @return true - se achar no.
 *         false - se Nao achar.
 */
bool Grafo::procurarNoPeloId(int idFindNo)
{
    No *noAux = noRaiz;
    No *noAuxAnterior = NULL;

    while (noAux != NULL)
    {
        if (noAux->getIdNo() == idFindNo)
        {
            return true;
        }
        if (noAux->getProxNo() == NULL)
        {
            return false;
        }
        noAuxAnterior = noAux;
        noAux = noAux->getProxNo();
    }
    return false;
}

No *Grafo::getNo(int idFindNo)
{
    No *noAux = noRaiz;
    No *noAuxAnterior = NULL;

    while (noAux != NULL)
    {
        if (noAux->getIdNo() == idFindNo)
        {
            return noAux;
        }
        if (noAux->getProxNo() == NULL)
        {
            return NULL;
        }
        noAuxAnterior = noAux;
        noAux = noAux->getProxNo();
    }
    return NULL;
}

/**
 * A funcao insere o No caso ele nao existe ou atualiza seu peso.
 *
 * @param nome
 * @param peso (peso do No)
 */
No *Grafo::insereNo(int idNo, int peso)
{

    if (!procurarNoPeloId(idNo))
    {
        No *novoNo = new No(idNo, peso);

        if (noRaiz == NULL)
        {
            noRaiz = novoNo;
        }
        else
        {
            novoNo->setProxNo(noRaiz);
            noRaiz = novoNo;
        }
        incOrdem();
        return noRaiz;
    }
    return NULL;
}

/**
 * Remove No de um grafo
 *
 * @param nome (no nome)
 */
// TODO Corrigir grau de entrada em grafos direcionados
bool Grafo::removeNo(int idNo, bool isDigrafo)
{
    // Pesquisa o No a ser excluido
    // Remove todas as arestas/arcos onde este nó ocorre
    // Remove o no

    No *noExcluir = NULL;
    No *noAux = this->noRaiz;
    No *noAnt = NULL;
    Aresta *arestaAux = NULL;
    Aresta *proxAresta = NULL;

    while (noAux != NULL)
    {

        if (noAux->getIdNo() != idNo)
        {
            if (noAux->getProxNo() != NULL && noAux->getProxNo()->getIdNo() == idNo)
            {
                noExcluir = noAux->getProxNo();
                noAnt = noAux;
            }
            arestaAux = noAux->procurarAresta(idNo);
            if (arestaAux != NULL)
            {
                this->removeAresta(noAux->getIdNo(), idNo, isDigrafo);
            }
        }
        noAux = noAux->getProxNo();
    }

    if (this->noRaiz->getIdNo() == idNo)
    {
        noExcluir = noRaiz;

        if (isDigrafo)
        {
            arestaAux = noExcluir->getPrimeiraAresta();
            while (arestaAux != NULL)
            {
                proxAresta = arestaAux->getProxAresta();
                this->removeAresta(noExcluir->getIdNo(), arestaAux->getIdNoDestino(), isDigrafo);
                arestaAux = proxAresta;
            }
        }

        noRaiz = noRaiz->getProxNo();
        delete (noExcluir);
        this->decOrdem();
        return true;
    }
    else if (noExcluir == NULL)
    {
        return false;
    }
    else
    {
        if (isDigrafo)
        {
            arestaAux = noExcluir->getPrimeiraAresta();
            while (arestaAux != NULL)
            {
                proxAresta = arestaAux->getProxAresta();
                this->removeAresta(noExcluir->getIdNo(), arestaAux->getIdNoDestino(), isDigrafo);
                arestaAux = proxAresta;
            }
        }

        noAnt->setProxNo(noExcluir->getProxNo());
        delete (noExcluir);
        this->decOrdem();
        return true;
    }
}

/**
 * Insere a aresta de A para B se não adjacencia nao existir,
 * caso exista, a funcao atualiza o peso
 *
 * @param noFonteNome ()
 * @param noDestinoNome ()
 * @param pesoAresta ()
 */
bool Grafo::insertAresta(int idNoOrigem, int idNoDestino, int pesoAresta, bool weigthArc, bool isDirected)
{
    if(idNoOrigem == idNoDestino) {
        return false;
    }

    No *noOrigem = getNo(idNoOrigem);
    No *noDestino = getNo(idNoDestino);

    if (noOrigem != NULL && noDestino != NULL)
    {
        Aresta *arestaAux = noOrigem->procurarAresta(idNoDestino);
        if (isDirected)
        {

            if (arestaAux != NULL)
            {
                arestaAux->setPesoAresta(pesoAresta);
            }
            else
            {
                noOrigem->incluirAresta(idNoDestino, pesoAresta, 0);
                noOrigem->incrementaGrauSaida();
                noDestino->incrementaGrauEntrada();
            }
        }
        else
        {
            if (arestaAux != NULL)
            {
                arestaAux->setPesoAresta(pesoAresta);
                noDestino->procurarAresta(idNoOrigem)->setPesoAresta(pesoAresta);
            }
            else
            {
                noOrigem->incluirAresta(idNoDestino, pesoAresta, 0);
                noDestino->incluirAresta(idNoOrigem, pesoAresta, 1);
                noOrigem->incrementaGrauSaida();
                noDestino->incrementaGrauSaida();
            }
        }
        incrementaNumAresta();
        return true;
    }
    else
    {
        if (noOrigem == NULL)
        {
            noOrigem = this->insereNo(idNoOrigem, 1);
        }
        if (noDestino == NULL)
        {
            noDestino = this->insereNo(idNoDestino, 1);
        }
        if (isDirected)
        {
            noOrigem->incluirAresta(idNoDestino, pesoAresta, 0);
            noOrigem->incrementaGrauSaida();
            noDestino->incrementaGrauEntrada();
        }
        else
        {

            noOrigem->incluirAresta(idNoDestino, pesoAresta, 0);
            noDestino->incluirAresta(idNoOrigem, pesoAresta, 1);
            noOrigem->incrementaGrauSaida();
            noDestino->incrementaGrauSaida();
        }
        incrementaNumAresta();
        return true;
    }
    return false;
    // Verifica se já existem os dois nós com esses ids no grafo
    //  Se ja existem, eé so inserir a aresta em cada um se o grafo for nao direcionado ou apenas de
    //    origem pra destino, caso o grafo seja orientado.
    // Se para algum ou ambos os ids não existe o no no grafo, e preciso inserir nos com esses ids antes de incluir a aresta

    // if ( procurarNoPeloId(noFonteNome) ) {
}

/**
 * This function search in a no the edges that points to the same destiny no.\n
 * If 'removeAll' is TRUE, all of these edges will be removed, only 1 otherwise. (multigraph)\n
 * If 'considerarPeso' is TRUE, only the edge with peso equals to 'peso' will be removed.\n
 * If 'considerarPeso' is FALSE, don't matter the valor paauxSSed as parameter in 'peso'.
 *
 * @param *noDestino (the no that refers to the edges that will be removed)
 * @param *noOrigem (the no that refers to the edges that will be removed)
 * @param isDirected (flag to inform graph or digraph)
 * @param peso (peso)
 *
 * @return int (numero arestas excluidas)
 */
bool Grafo::removeAresta(int idNoOrigem, int idNoDestino, bool isDirected)
{
    // Procura o nó origem e busca na sua lista de arestas o idNoDestino
    // Se encontrar, remove. Se não, retorna zero

    No *noOrigem = getNo(idNoOrigem);
    No *noDestino = getNo(idNoDestino);

    if (noOrigem != NULL && noDestino != NULL)
    {
        if (isDirected)
        {
            if (noOrigem->excluirAresta(idNoDestino))
            {
                noOrigem->decrementaGrauSaida();
                noDestino->decrementaGrauEntrada();
                decrementaNumAresta();
                return true;
            }
        }
        else
        {
            if (noOrigem->excluirAresta(idNoDestino) && noDestino->excluirAresta(idNoOrigem))
            {
                noOrigem->decrementaGrauSaida();
                noDestino->decrementaGrauSaida();
                decrementaNumAresta();
                return true;
            }
        }
    }
    return false;
}

//--- Caracteristica do Grafo ---

/**
 * Retorna o numero de aresta do grafo.
 */
int Grafo::getNumAresta()
{
    No *noAux = noRaiz;
    int numAresta = 0;

    while (noAux != NULL)
    {
        numAresta += noAux->getGrau();
        noAux = noAux->getProxNo();
    }
    return numAresta / 2;
}

/**
 * Retorna 'rootNode'.
 */
No *Grafo::getNoRaiz()
{
    return this->noRaiz;
}

/**
 * Retorna ordem do grafo.
 */
int Grafo::getOrdem()
{
    return this->ordem;
}

/**
 * Retorna Aresta Aux.
 */

/*
Aresta* Grafo::getArestaAux() {
    return this->arestaAux;
}
*/

/**
 * Retorna grau de entrada.
 */
int Grafo::getGrauEntrada()
{
    int inputDegree = 0;

    No *noAux = noRaiz;
    while (noAux != NULL)
    {
        if (noAux->getGrauEntrada() > inputDegree)
        {
            inputDegree = noAux->getGrauEntrada();
        }
        noAux = noAux->getProxNo();
    }
    return inputDegree;
}

/**
 * Retorna grau de saida.
 */
int Grafo::getGrauSaida()
{
    int outputDegree = 0;

    No *noAux = noRaiz;
    while (noAux != NULL)
    {
        if (noAux->getGrauSaida() > outputDegree)
        {
            outputDegree = noAux->getGrauSaida();
        }
        noAux = noAux->getProxNo();
    }
    return outputDegree;
}

/**
 * @return true - se grafo e digrafo.
 *        false - se grafo NAO e digrafo.
 */
bool Grafo::isDigraph()
{
    return this->digrafo;
}
// Ordenacao de Vetores

void Grafo::merge(vector<Aresta_aux> &vet, int fIndex, int mIndex, int lIndex)
{
    vector<Aresta_aux> vetAux(lIndex - fIndex + 1);
    int i = fIndex;
    int j = mIndex + 1;
    int k = 0;

    while ((i <= mIndex) && (j <= lIndex))
    {
        if (vet[i].peso < vet[j].peso)
        {
            vetAux[k] = vet[i];
            i++;
        }
        else
        {
            vetAux[k] = vet[i];
            vetAux[k] = vet[j];
            j++;
        }

        k++;
    }
    while (i <= mIndex)
    {
        vetAux[k] = vet[i];
        i++;
        k++;
    }
    while (j <= lIndex)
    {
        vetAux[k] = vet[j];
        j++;
        k++;
    }
    for (i = fIndex; i <= lIndex; i++)
    {
        vet[i] = vetAux[i - fIndex];
    }
}
void Grafo::mergeSort(vector<Aresta_aux> &vet, int fIndex, int lIndex)
{
    if (fIndex < lIndex)
    {
        int mIndex = (fIndex + lIndex) / 2;
        mergeSort(vet, fIndex, mIndex);
        mergeSort(vet, mIndex + 1, lIndex);
        merge(vet, fIndex, mIndex, lIndex);
    }
}

//--------------------FUNCIONALIDADES-------------------------------- 

void Grafo::agmKruskal()
{
    // Passo 1: Criação e ordenação do vetor de Arestas com base nos pesos
    vector<Aresta_aux> arestasOrdenadas; // Vetor de Aresta_aux para armazenar as arestas ordenadas
    No *noAux = getNoRaiz();
    Aresta *arestaAux = NULL;
    Aresta_aux arestaVet;
    while (noAux != NULL)
    {
        arestaAux = noAux->getPrimeiraAresta();
        while (arestaAux != NULL)
        {
            arestaVet.destino = arestaAux->getIdNoDestino();
            arestaVet.origem = noAux->getIdNo();
            arestaVet.peso = arestaAux->getPesoAresta();
            bool arestaJaExiste = false;

            // Verificar se a aresta inversa já existe

            if(arestaAux->getArestaDuplicada() == 0){
                arestasOrdenadas.push_back(arestaVet);
            }

            arestaAux = arestaAux->getProxAresta();
        }
        noAux = noAux->getProxNo();
    }

    // Ordenar o vetor de arestas usando o algoritmo de merge sort
    mergeSort(arestasOrdenadas, 0, arestasOrdenadas.size() - 1);

    // Passo 2: Inicialização da estrutura Conjunto 
    int numNos = this->ordem; 
    Conjunto uf(numNos);

    // Passo 3: Construção da Árvore Geradora Mínima (AGM)
    vector<Aresta_aux> agm; // Vetor para armazenar as arestas da AGM

    for (Aresta_aux aresta : arestasOrdenadas)
    {
        uf.adicionarVertice(aresta.origem);
        uf.adicionarVertice(aresta.destino);

        // Verificar se os dois vertices estao no mesmo conjunto
        if (!uf.mesmoConjunto(aresta.origem, aresta.destino))
        {
            // Adicionar a aresta à AGM
            agm.push_back(aresta);

            // Unir os conjuntos dos vértices conectados pela aresta
            uf.unirConjuntos(aresta.origem, aresta.destino);
        }
    }

    
    for (int i = 0; i < agm.size(); i++)
    {
        cout << "(" << agm[i].origem << "," << agm[i].destino << ")" << endl;
    }
}

// FUNCAO AUXILIAR PARA VERIFICAR ARESTAS
string Grafo::indexAresta(int v, int w)
{
    return std::to_string(v) + "-" + std::to_string(w);
}

// BUSCA EM LARGURA
void Grafo::buscaLargura(int v)
{

    std::unordered_map<int, bool> visitado;

    bfs(v, visitado);
}

void Grafo::bfs(int v, unordered_map<int, bool> &visitado)
{

    vector<int> nosId;
    int idx = 0;

    visitado[v] = true;
    nosId.push_back(v);

    cout << "Busca em largura: ";

    while (idx < nosId.size())
    {
        int corrente = nosId[idx];
        idx++;

        No *noAtual = getNo(corrente);

        if (noAtual == NULL)
        {
            cout << "Este no nao esta contido neste grafo!" << endl;
            return;
        }

        Aresta *aresta = noAtual->getPrimeiraAresta();

        cout << corrente << " ";

        while (aresta != NULL)
        {
            int adj = aresta->getIdNoDestino();
            if (visitado.find(adj) == visitado.end() || !visitado[adj])
            {
                visitado[adj] = true;
                nosId.push_back(adj);
            }
            aresta = aresta->getProxAresta();
        }
    }
    cout << endl;
}

// BUSCA EM PROFUNDIDADE
void Grafo::bpDir(int v, unordered_map<int, bool> &visitado, unordered_map<string, bool> &arestas_exploradas)
{
    No *node = getNo(v);

    if (node == NULL)
    {
        cout << "Este no nao esta contido neste grafo!" << endl;
        return;
    }

    visitado[v] = true;
    cout<< v << " " << endl;
    for (Aresta *aresta = node->getPrimeiraAresta(); aresta != NULL; aresta = aresta->getProxAresta())
    {
        int w = aresta->getIdNoDestino();

        if (visitado.find(w) == visitado.end() || !visitado[w])
        {
            arestas_exploradas[indexAresta(v, w)] = true;
            bpDir(w, visitado, arestas_exploradas);
        }
        else
        {
            if (!arestas_exploradas[indexAresta(v, w)])
            {
                arestas_exploradas[indexAresta(v, w)] = true;
                cout << "Aresta de retorno: " << v << "->" << w << endl;
            }
        }
    }
}

void Grafo::buscaProfundidade(int v)
{

    unordered_map<int, bool> visitado;
    unordered_map<string, bool> arestas_exploradas;

    if (visitado.find(v) == visitado.end(v) || !visitado[v])
    {
        bpDir(v, visitado, arestas_exploradas);
    }
}

//----ORDENACAO TOPOLOGICA----
void Grafo::ordenacaoTopologica()
{
    if (!this->isDigraph())
    {
        cout << "A ordenacao topologica e valida somente para grafos direcionados." << endl;
        return;
    }
    std::unordered_map<int, int> grausEntrada; // armazenar graus de entrada

    No *no = this->getNoRaiz();
    while (no != NULL)
    {
        grausEntrada[no->getIdNo()] = no->getGrauEntrada();
        no = no->getProxNo();
    }

    vector<No *> ordenacao;
    vector<No *> s;

    No *noAtual = getNoRaiz();
    while (noAtual != NULL)
    {
        if (noAtual->getGrauEntrada() == 0)
        {
            s.push_back(noAtual);
        }

        noAtual = noAtual->getProxNo();
    }

    while (!s.empty())
    {
        No *v = s.back();
        s.pop_back();

        ordenacao.push_back(v);

        Aresta *aresta = v->getPrimeiraAresta();
        while (aresta != NULL)
        {
            No *w = getNo(aresta->getIdNoDestino());

            grausEntrada[w->getIdNo()]--; // decrementa grau
            if (grausEntrada[w->getIdNo()] == 0)
            {
                s.push_back(w);
            }
            aresta = aresta->getProxAresta();
        }
    }

    // Se o tamanho do vetor for menor que a ordem do grafo, o mesmo tem um ciclo
    if (ordenacao.size() != this->getOrdem())
    {
        cout << "O grafo nao e aciclico! A ordenacao topologica nao e possivel." << endl;
        return;
    }

    cout << "Ordenacao Topologica do grafo: \n<";
    for (No *no : ordenacao)
    {
        cout << no->getIdNo() << " ";
    }
    cout << ">";
    cout << endl;
}

//COMPONENTES CONEXAS
    // Função auxiliar para busca em profundidade, usada para encontrar componentes conexas
void Grafo::buscaComponentes(int v, unordered_map<int,bool> &visitado, vector<int> &componente) {
    visitado[v] = true;
    componente.push_back(v);

    // Obtém o nó atual
    No* noAtual = this->getNo(v);

    // Itera sobre as arestas do nó
    for(Aresta* aresta = noAtual->getPrimeiraAresta(); aresta != NULL; aresta = aresta->getProxAresta()) {
        int adj = aresta->getIdNoDestino();
        
        // Se o vértice adjacente não foi visitado, realiza busca em profundidade recursivamente
        if(visitado.find(adj) == visitado.end() || !visitado[adj]) {
            buscaComponentes(adj,visitado,componente);
        }
    }
}

// Função para encontrar componentes conexas no grafo
vector<vector<int>> Grafo::componetesConexas() {
    unordered_map<int,bool> visitado;
    vector<vector<int>> componentes;

    // Obtém o primeiro nó do grafo
    No* noAtual = this->getNoRaiz();

    // Itera sobre todos os nós do grafo
    while (noAtual != NULL) 
    {
        // Se o nó não foi visitado, inicia uma busca em profundidade para encontrar o componente conexo
        if(visitado.find(noAtual->getIdNo()) == visitado.end() || !visitado[noAtual->getIdNo()]) {
            vector<int> componente;
            buscaComponentes(noAtual->getIdNo(),visitado,componente);
            componentes.push_back(componente);
        }
        // Move para o próximo nó
        noAtual = noAtual->getProxNo();
    }

    return componentes;    
}

// Função para imprimir os componentes conexos encontrados
void Grafo::imprimeComponentesConexas() {

    // Verifica se o grafo é direcionado
    if(this->isDigraph()) {
        cout << "O algoritmo suporta somente grafos não orientados." << endl;
        return;
    }

    // Obtém os componentes conexos
    vector<vector<int>> componentes = componetesConexas();

    // Imprime o número de componentes conexos
    cout << "O numero de Componentes Conexas e: " << componentes.size() << endl;

    // Imprime cada componente conexo
    for(int i = 0; i < componentes.size(); i++) {
        cout << "Componente " << (i+1) << " : ";
        for(int v : componentes[i]) {
            cout << v << " ";
        }
        cout  << endl;
    }
}

  // Função para encontrar os vértices de articulação no grafo
void Grafo::verticesArticulacao()
{
    // Mapa para armazenar o tempo de descoberta de cada nó
    unordered_map<int, int> tempoDescoberta;

    // Mapa para armazenar o menor tempo de descoberta alcançável por cada nó
    unordered_map<int, int> menorTempoDescoberta;

    // Mapa para rastrear se um nó foi visitado durante a travessia
    unordered_map<int, bool> visitado;

    // Variável para rastrear o tempo atual durante a travessia
    int tempo = 0;

    // Imprime a mensagem inicial
    cout << "Conjunto de vertices de articulacao: \n{";

    // Percorre todos os nós do grafo
    for (No *noAtual = getNoRaiz(); noAtual != nullptr; noAtual = noAtual->getProxNo())
    {
        // Verifica se o nó foi visitado, se não, chama a função de busca em profundidade
        if (!visitado[noAtual->getIdNo()])
        {
            encontrarArticulacao(noAtual, -1, tempoDescoberta, menorTempoDescoberta, visitado, tempo);
        }
    }

    // Imprime o conjunto de vértices de articulação
    cout << "}" << endl;
}

// Função auxiliar para encontrar vértices de articulação usando busca em profundidade
void Grafo::encontrarArticulacao(No *noAtual, int pai, unordered_map<int, int> &tempoDescoberta, unordered_map<int, int> &menorTempoDescoberta, unordered_map<int, bool> &visitado, int tempo)
{
    // Marca o nó como visitado
    visitado[noAtual->getIdNo()] = true;

    // Atualiza os tempos de descoberta para o nó atual
    tempo++;
    tempoDescoberta[noAtual->getIdNo()] = tempo;
    menorTempoDescoberta[noAtual->getIdNo()] = tempo;

    // Contador de filhos na árvore de busca em profundidade
    int filhos = 0;

    // Itera sobre as arestas do nó
    for (Aresta *aresta = noAtual->getPrimeiraAresta(); aresta != nullptr; aresta = aresta->getProxAresta())
    {
        int filho = aresta->getIdNoDestino();

        // Se o filho não foi visitado, continua a busca em profundidade
        if (!visitado[filho])
        {
            filhos++;

            // Chama a função de busca em profundidade recursivamente
            encontrarArticulacao(getNo(filho), noAtual->getIdNo(), tempoDescoberta, menorTempoDescoberta, visitado, tempo);

            // Atualiza o menor tempo de descoberta alcançável pelo nó atual
            menorTempoDescoberta[noAtual->getIdNo()] = std::min(menorTempoDescoberta[noAtual->getIdNo()], menorTempoDescoberta[filho]);

            // Verifica a condição para ser um vértice de articulação
            if (menorTempoDescoberta[filho] >= tempoDescoberta[noAtual->getIdNo()] && pai != -1)
            {
                cout << noAtual->getIdNo() << ",";
            }

            // Verifica a condição especial para a raiz da árvore de busca em profundidade
            if (pai == -1 && filhos > 1)
            {
                cout << noAtual->getIdNo() << ",";
            }
        }
        // Se o filho já foi visitado e não é o pai, atualiza o menor tempo de descoberta
        else if (filho != pai)
        {
            menorTempoDescoberta[noAtual->getIdNo()] = std::min(menorTempoDescoberta[noAtual->getIdNo()], tempoDescoberta[filho]);
        }
    }
}
