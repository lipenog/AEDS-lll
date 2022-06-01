#include <stdio.h>
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

int tempo;

int *adj(int *matriz, int tamanho, int vertice)
{
    int *tmp = new int[tamanho];
    int *aux = tmp;
    for(int *ptr = &matriz[tamanho*vertice]; ptr < &matriz[tamanho*vertice] + tamanho; ptr++){
        if(*ptr != 0){
            *tmp = ptr - &matriz[tamanho*vertice] + 1;
            tmp++;
        }
    }
    return aux;
}

void dfs_visit(int u, int *cor, int *d, int *f, int tamanho, int *matriz)
{
    int v;
    cor[u-1] = 1;
    tempo++;
    d[u-1] = tempo;
    int i = 0;
    int *aux = adj(matriz, tamanho, u-1);
    for(int *tmp = aux; i < tamanho - 1; tmp++, i++) {
        if(cor[tmp - aux] == 0){
            cout << "dfs visit - vertice = " << *tmp << endl;
            dfs_visit(*tmp, cor, d, f, tamanho, matriz);
        }
    }
    cor[u-1] = 2;
    tempo++;
    f[u-1] = tempo;
}

void dfs(int *vertices, int *cor, int *d, int *f, int tamanho, int *matriz)
{
    for(int *tmp = vertices; tmp < vertices + tamanho; tmp++){
        cor[tmp - vertices] = 0;
    }
    tempo = 0;
    for(int *tmp = vertices; tmp < vertices + tamanho; tmp++){
        if(cor[tmp - vertices] == 0){
            cout << "dfs - vertice = " << *tmp << endl;
            dfs_visit(*tmp, cor, d, f, tamanho, matriz);
        }
    }
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


    int *nome = new int[qtd_linhas];
    int *d = new int[qtd_linhas];
    int *f = new int[qtd_linhas];
    int *cor = new int[qtd_linhas];

    int *tmp = nome;

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

    // PRINTA A MATRIZ DO ARQ
    for (ptr = matriz_dados; ptr < matriz_dados+qtd_linhas*3; ptr++, i++){
        if (i == 3) {
        //    cout << endl;
            i = 0;
        }
        //cout << *ptr << " ";
    } 

    // RODA PELA MATRIZ CALCULANDO OS VALORES DA ARESTA
    int x1, x2, y1, y2;
    for (int i = 0; i < qtd_linhas; i++) {
        *tmp = matriz_dados[3*i];
        tmp++;
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

    // PRINTA A MATRIZ DE ARESTA
    for (ptr = matriz; ptr < matriz+(qtd_linhas*qtd_linhas); ptr++, i++){
        if (i == qtd_linhas - 1) {
        //    cout << endl;
            i = 0;
        }
        //cout << *ptr << " ";
    } 
    for (int i = 0; i < qtd_linhas; i++) {
        cout << "ADJ de " << i+1 << endl;
        for (int *a = adj(matriz, qtd_linhas, i), j = 0; j < qtd_linhas; j++, a++) {
            cout << *a << " ";
        }
        cout << endl;
    }
    dfs(nome, cor, d, f, qtd_linhas, matriz);
    for (int *i = nome, *j = d, *k = f, *l = cor; i < nome + qtd_linhas; i++, j++, k++, l++) {
        cout << "V: " << *i << " d: " << *j << " f: " << *k << " cor: " << *l << endl;
    }
    cout << endl;

    return 0;
}
