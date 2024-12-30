#ifndef CONJUNTO_H
#define CONJUNTO_H

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;
class Conjunto
{
public:
    vector<int> parent;

    Conjunto(int tamanho)
    {
    }

    void adicionarVertice(int id)
    {
        if (mapeamento.find(id) == mapeamento.end())
        {
            int novoIndice = valoresReais.size();
            mapeamento[id] = novoIndice;
            valoresReais.push_back(novoIndice);
        }
    }
    int encontrar(int x, int primeiraInteracao)
    {
        if(primeiraInteracao)
            x = mapeamento[x];
        if (valoresReais[x] == x)
        {
            return x;
        }
        return valoresReais[x] = encontrar(valoresReais[x], 0);
    }

    bool mesmoConjunto(int x, int y)
    {
        return encontrar(x,1) == encontrar(y,1);
    }

    void unirConjuntos(int x, int y)
    {
        int raizX = encontrar(x,1);
        int raizY = encontrar(y,1);

        if (raizX != raizY)
        {
            valoresReais[raizX] = raizY;
        }
    }

private:
    vector<int> valoresReais;
    unordered_map<int, int> mapeamento;
};
#endif /* CONJUNTO_H */
