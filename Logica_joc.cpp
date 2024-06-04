#include "Logica_joc.h"
#include <iostream>
#include <cmath>
#include <string>
#include "Tabla_de_sah.h"

using namespace std;
bool Logica_joc::verificaMiscare( Piese& p, int xInitial, int yInitial, int xFinal, int yFinal,string culoare,Tabla_de_sah tabla)
{

    char x=tabla.getvaloareCelula(xInitial,yInitial);
    char tipPiesa = p.getTip();
    string culoarePiesa = p.getCuloare();
    if(tipPiesa=='*')
        return false;
    if(culoare==culoarePiesa)
    {
        switch(tipPiesa)
        {
        case 'P':

            return verificaMiscarePion(xInitial,yInitial,xFinal,yFinal,culoarePiesa,tabla);
            break;
        case 'K':
            return verificaMiscareRege( xInitial, yInitial, xFinal, yFinal, culoarePiesa,tabla);
            break;
        case 'Q':
            return verificaMiscareRegina(xInitial,yInitial,xFinal,yFinal,culoarePiesa,tabla);

            break;
        case 'R':
            return verificaMiscareTurn(xInitial,yInitial,xFinal,yFinal,tabla);
            break;
        case 'N':
            return verificaMiscareCal(xInitial,yInitial,xFinal,yFinal,culoarePiesa,tabla);
            break;
        case 'B':
            return verificaMiscareNebun(xInitial,yInitial,xFinal,yFinal,culoarePiesa,tabla);
            break;

        }

    }
    if(culoare==p.getCuloare())
    {
        switch(tipPiesa)
        {
        case 'p':
            return verificaMiscarePion(xInitial,yInitial,xFinal,yFinal,culoarePiesa,tabla);
            break;
        case 'k':
            return verificaMiscareRege( xInitial, yInitial, xFinal, yFinal, culoarePiesa, tabla);
            break;
        case 'q':
            return verificaMiscareRegina(xInitial,yInitial,xFinal,yFinal,culoarePiesa,tabla);
            break;
        case 'r':
            return verificaMiscareTurn(xInitial,yInitial,xFinal,yFinal,tabla);
            break;
        case 'n':
            return verificaMiscareCal(xInitial,yInitial,xFinal,yFinal,culoarePiesa,tabla);
            break;
        case 'b':
            return verificaMiscareNebun(xInitial,yInitial,xFinal,yFinal,culoarePiesa,tabla);
            break;


        }

    }

}
bool Logica_joc::verificaMiscareRege(int xInitial, int yInitial, int xFinal, int yFinal, string culoarePiesa, Tabla_de_sah tabla)
{
    // Calculăm distanțele în x și y
    int deltaX = abs(xFinal - xInitial);
    int deltaY = abs(yFinal - yInitial);

    // Verificăm dacă mișcarea este în raza unui pătrat
    if (deltaX <= 1 && deltaY <= 1)
    {
        // Verificăm dacă destinația este liberă sau ocupată de o piesă adversă
        char celulaFinala = tabla.getvaloareCelula(xFinal, yFinal);
        char celulaInitiala = tabla.getvaloareCelula(xInitial, yInitial);

        // Regele poate muta doar pe o poziție liberă sau pe o poziție ocupată de o piesă adversă
        if (celulaFinala == '*' ||
                (isupper(celulaInitiala) && islower(celulaFinala)) ||
                (islower(celulaInitiala) && isupper(celulaFinala)))
        {
            // Simulăm mutarea regelui
            tabla.setValoareCelula(xFinal, yFinal, celulaInitiala);
            tabla.setValoareCelula(xInitial, yInitial, '*');

            // Verificăm dacă regele este în șah în noua poziție
            bool inSah = esteSah(culoarePiesa, tabla);

            // Restaurăm tabla
            tabla.setValoareCelula(xInitial, yInitial, celulaInitiala);
            tabla.setValoareCelula(xFinal, yFinal, celulaFinala);

            // Dacă regele nu este în șah, mutarea este validă
            if (!inSah)
            {
                return true;
            }
        }
    }

    // Mișcarea nu este validă
    return false;
}

bool Logica_joc::verificaMiscareRegina(int xInitial, int yInitial, int xFinal, int yFinal, string culoarePiesa, Tabla_de_sah tabla)
{
    bool Traseu_liber = true;

    if (xInitial == xFinal || yInitial == yFinal)
    {
        // Verificăm dacă este o mișcare pe aceeași coloană
        if (xInitial == xFinal)
        {
            int minCol, maxCol;
            if (yInitial < yFinal)
            {
                minCol = yInitial;
                maxCol = yFinal;
            }
            else
            {
                minCol = yFinal;
                maxCol = yInitial;
            }
            for (int i = minCol + 1; i < maxCol; i++)
            {
                if (tabla.getvaloareCelula(xInitial, i) != '*')
                {
                    Traseu_liber = false;
                    break;
                }
            }
        }
        // Verificăm dacă este o mișcare pe același rând
        else if (yInitial == yFinal)
        {
            int minRow, maxRow;
            if (xInitial < xFinal)
            {
                minRow = xInitial;
                maxRow = xFinal;
            }
            else
            {
                minRow = xFinal;
                maxRow = xInitial;
            }
            for (int i = minRow + 1; i < maxRow; i++)
            {
                if (tabla.getvaloareCelula(i, yFinal) != '*')
                {
                    Traseu_liber = false;
                    break;
                }
            }
        }
    }
    else if (abs(xInitial - xFinal) == abs(yFinal - yInitial))
    {
        // Verificăm dacă este o mișcare pe diagonală
        if (xInitial > xFinal && yInitial < yFinal)
        {
            for (int i = 1; i < (xInitial - xFinal); i++)
            {
                if (tabla.getvaloareCelula(xInitial - i, yInitial + i) != '*')
                {
                    Traseu_liber = false;
                    break;
                }
            }
        }
        else if (xInitial < xFinal && yInitial > yFinal)
        {
            for (int i = 1; i < (xFinal - xInitial); i++)
            {
                if (tabla.getvaloareCelula(xInitial + i, yInitial - i) != '*')
                {
                    Traseu_liber = false;
                    break;
                }
            }
        }
        else if (xInitial > xFinal && yInitial > yFinal)
        {
            for (int i = 1; i < (xInitial - xFinal); i++)
            {
                if (tabla.getvaloareCelula(xInitial - i, yInitial - i) != '*')
                {
                    Traseu_liber = false;
                    break;
                }
            }
        }
        else if (xInitial < xFinal && yInitial < yFinal)
        {
            for (int i = 1; i < (xFinal - xInitial); i++)
            {
                if (tabla.getvaloareCelula(xInitial + i, yInitial + i) != '*')
                {
                    Traseu_liber = false;
                    break;
                }
            }
        }
    }
    else
    {
        return false; // Nu este o mișcare validă pentru regină
    }

    // Verificăm dacă destinația este liberă sau conține o piesă adversă
    char celulaFinala = tabla.getvaloareCelula(xFinal, yFinal);
    char celulaInitiala = tabla.getvaloareCelula(xInitial, yInitial);

    if (Traseu_liber && (celulaFinala == '*' ||
                         (isupper(celulaInitiala) && !isupper(celulaFinala)) ||
                         (!isupper(celulaInitiala) && isupper(celulaFinala))))
    {
        return true;
    }

    return false;
}


bool Logica_joc::verificaMiscareCal(int xInitial, int yInitial, int xFinal, int yFinal, string culoare, Tabla_de_sah tabla)
{
    bool Traseu_liber = false;

    if ((xInitial - 2 == xFinal && (yInitial - 1 == yFinal || yInitial + 1 == yFinal)) ||
            (xInitial - 1 == xFinal && (yInitial - 2 == yFinal || yInitial + 2 == yFinal)) ||
            (xInitial + 1 == xFinal && (yInitial - 2 == yFinal || yInitial + 2 == yFinal)) ||
            (xInitial + 2 == xFinal && (yInitial - 1 == yFinal || yInitial + 1 == yFinal)))
    {
        if (tabla.getvaloareCelula(xFinal, yFinal) == '*' || (isupper(tabla.getvaloareCelula(xInitial, yInitial)) && islower(tabla.getvaloareCelula(xFinal, yFinal))) || (isupper(tabla.getvaloareCelula(xFinal ,yFinal)) && islower(tabla.getvaloareCelula(xInitial, yInitial))))
        {
            Traseu_liber = true;
        }
    }

    return Traseu_liber;
}


bool Logica_joc::verificaMiscareNebun(int xInitial, int yInitial, int xFinal, int yFinal, string culoare, Tabla_de_sah tabla)
{
    bool Traseu_liber = true;

    int deltaX = xFinal - xInitial;
    int deltaY = yFinal - yInitial;

    // Verificăm dacă mutarea este diagonală
    if (deltaX != 0 && deltaY != 0 && abs(deltaX) == abs(deltaY))
    {
        int pasX = (deltaX > 0) ? 1 : -1;
        int pasY = (deltaY > 0) ? 1 : -1;

        // Verificăm dacă traseul este liber
        for (int i = 1; i < abs(deltaX); i++)
        {
            if (tabla.getvaloareCelula(xInitial + i * pasX, yInitial + i * pasY) != '*')
            {
                Traseu_liber = false;
                break;
            }
        }

        char celulaFinala = tabla.getvaloareCelula(xFinal, yFinal);
        char celulaInitiala = tabla.getvaloareCelula(xInitial, yInitial);

        // Verificăm dacă destinația este liberă sau conține o piesă adversă
        if (Traseu_liber && (celulaFinala == '*' ||
                             (isupper(celulaInitiala) && !isupper(celulaFinala)) ||
                             (!isupper(celulaInitiala) && isupper(celulaFinala))))
        {
            return true;
        }
    }

    return false;
}


bool Logica_joc::verificaMiscarePion(int xInitial, int yInitial, int xFinal, int yFinal, string culoare, Tabla_de_sah tabla)
{
      bool Traseu_liber=true;

   //cout<<xInitial<<" "<<yInitial<<" "<<xFinal<<" "<<yFinal<<endl;
    if((yInitial==yFinal && (max(xInitial,xFinal)-min(xInitial,xFinal)<2)))
    {

        if(culoare=="negru")
        {
            for(int i=min(xInitial,xFinal)+1; i<=max(xInitial,xFinal); i++)
            {

                if(tabla.getvaloareCelula(i,yInitial)!='*')
                {
                    Traseu_liber=false;
                    break;
                }
            }
        }
        else
            for(int i=max(xInitial,xFinal)-1; i>=min(xInitial,xFinal); i--)
            {

                if(tabla.getvaloareCelula(i,yInitial)!='*')
                {  // cout<<"intra1";
                    Traseu_liber=false;
                    break;
                }
            }

    }
    else  if((yInitial==yFinal && ((max(xInitial,xFinal)-min(xInitial,xFinal)==2))&& (xInitial==1 || xInitial==6)))
    {


        if(culoare=="negru")
        {

            for(int i=min(xInitial,xFinal)+1; i<=max(xInitial,xFinal); i++)
            {


                if(tabla.getvaloareCelula(i,yInitial)!='*')
                {
                    Traseu_liber=false;
                    break;
                }
            }
        }
        else
            for(int i=max(xInitial,xFinal)-1; i>=min(xInitial,xFinal); i--)
            {

                if(tabla.getvaloareCelula(i,yInitial)!='*')
                { //cout<<"intra2";

                    Traseu_liber=false;
                    break;
                }
            }


    }
    // Mutare pe diagonală pentru captură
    else if (abs(xInitial - xFinal) == 1 && abs(yInitial - yFinal) == 1)
    {
        if (culoare == "negru" && xFinal > xInitial)
        {
            char celulaFinala = tabla.getvaloareCelula(xFinal, yFinal);
            char celulaInitiala = tabla.getvaloareCelula(xInitial, yInitial);

            if (celulaFinala == '*' ||
                (isupper(celulaInitiala) && isupper(celulaFinala)) ||
                (!isupper(celulaInitiala) && !isupper(celulaFinala)))
            {
                Traseu_liber = false;
            }
        }
        else if (culoare == "alb" && xFinal < xInitial)
        {
            char celulaFinala = tabla.getvaloareCelula(xFinal, yFinal);
            char celulaInitiala = tabla.getvaloareCelula(xInitial, yInitial);

            if (celulaFinala == '*' ||
                (isupper(celulaInitiala) && isupper(celulaFinala)) ||
                (!isupper(celulaInitiala) && !isupper(celulaFinala)))
            {
                Traseu_liber = false;
            }
        }
        else
        {
            Traseu_liber = false;
        }
    }
    // Mutare invalidă
    else
    {
        return false;
    }

    return Traseu_liber;
}



bool Logica_joc::verificaMiscareTurn(int xInitial, int yInitial, int xFinal, int yFinal, Tabla_de_sah tabla)
{
    if (xInitial == xFinal || yInitial == yFinal)
    {
        bool Traseu_liber = true;
        if (xFinal == xInitial) // verificăm dacă mutarea este pe același rând
        {
            for (int i = min(yInitial, yFinal) + 1; i < max(yInitial, yFinal); i++)
            {
                if (tabla.getvaloareCelula(xInitial, i) != '*')
                {
                    Traseu_liber = false;
                    break;
                }
            }
        }
        else if (yInitial == yFinal) // verificăm dacă mutarea este pe aceeași coloană
        {
            for (int i = min(xInitial, xFinal) + 1; i < max(xInitial, xFinal); i++)
            {
                if (tabla.getvaloareCelula(i, yFinal) != '*')
                {
                    Traseu_liber = false;
                    break;
                }
            }
        }

        // Verificăm dacă destinația este liberă sau conține o piesă adversă
        char celulaFinala = tabla.getvaloareCelula(xFinal, yFinal);
        char celulaInitiala = tabla.getvaloareCelula(xInitial, yInitial);

        if (Traseu_liber && (celulaFinala == '*' ||
                             (isupper(celulaInitiala) && islower(celulaFinala)) ||
                             (islower(celulaInitiala) && isupper(celulaFinala))))
        {
            return true;
        }
    }
    return false;
}

bool Logica_joc::esteSah(string culoare, Tabla_de_sah tabla)
{
    int xRege, yRege;
    // Găsește poziția regelui
    char rege;
    if(culoare=="alb")
        rege ='K';
    else
        rege ='k';
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (tabla.getvaloareCelula(i, j) ==rege)
            {
                xRege = i;
                yRege = j;
                break;
            }
        }
    }

    // Verifică dacă vreo piesă adversă amenință regele
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            char piesa = tabla.getvaloareCelula(i, j);
            if (piesa != '*' && ((culoare == "alb" && islower(piesa)) || (culoare == "negru" && isupper(piesa))))
            {
                Piese p(piesa, (isupper(piesa) ? "alb" : "negru"));
                if (verificaMiscare(p, i, j, xRege, yRege, (isupper(piesa) ? "alb" : "negru"), tabla))
                {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Logica_joc::esteSahMat(string culoare, Tabla_de_sah tabla)
{
    // Verificăm dacă există vreo mutare legală care scoate regele din șah
    for (int xI = 0; xI < 8; ++xI)
    {
        for (int yI = 0; yI < 8; ++yI)
        {
            char piesa = tabla.getvaloareCelula(xI, yI);
            if (piesa != '*' && ((culoare == "alb" && isupper(piesa)) || (culoare == "negru" && islower(piesa))))
            {
                for (int xF = 0; xF < 8; ++xF)
                {
                    for (int yF = 0; yF < 8; ++yF)
                    {
                        Tabla_de_sah copiaTabla = tabla;
                        Piese p(piesa, (isupper(piesa) ? "alb" : "negru"));
                        if (verificaMiscare(p, xI, yI, xF, yF, culoare, copiaTabla))
                        {
                            copiaTabla.setValoareCelula(xF, yF, piesa);
                            copiaTabla.stergePiesa(xI, yI);
                            if (!esteSah(culoare, copiaTabla))
                            {   //cout<<xI<<" "<<yI<<endl;
                                return false; // Există o mutare care scoate regele din șah
                            }
                        }
                    }
                }
            }
        }
    }
    return true; // Nu există nicio mutare care să scoată regele din șah
}
bool Logica_joc::verificaSahDupaMutare(int xInitial, int yInitial, int xFinal, int yFinal, string culoare, Tabla_de_sah tabla)
{
    if(!((tabla.getvaloareCelula(xInitial,yInitial)=='P' && xFinal==0) || (tabla.getvaloareCelula(xInitial,yInitial)=='p' && xFinal==7)))
    {

     // Salvează piesa de la poziția inițială
    char piesaInitiala = tabla.getvaloareCelula(xInitial, yInitial);
    cout<<"Intra";
    // Simulează mutarea piesei
    tabla.setValoareCelula(xFinal, yFinal, piesaInitiala);
    tabla.setValoareCelula(xInitial, yInitial, '*');

    // Verifică dacă regele este în șah după mutare
    bool inSah = esteSah(culoare, tabla);

    // Restaurează tabla la starea inițială
    tabla.setValoareCelula(xInitial, yInitial, piesaInitiala);
    tabla.setValoareCelula(xFinal, yFinal, '*');


    return inSah;
    }
    else
    return false;
}

