#ifndef ARESTA_H
#define ARESTA_H
#include <iostream>
#include <stdlib.h>
#include <string>
#include "No.h"

using namespace std;

class No;

class Aresta
{
public:
    Aresta(int noDestino);
    Aresta(int noDestino, int pesoAresta, int arestaDuplicada);
    ~Aresta();

    // Gets
    int getPesoAresta() { return pesoAresta; }
    int getIdOrigem() { return idOrigem; }
    int getIdNoDestino() { return idNoDestino; }
    int getArestaDuplicada() { return arestaDuplicada; }
    Aresta *getProxAresta() { return proxAresta; }

    // Sets
    void setPesoAresta(int valor) { pesoAresta = valor; }
    void setIdOrigem(int valor) { idOrigem = valor; }
    void setIdNoDestino(int valor) { idNoDestino = valor; }
    void setProxAresta(Aresta *aresta) { proxAresta = aresta; }

private:
    int pesoAresta;
    int idOrigem;
    int idNoDestino;
    int arestaDuplicada;
    Aresta *proxAresta;
};

#endif // ARESTA_H
