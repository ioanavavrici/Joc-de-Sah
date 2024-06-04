#ifndef PIESE_H
#define PIESE_H
#include <iostream>
#include <string>


using namespace std;

class Piese
{
    private:
        char tip;
        string culoare;
    public:
        Piese(char tip,string culoare);
        char getTip();
        string getCuloare();
        virtual ~Piese();

    protected:


};

#endif // PIESE_H
