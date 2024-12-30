#include <iostream>
#include <fstream>
#include "Grafo.h"

using namespace std;

const string OUTPUT_DIRECTORY = "output_file/";
const string INPUT_DIRECTORY_1 = "input_file/ponderadosAresta/"; //grafos ponderados
const string INPUT_DIRECTORY_2 = "input_file/naoPonderadosAresta/"; //grafos nao ponderados

string nome_arquivo_saida;
string nome_arquivo_entrada;

Grafo *leitura(ifstream &arquivoDeLeitura, bool digrafo, bool pesoAresta, bool pesoNo)
{
    Grafo *newGrafo = new Grafo(digrafo, pesoAresta, pesoNo);

    int ordem = 0;
    int idNoOrigem = 0, idNoDestino = 0, peso = 1;

    arquivoDeLeitura >> ordem;
    cout << "\nORDEM LIDA DO ARQUIVO - " << ordem << endl << endl;
    
    if (pesoAresta)
    {
        while (arquivoDeLeitura >> idNoOrigem >> idNoDestino >> peso)
        {
            newGrafo->insertAresta(idNoOrigem, idNoDestino, peso, pesoAresta, digrafo);
        }
    }
    else {
        while (arquivoDeLeitura >> idNoOrigem >> idNoDestino)
        {
            newGrafo->insertAresta(idNoOrigem, idNoDestino, peso, pesoAresta, digrafo);
        }
    }
    return newGrafo;
}

void armazenarGrafo(ofstream &arquivoDeEscrita, Grafo *newGraph, bool digrafo, bool pesoAresta, bool pesoNo)
{

    if (digrafo)
    {
        arquivoDeEscrita << "DIGRAFO ORDEM - " << newGraph->getOrdem() << endl;
    }
    else
    {
        arquivoDeEscrita << "GRAFO ORDEM - " << newGraph->getOrdem() << endl;
    }

    arquivoDeEscrita << "LISTA DE ADJACENCIAS" << endl;

    No *noAux = newGraph->getNoRaiz();

    while (noAux != nullptr)
    {
        Aresta *auxAresta = noAux->getPrimeiraAresta();

        arquivoDeEscrita << "|" << noAux->getIdNo() << "|-> ";
        while (auxAresta != nullptr)
        {
            arquivoDeEscrita << "|" << auxAresta->getIdNoDestino() << "|-";
            auxAresta = auxAresta->getProxAresta();
        }
        arquivoDeEscrita << "¬" << endl;

        noAux = noAux->getProxNo();
    }
    arquivoDeEscrita.close();
}

int menu()
{

    int selecao;

    cout << "MENU" << endl;
    cout << "----" << endl;
    cout << "[1]  Algoritmo de Kruskal" << endl;
    cout << "[2]  Caminhamento em Profundidade" << endl;
    cout << "[3]  Ordenacao Topologica" << endl;
    cout << "[4] Busca em Largura" << endl;
    cout << "[5] Vertices de Articulacao" << endl;
    cout << "[6] Componentes Conexas" << endl;
    cout << "[7] Ordem do Grafo" << endl;
    cout << "[8] Adicionar No" << endl;
    cout << "[9] Remover No" << endl;
    cout << "[10] Adicionar Aresta" << endl;
    cout << "[11] Remover Aresta" << endl; 
    cout << "[12] Graus do No" << endl;
    cout << "[0]  Sair" << endl;

    cin >> selecao;

    return selecao;
}

//------------------inicio menu-----------------------------------------------
void selecionar(int selecao, Grafo *graph, ofstream &arquivoDeEscrita, bool pesoAresta, bool pesoNo)
{

    switch (selecao)
    {
    // Algoritimo de Kruskal
    case 1:
    {
        graph->agmKruskal();
        break;
    }

    // Caminhamento em profundidade
    case 2:
    {
        int verticeID;
        cout << "Digite o ID do vertice para iniciar o caminhamento em profundidade: ";
        cin >> verticeID;

        cout << "CAMINHAMENTO EM PROFUNDIDADE" << endl;
        graph->buscaProfundidade(verticeID);
        cout << endl;
        break;
    }

    // Ordenacao Topologica
    case 3:
    {
        graph->ordenacaoTopologica();
        break;
    }

    // Busca em Largura
    case 4:
    {
        int verticeID;
        cout << "Digite o ID do vertice para iniciar o caminhamento em Largura: ";
        cin >> verticeID;

        graph->buscaLargura(verticeID);   
        break;
    }

    // Vertices de Articulacao
    case 5:
    {
        if(graph->isDigraph()) {
            cout << "Encontrar Vertices de articulacao somente para grafos nao direcionados!" << endl;
            return;
        }

        graph->verticesArticulacao();
        break;
    }

    // Imprime componentes conexas
    case 6:
    {
        graph->imprimeComponentesConexas();
        break;
    }

    // IMPRIME OREDEM DO GRAFO
    case 7:
    {
        cout << "Ordem do Grafo: " << graph->getOrdem() << endl;
        break;
    }

    // ADICIONA NO
    case 8:
    {
        int id;
        cout << "Digite o id do no: ";
        cin >> id;
        No *noTeste = graph->insereNo(id, 1);
        if (noTeste == NULL)
            cout << "Esse no ja existe" << endl;
        else
        {
            cout << "No inserido com sucesso." << endl;
            string outputFilePath = OUTPUT_DIRECTORY + nome_arquivo_saida;
            arquivoDeEscrita.open(outputFilePath, ios::out | ios::trunc);
            armazenarGrafo(arquivoDeEscrita, graph, graph->isDigraph(), pesoAresta, pesoNo);
            arquivoDeEscrita.close();
        }
        break;
    }

    // REMOVE NO
    case 9:
    {
        int id;
        cout << "Digite o id do no a remover: ";
        cin >> id;

        if (graph->removeNo(id, graph->isDigraph()))
        {
            cout << "No removido com sucesso." << endl;
            string outputFilePath = OUTPUT_DIRECTORY + nome_arquivo_saida;
            arquivoDeEscrita.open(outputFilePath, ios::out | ios::trunc);
            armazenarGrafo(arquivoDeEscrita, graph, graph->isDigraph(), pesoAresta, pesoNo);
            arquivoDeEscrita.close();
        }
        else
            cout << "Este no nao existe no grafo." << endl;
        break;
    }

    // ADICIONA ARESTA
    case 10:
    {
        int id1, id2, peso;
        cout << "Digite o id do no de origem: ";
        cin >> id1;

        cout << "Digite o id do no de destino: ";
        cin >> id2;

        cout << "Digite o peso da aresta (obs: se nao for ponderado nas arestas digite 1): ";
        cin >> peso;

        graph->insertAresta(id1, id2, peso, true, graph->isDigraph());

        string outputFilePath = OUTPUT_DIRECTORY + nome_arquivo_saida;
        arquivoDeEscrita.open(outputFilePath, ios::out | ios::trunc);
        armazenarGrafo(arquivoDeEscrita, graph, graph->isDigraph(), pesoAresta, pesoNo);
        arquivoDeEscrita.close();

        break;
    }

    // REMOVE ARESTA
    case 11:
    {
        int id1, id2;
        cout << "Digite o id do no de origem: ";
        cin >> id1;

        cout << "Digite o id do no de destino: ";
        cin >> id2;
        if (graph->removeAresta(id1, id2, graph->isDigraph()))
        {
            cout << "Aresta removida com sucesso." << endl;

            string outputFilePath = OUTPUT_DIRECTORY + nome_arquivo_saida + ".txt";
            arquivoDeEscrita.open(outputFilePath, ios::out | ios::trunc);
            armazenarGrafo(arquivoDeEscrita, graph, graph->isDigraph(), pesoAresta, pesoNo);
            arquivoDeEscrita.close();
        }
        else
            cout << "Aresta nao existe no grafo." << endl;
        break;
    }

    //Graus dos nos
    case 12:
    {
        int idNo;
        cout << "Digite o ID que deseja saber o grau: ";
        cin >> idNo;
        
        No *noAux;

        noAux = graph->getNo(idNo);

        if(noAux == NULL) {
            cout << "Este no nao esta contido no grafo." << endl;
            return;
        }
        
        cout << "------------------------\nID: " << idNo << endl;
        if(graph->isDigraph()) {
            cout << "Grau de entrada   | " << noAux->getGrauEntrada() << endl;
            cout << "Grau de saida     | " << noAux->getGrauSaida() << endl;
        }
        else {
            cout << "Grau              | " << noAux->getGrau() << endl;
        }        
    }
    }
}
//-----------------fim menu-----------------------------------


int main(int argc, char const *argv[])
{

    if (argc != 6)
    {
        cout << argc;
        cout << "DADOS INVALIDOS!" << endl;
        return 1;
    }

    nome_arquivo_entrada = (argv[1]);
    nome_arquivo_saida = (argv[2]);

    string outputFilePath = OUTPUT_DIRECTORY + nome_arquivo_saida + ".txt";
    string inputFilePath;

    //se o grafo for ponderado arquivo de entrada no diretorio input_file/grafos ponderados na aresta
    if(stoi(argv[4]) == 1) {
        inputFilePath = INPUT_DIRECTORY_1 + nome_arquivo_entrada + ".txt";
    }
    else {
        inputFilePath = INPUT_DIRECTORY_2 + nome_arquivo_entrada + ".txt";
    }

    // Abrindo arquivo
    ifstream arq_entrada;
    ofstream arq_saida;

    arq_entrada.open(inputFilePath, ios::in);
    arq_saida.open(outputFilePath, ios::out | ios::trunc);

    Grafo *grafoTeste;

    bool digrafo = false;
    bool pesoAresta = false;
    bool pesoNo = false;
    if (arq_entrada.is_open())
    {
        digrafo = atoi(argv[3]) == 1;
        pesoAresta = atoi(argv[4]) == 1;
        pesoNo = atoi(argv[5]) == 1;

        grafoTeste = leitura(arq_entrada, digrafo, pesoAresta, pesoNo);
        armazenarGrafo(arq_saida, grafoTeste, digrafo, pesoAresta, pesoNo);
    }
    else
    {
        cout << "falha ao abrir arquivo de leitura.";
    }

    int selecao = 1;

    while (selecao != 0)
    {
        selecao = menu();
        selecionar(selecao, grafoTeste, arq_saida, pesoAresta, pesoNo);
    }

    arq_entrada.close();
    arq_saida.close();

    return 0;
}
