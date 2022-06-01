#include <stdio.h>
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

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
            cout << endl;
            i = 0;
        }
        cout << *ptr << " ";
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
            cout << endl;
            i = 0;
        }
        cout << *ptr << " ";
    } 

    return 0;
}
