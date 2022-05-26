#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;

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

    int **matriz = new int*[qtd_linhas];

    if ( myfile2.is_open() ) {
        cout << "OK" << endl;
        for (int i = 0; i < qtd_linhas; i++)
        {
            myfile2 >> v;
            myfile2 >> x;
            myfile2 >> y;
            cout << v << " " << x << " " << y << endl;
            matriz[x][y] = v;
        }
    }
    for (int i = 0; i < qtd_linhas; i++){
        for (int j = 0; j < qtd_linhas; j++){
            cout << matriz[i][j];
        }
    }


    return 0;
}
