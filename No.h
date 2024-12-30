#ifndef NO_H
#define NO_H
#include <iostream>
#include <stdlib.h>
#include <string>
#include "Aresta.h"

using namespace std;
class Aresta;

class No
{
public:
    No(int idNo);
    No(int idNo, int weight);
    virtual ~No();

    // Gets
    int getIdNo() { return idNo; }
    int getPeso() { return pesoNo; }
    int getGrau() { return grauSaida; }
    int getGrauEntrada() { return grauEntrada; }
    int getGrauSaida() { return grauSaida; }
    No *getProxNo() { return proxNo; }
    Aresta *getPrimeiraAresta() { return primeiraAresta; }

    // Sets
    void setIdNo(int valor) { idNo = valor; }
    void setPeso(int valor) { pesoNo = valor; }
    void setProxNo(No *novoNo) { proxNo = novoNo; }
    void setPrimeiraAresta(Aresta *novaAresta) { primeiraAresta = novaAresta; }

    // Outras
    void incGrau();
    void decGrau();
    void incrementaGrauEntrada();
    void decrementaGrauEntrada();
    void incrementaGrauSaida();
    void decrementaGrauSaida();
    void incluirAresta(int idNoDestino, int pesoAresta, int arestaDuplicada);
    bool excluirAresta(int idNoDestino);
    Aresta *procurarAresta(int idNoDestino);

private:
    int idNo;
    int pesoNo;
    int grauEntrada;
    int grauSaida;
    No *proxNo;
    Aresta *primeiraAresta;
    Aresta *ultimaAresta;
};

#endif     /* NO_H */
