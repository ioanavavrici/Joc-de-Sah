#include "Tabla_de_sah.h"
#include <iostream>
#include "Piese.h"
using namespace std;
Tabla_de_sah::Tabla_de_sah()
{
    char piese[2][8] =
    {
         {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
    };

    bool ok=false;
    int k=1;
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            if (i < 2)
            {
                tabla[i][j] = piese[i][j];
            }
            else if(i>=6)
            {
                tabla[i][j] =toupper(piese[k][j]);
                ok=true;
            }
            else
            {
                tabla[i][j]='*';
            }
        }
        if(ok==true)
        {
            k--;
        }
    }

}
void Tabla_de_sah::reinitializeazaTabla()
{
    char piese[2][8] =
    {
        {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
    };

    bool ok = false;
    int k = 1;

    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            if (i < 2)
            {
                tabla[i][j] = piese[i][j];
            }
            else if (i >= 6)
            {
                tabla[i][j] = toupper(piese[k][j]); // Piese considerate albe vor fi scrise cu litere mari
                ok = true;
            }
            else
            {
                tabla[i][j] = '*';
            }
        }
        if (ok == true)
        {
            k--;
        }
    }
}

void Tabla_de_sah::afiseazaTabla()
{
    cout << "    1   2   3   4   5   6   7   8" << endl;
    cout << "  +-------------------------------+" << endl;
    for (int i = 0; i < 8; ++i)
    {
        cout << 8 - i << " | ";
        for (int j = 0; j < 8; ++j)
        {
            cout << tabla[i][j]<<" | ";
        }
        cout <<8 - i <<endl<< "  +-------------------------------+  "<<endl ;

    }
    cout << "    1   2   3   4   5   6   7   8" << endl;
}
Piese piesa('*',""); // Declare a Piese object outside of the if statements

Piese& Tabla_de_sah::getValoareCelula(int x, int y)
{
    char piesaChar = tabla[x][y];

    if (islower(piesaChar))
    {
        piesa = Piese(piesaChar, "negru");
    }
    else if (isupper(piesaChar))
    {
        piesa = Piese(piesaChar, "alb");
    }

    return piesa;
}


char Tabla_de_sah::getvaloareCelula(int x, int y)
{
    return tabla[x][y];

}
void Tabla_de_sah::setValoareCelula(int x, int y, char valoare)
{
    if(valoare == 'P' )
    {
        if(x==0)
        {

            char alegereTipPiesa;

            cout << "Alege tipul piesei in care vrei sa promovezi pionul (Q/R/B/N): ";
            cin >> alegereTipPiesa;

            while (alegereTipPiesa != 'Q' && alegereTipPiesa != 'R' && alegereTipPiesa != 'B' && alegereTipPiesa!= 'N')
            {
                cout << "Optiune invalida. Alege tipul piesei din lista: Q/R/B/N: ";
                cin >> alegereTipPiesa;
            }
            tabla[x][y] = alegereTipPiesa;
        }
        else
        {
            tabla[x][y] = valoare;
        }

    }
    else
    {
        tabla[x][y] = valoare;
    }
   // tabla[x][y] = valoare;
}
void Tabla_de_sah::stergePiesa(int x, int y)
{
    tabla[x][y] = '*'; // Setează simbolul corespunzător poziției (x, y) ca fiind un spațiu gol
}

Tabla_de_sah::~Tabla_de_sah()
{

}
