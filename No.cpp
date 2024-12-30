#include "No.h"

using namespace std;

No::No(int name)
{
    this->idNo = name;
    this->pesoNo = 0;
    this->grauEntrada = 0;
    this->grauSaida = 0;
    this->proxNo = NULL;
    this->primeiraAresta = NULL;
}

No::No(int name, int peso)
{
    this->idNo = name;
    this->pesoNo = peso;
    this->grauEntrada = 0;
    this->grauSaida = 0;
    this->proxNo = NULL;
    this->primeiraAresta = NULL;
}

No::~No()
{
    Aresta *auxEdge = getPrimeiraAresta();
    while (auxEdge != NULL)
    {
        Aresta *auxNextEdge = auxEdge->getProxAresta();
        delete (auxEdge);
        auxEdge = auxNextEdge;
    }
}

void No::incGrau()
{
    this->grauEntrada++;
    this->grauSaida++;
}
void No::decGrau()
{
    this->grauEntrada--;
    this->grauSaida--;
}

void No::incrementaGrauEntrada()
{
    this->grauEntrada++;
}
void No::decrementaGrauEntrada()
{
    this->grauEntrada--;
}

void No::incrementaGrauSaida()
{
    this->grauSaida++;
}
void No::decrementaGrauSaida()
{
    this->grauSaida--;
}

void No::incluirAresta(int idNoDestino, int pesoAresta, int arestaDuplicada)
{
    Aresta *novaAresta = new Aresta(idNoDestino, pesoAresta, arestaDuplicada);
    if (primeiraAresta == NULL)
    {
        primeiraAresta = novaAresta;
    }
    else
    {
        novaAresta->setProxAresta(primeiraAresta);
        primeiraAresta = novaAresta;
    }
}

bool No::excluirAresta(int idNoDestino)
{
    if (this->primeiraAresta->getIdNoDestino() == idNoDestino)
    {
        // TODO Arrumar
        Aresta *arestaExcluir = this->primeiraAresta;
        primeiraAresta = primeiraAresta->getProxAresta();
        delete (arestaExcluir);
        return true;
    }
    else
    {
        Aresta *arestaAux = this->primeiraAresta->getProxAresta();
        Aresta *arestaAnt = this->primeiraAresta;
        while (arestaAux != NULL)
        {
            if (arestaAux->getIdNoDestino() == idNoDestino)
            {
                arestaAnt->setProxAresta(arestaAux->getProxAresta());
                delete (arestaAux);
                return true;
            }

            arestaAnt = arestaAux;
            arestaAux = arestaAux->getProxAresta();
        }
        return false;
    }
}

Aresta *No::procurarAresta(int idNoDestino)
{
    Aresta *arestaAux = primeiraAresta;
    while (arestaAux != NULL)
    {
        if (arestaAux->getIdNoDestino() == idNoDestino)
        {
            return arestaAux;
        }
        arestaAux = arestaAux->getProxAresta();
    }
    return NULL;
}
