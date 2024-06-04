#ifndef JOC_H
#define JOC_H
#include <iostream>
#include <string>
#include "Tabla_de_sah.h"
#include "Logica_joc.h"
#include "Piese.h"
using namespace std;

class Joc
{
    public:
        Joc() ;
        virtual ~Joc();

    protected:

    private:
         Tabla_de_sah tabla;
         Logica_joc logica ;
};

#endif // JOC_H
