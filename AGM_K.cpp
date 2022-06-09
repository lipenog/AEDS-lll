#include <stdio.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <list>

using namespace std;

typedef struct
{
    int vA;
    int vB;
    float pesoAresta;
}conjunto;

list<conjunto> formaConjunto(int *matriz, int tamanho)
{
    list<conjunto> retorno;
    conjunto tmp;
    for (int i = 0; i < tamanho; i++)
    {
        for (int j = i; j < tamanho; j++)
        {
            if (i != j)
            {
                tmp.vA = i;
                tmp.vB = j;
                tmp.pesoAresta = matriz[tamanho*i+j];
                retorno.push_back(tmp);
            }
        }
    }
    return retorno;
}

list<conjunto> sortConjunto(list<conjunto> grafo, int tamanho)
{
    list<conjunto> retorno;

    list<conjunto> :: iterator p1;
    conjunto o1;

    list<conjunto> :: iterator p2;
    conjunto o2;

    list<conjunto> :: iterator p3;

    conjunto menorValor;
    int i;
    for (i = 0; i < tamanho; i++)
    {
        menorValor.pesoAresta = 9999;
        for (p2 = grafo.begin(); p2 != grafo.end(); p2++)
        {
            o2 = *p2;
            if (o2.pesoAresta < menorValor.pesoAresta)
            {
                menorValor = o2;
                p3 = p2;
            }
        }
        retorno.push_back(menorValor);
        grafo.erase(p3);
    }
    return retorno;
}

int conjuntoDe(list<conjunto> grafo, list<int> nome, int tamanho, int v)
{
    int retorno = 1;
    list<int> :: iterator p1;
    for(p1 = nome.begin(); p1 != nome.end(); p1++)
    {
        if (*p1 == v)
        {
            retorno = 0;
        }
    }
    return retorno;
}

list<int> *AGM_Kruskal(list<conjunto> grafo, list<int> nome, int tamanho)
{
    list<int> X[tamanho];
    list<conjunto> AI = sortConjunto(grafo, tamanho);
    
    list<conjunto> :: iterator p1;
    list<int> :: iterator aux;
    int i = 0;
    for (aux = nome.begin(); aux != nome.end(); aux++, i++)
    {
        X[i].push_back(*aux);
    }

    for (p1 = AI.begin(); p1 != AI.end(); p1++)
    {
        if (conjuntoDe(grafo, X[(*p1).vA], tamanho, (*p1).vB) || conjuntoDe(grafo, X[(*p1).vB], tamanho, (*p1).vB))
        {
            X[(*p1).vA].push_back(((*p1).vB)+1);
            X[(*p1).vB].clear();
        }
    }
    return X;
}

int main(void)
{
    
    int v, x, y, i = 0, qtd_linhas = 0;
    ifstream myfile ("teste");
    string linha;

    // ABRE O ARQ E FAZ A CONTAGEM DE LINHAS
    if ( myfile.is_open() ) {
        while (getline(myfile, linha))
        {
            qtd_linhas++;
        }
    }

    // FECHA O ARQ E ABRE EM UMA SEGUNDA VARIAVEL
    myfile.close();
    ifstream myfile2 ("teste");

    // FAZ A ALOCAÇÃO DINAMICA
    int *matriz = new int[qtd_linhas*qtd_linhas];
    int *matriz_dados = new int[qtd_linhas*3];
    int *ptr = matriz_dados;


    list<int> vertices;

    // PERCORRE O ARQ DNV E GUARDA OS VALORES EM UMA MATRIZ
    if ( myfile2.is_open() ) {
        for (int i = 0; i < qtd_linhas; i++)
        {
            myfile2 >> v;
            myfile2 >> x;
            myfile2 >> y;         
            *ptr = v;
            ptr++;
            *ptr = x;
            ptr++;
            *ptr = y;
            ptr++;
            
        }
    }

    // RODA PELA MATRIZ CALCULANDO OS VALORES DA ARESTA
    int x1, x2, y1, y2;
    for (int i = 0; i < qtd_linhas; i++) {
        vertices.push_back(matriz_dados[3*i]);
        // COMO TODAS OS V SÃO CONECTADOS BASTA FAZER X1 E Y1 1 VEZ POR REP
        x1 = matriz_dados[3*i + 1];
        y1 = matriz_dados[3*i + 2];
        // A DIAGONAL SEMPRE É 0, O RESTANTE É USADO A FORMULA 
        for (int j = 0; j < qtd_linhas; j++) {
            if (i != j) {
                x2 = matriz_dados[3*j + 1];
                y2 = matriz_dados[3*j + 2];
                matriz[qtd_linhas*i+j] = sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
            } else {
                matriz[qtd_linhas*i+j] = 0;
            }
        }
    } 

    list<int> :: iterator p1;
    for (p1 = vertices.begin(); p1 != vertices.end(); p1++)
    {
        cout << *p1 << " "; 
    }
    cout << endl << endl;

    list<conjunto> verticesArestas = formaConjunto(matriz, qtd_linhas);
    list<conjunto> :: iterator p2;
    int tamanhoConjunto = 0;
    for (p2 = verticesArestas.begin(); p2 != verticesArestas.end(); p2++)
    {
        tamanhoConjunto++;
        conjunto tmp = *p2;
        //cout << "( " <<tmp.vA << " , " << tmp.vB << " )  =  " << tmp.pesoAresta << endl; 
    }
    cout << endl;
    
    list<conjunto> sortAresta = sortConjunto(verticesArestas, tamanhoConjunto);
    for (p2 = sortAresta.begin(); p2 != sortAresta.end(); p2++)
    {
        conjunto tmp = *p2;
        //cout << tmp.pesoAresta << " ";
    }
    cout << endl;
    
    list<int> :: iterator *p6;
    AGM_Kruskal(verticesArestas, vertices, qtd_linhas);

    return 0;
}

