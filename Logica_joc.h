#ifndef LOGICA_JOC_H
#define LOGICA_JOC_H

#include <iostream>
#include <string>
#include "Piese.h"
#include "Tabla_de_sah.h"


using namespace std;
class Logica_joc
{
    public:
        bool verificaMiscare( Piese& p, int xInitial, int yInitial, int xFinal, int yFinal,string culoare,Tabla_de_sah tabla);
        bool verificaMiscareTurn(int xInitial, int yInitial, int xFinal, int yFinal,Tabla_de_sah tabla);
        bool verificaMiscarePion(int xInitial, int yInitial, int xFinal, int yFinal,string culoare,Tabla_de_sah tabla);
        bool verificaMiscareNebun(int xInitial, int yInitial, int xFinal, int yFinal,string culoare,Tabla_de_sah tabla);
        bool verificaMiscareCal(int xInitial, int yInitial, int xFinal, int yFinal, string culoare,Tabla_de_sah tabla);
        bool verificaMiscareRegina(int xInitial,int yInitial,int xFinal,int yFinal,string culoarePiesa,Tabla_de_sah tabla);
        bool verificaMiscareRege(int xInitial,int yInitial,int xFinal,int yFinal,string culoarePiesa,Tabla_de_sah tabla);
        bool esteSahMat(string culoare, Tabla_de_sah tabla);
        bool esteSah(string culoare,Tabla_de_sah tabla);
        bool verificaSahDupaMutare(int xInitial, int yInitial, int xFinal, int yFinal, string culoare, Tabla_de_sah tabla);


    protected:

    private:

};

#endif // LOGICA_JOC_H
