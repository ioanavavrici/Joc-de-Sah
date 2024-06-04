#ifndef TABLA_DE_SAH_H
#define TABLA_DE_SAH_H
#include <iostream>
#include "Piese.h"

using namespace std;

class Tabla_de_sah
{
    private:
         char tabla[8][8];
    public:

        Tabla_de_sah();
        virtual ~Tabla_de_sah();
        void reinitializeazaTabla();
        Piese& getValoareCelula(int x, int y);
        char getvaloareCelula(int x, int y);
        void setValoareCelula(int x, int y, char valoare);
        void stergePiesa(int x, int y);
        void afiseazaTabla();

    protected:


};

#endif // TABLA_DE_SAH_H
