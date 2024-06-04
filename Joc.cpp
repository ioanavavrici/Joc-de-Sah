#include "Joc.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include "Tabla_de_sah.h"
#include "Logica_joc.h"
#include "Piese.h"

using namespace std;

Joc::Joc() : tabla()
{
    cout << "Jocul a inceput " << endl;
    int xF, xI, yI, yF;
    string culoare = "alb";
    Logica_joc logica;
    Tabla_de_sah tabla_noua;

    while (true)
    {
        // Verificăm dacă regele este în șah
        if (logica.esteSah(culoare, tabla))
        {
            // Verificăm dacă este șah mat
            if (logica.esteSahMat(culoare, tabla))
            {   system("cls"); // Curăță ecranul
                cout << "Sah-Mat!" << endl;
                cout << "Castigator: " << ((culoare == "alb") ? "negru" : "alb") << endl;
                char optiune;
                cout << "Doriti sa incepeti un nou joc? (y/n): ";
                cin >> optiune;

                if (optiune == 'y' || optiune == 'Y')
                {
                    // Reinițializăm tabla și culorile și începem un joc nou
                    tabla.reinitializeazaTabla();
                    culoare = "alb"; // sau "negru", în funcție de cine începe
                    continue; // Ne întoarcem la începutul buclei pentru a începe un nou joc
                }
                else if (optiune == 'n' || optiune == 'N')
                {
                    cout << "Jocul s-a incheiat. Multumim ca ai jucat!" << endl;
                    break; // Ieșim din buclă și din program
                }
                else
                {
                    cout << "Optiune invalida. Te rog sa introduci 'y' pentru da sau 'n' pentru nu." << endl;
                }
            }
            else
            {

                system("cls"); // Curăță ecranul
                cout << "Tabla de sah:" << endl;
                tabla.afiseazaTabla();
                cout << "Regele este in sah! Trebuie sa faci o mutare pentru a-l scoate din sah." << endl;
            }
        }
        else
        {
            system("cls"); // Curăță ecranul
            cout << "Tabla de sah:" << endl;
            tabla.afiseazaTabla();
        }

        cout << "Muta " << (culoare == "alb" ? "Alb (litere mari)" : "Negru (litere mici)") << endl;

        cout << "Muta piesa de pe pozitia: ";
        cin >> xI >> yI;
        while (xI > 8 || xI <= 0 || yI <= 0 || yI > 8 || tabla.getvaloareCelula(8 - xI, yI - 1) == '*' )
        {
            cout << "Nu ati introdus date valide" << endl << "Reintroduceti datele" << endl;
            cin >> xI >> yI;
        }

        cout << "Pe pozitia: ";
        cin >> xF >> yF;
        while (xF > 8 || xF <= 0 || yF <= 0 || yF > 8 ||(xF==xI && yF==yI))
        {
            cout << "Nu ati introdus date valide" << endl << "Reintroduceti datele" << endl;
            cin >> xF >> yF;
        }

        // Verificăm dacă mutarea este validă și nu lasă regele în șah
        while (!logica.verificaMiscare(tabla.getValoareCelula(8 - xI, yI - 1), 8 - xI, yI - 1, 8 - xF, yF - 1, culoare, tabla) || logica.verificaSahDupaMutare(8 - xI, yI - 1, 8 - xF, yF - 1, culoare, tabla))
        {
            cout << "Mutare incorecta sau regele ramane in sah" << endl;
           cout << "Muta " << (culoare == "alb" ? "Alb (litere mari)" : "Negru (litere mici)") << endl;

            cout << "Muta piesa de pe pozitia: ";
            cin >> xI >> yI;
            while (xI > 8 || xI <= 0 || yI <= 0 || yI > 8)
            {
                cout << "Nu ati introdus date valide" << endl << "Reintroduceti datele" << endl;
                cin >> xI >> yI;
            }
            cout << "Pe pozitia: ";
            cin >> xF >> yF;
            while (xF > 8 || xF <= 0 || yF <= 0 || yF > 8)
            {
                cout << "Nu ati introdus date valide" << endl << "Reintroduceti datele" << endl;
                cin >> xF >> yF;
            }
        }

        // Dacă am ieșit din buclă, înseamnă că mutarea este corectă
        tabla.setValoareCelula(8 - xF, yF - 1, tabla.getvaloareCelula(8 - xI, yI - 1));
        tabla.stergePiesa(8 - xI, yI - 1);

        // Schimbă culoarea pentru următoarea mutare
        culoare = (culoare == "alb") ? "negru" : "alb";
    }

}

Joc::~Joc()
{
    // Destructor
}
