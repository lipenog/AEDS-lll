#include <stdio.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <list>


using namespace std;

typedef struct
{
    int d;
    int pi;
}vertice;


int tamanhoGrafo(string nomeArq)
{
    ifstream myfile ("teste.txt");
    string linha;
    int tamanho = 0;
    // ABRE O ARQ E FAZ A CONTAGEM DE LINHAS
    if ( myfile.is_open() ) {
        while (getline(myfile, linha))
        {
            tamanho++;
        }
    }
    myfile.close();
    return tamanho;
}

int *leArq(string nomeArq, int tamanho)
{
    int *matriz;
    int x, y, v;

    ifstream myfile2 ("teste.txt");

    matriz = (int*) malloc(sizeof(int)*tamanho*3);

    int *ptr = matriz;
    // PERCORRE O ARQ DNV E GUARDA OS VALORES EM UMA MATRIZ
    if ( myfile2.is_open() ) {
        for (int i = 0; i < tamanho; i++)
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
    return matriz;
}

int *calculaAresta(int *matrizDados, int tamanho)
{
    int *matriz = (int*) malloc(sizeof(int)*tamanho*tamanho);
    // RODA PELA MATRIZ CALCULANDO OS VALORES DA ARESTA
    int x1, x2, y1, y2;
    for (int i = 0; i < tamanho; i++) {
        // COMO TODAS OS V SÃO CONECTADOS BASTA FAZER X1 E Y1 1 VEZ POR REP
        x1 = matrizDados[3*i + 1];
        y1 = matrizDados[3*i + 2];
        // A DIAGONAL SEMPRE É 0, O RESTANTE É USADO A FORMULA 
        for (int j = 0; j < tamanho; j++) {
            if (i != j) {
                x2 = matrizDados[3*j + 1];
                y2 = matrizDados[3*j + 2];
                matriz[tamanho*i+j] = sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
            } else {
                matriz[tamanho*i+j] = 0;
            }
        }
    } 
    return matriz;
}

vertice *inicializa(int *matriz, int tamanho, int s)
{
    vertice *v = (vertice*)malloc(sizeof(vertice)*tamanho);
    for (int i = 0; i < tamanho; i++){
        v[i].d = 999999;
        v[i].pi = -1;
    }
    v[s].d = 0;
    return v;
}
vertice *relaxa(vertice *a, int u, int v, int *w, int tamanho)
{
    if (a[v].d > (a[u].d + w[tamanho*u+v]))
    {   
        a[v].d = a[u].d + w[tamanho*u+v];
        a[v].pi = u;
    }
    return a;
}

bool verificaQ(int *Q, int tamanho)
{
    for (int i = 0; i < tamanho; i++)
    {
        if (Q[i] == 1){
            return true;
        }
    }
    return false;
}

int extrairMinimo(int **Q, vertice *a, int tamanho)
{
    int menorValor = 999999;
    int menorIndex = -1;
    for(int i = 0; i < tamanho; i++)
    {
        if(a[i].d < menorValor)
        {
            menorValor = a[i].d;     
            menorIndex = i;       
        }        
    }
    *Q[menorIndex] = 0;
    return menorValor;
}

int *uniao(int *a, int b)
{
    int *c;
    c[b] = 1;
    return c;
}

int *Adj(int u, int *matriz, int tamanho)
{
    int *tmp = (int*)malloc(sizeof(int)*tamanho);
    int *aux = tmp;
    for(int *ptr = &matriz[tamanho*u]; ptr < &matriz[tamanho*u] + tamanho; ptr++){
        if(*ptr != 0){
            *tmp = ptr - &matriz[tamanho*u];
            tmp++;
        }
    }
    return aux;
}

vertice *dijkstra(int *matriz, int tamanho, int s)
{
    vertice *a = inicializa(matriz, tamanho, s);
    int *S = (int*)malloc(sizeof(int)*tamanho);
    int *Q = (int*)malloc(sizeof(int)*tamanho);
    for (int i = 0; i < tamanho; i++){
        Q[i] = 1;
        S[i] = 0;
    }
    while (verificaQ(Q, tamanho))
    {
        int u = extrairMinimo(&Q, a, tamanho);
        S = uniao(S, u);
        int *ptr = Adj(u, matriz, tamanho);
        for (int i = 0; i < tamanho - 1; i++)
        {
            a = relaxa(a, u, ptr[i], matriz, tamanho);
        }
    }
    return a;
}

void printVertice(vertice *a, int tamanho)
{
    for(int i = 0; i < tamanho; i++)
    {
        cout << "Verice " << i << endl;
        cout << a[i].d << endl;
        cout << a[i].pi << endl;
    }
}

int main(void)
{
    int tamanho = tamanhoGrafo("teste.txt");
    int *matrizDados = leArq("teste.txt", tamanho);
    int *matriz = calculaAresta(matrizDados, tamanho);
    vertice *a = dijkstra(matriz, tamanho, 0);
    printVertice(a, tamanho);
    
    return 0;
}
