#include <iostream>
#include <stdlib.h>
#include <string>
#include "Aresta.h"

using namespace std;


Aresta::Aresta(int idNoDestino){
    this->idOrigem = idOrigem;
    this->idNoDestino = idNoDestino;
    this->pesoAresta = 1;
    this->proxAresta = nullptr;
}

Aresta::Aresta(int idNoDestino, int pesoAresta, int arestaDuplicada){
    this->idOrigem = idOrigem;
    this->idNoDestino = idNoDestino;
    this->pesoAresta = pesoAresta;
    this->arestaDuplicada = arestaDuplicada;
    this->proxAresta = nullptr;
}


/** Destructor */
Aresta::~Aresta() {
    //dtor
}

