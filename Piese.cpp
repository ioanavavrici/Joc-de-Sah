#include "Piese.h"
#include <iostream>
#include <string>


using namespace std;
Piese::Piese(char tip=' ',string culoare="")
{
    this ->tip=tip;
    this ->culoare=culoare;
}

char Piese::getTip()
{
    return tip;
}


string Piese::getCuloare()
{

    return culoare;

}
Piese::~Piese()
{
    //dtor
}
