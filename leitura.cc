#include <stdio.h>
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

float dist_pontos(int x1, int x2, int y1, int y2)
{
    return sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
}


int main(void)
{
    
    int v, x, y, qtd_linhas = 0;
    ifstream myfile ("teste");
    string linha;
    
    if ( myfile.is_open() ) {
        cout << "OK" << endl;
        while (getline(myfile, linha))
        {
            qtd_linhas++;
        }
    }
    cout << qtd_linhas << endl;

    myfile.close();
    ifstream myfile2 ("teste");

    int *matriz = new int[qtd_linhas];
    int *matriz_dados = new int[qtd_linhas*3];
    int *ptr = matriz_dados;

    if ( myfile2.is_open() ) {
        cout << "OK" << endl;
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
    int i = 0;
    for (ptr = matriz_dados; ptr < matriz_dados+qtd_linhas*3; ptr++, i++){
        cout << *ptr << " ";
        if (i == 3) {
            cout << endl;
            i = 0;
        }
    } 
    /*
    for (int i = 0; i < qtd_linhas; i++){
        for (int j = 0; j < qtd_linhas; j++){
            cout << matriz[qtd_linhas*i+j];
        }
    }
    */

    return 0;
}
