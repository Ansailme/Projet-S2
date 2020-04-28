#ifndef ARETE_H_INCLUDED
#define ARETE_H_INCLUDED

#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <map>
#include "Sommet.h"

class Arete
{
private :
    int m_indice;
    int m_extrem1;
    int m_extrem2;
    Sommet* m_sommet[2];

public :
    Arete (int indice,int m_extrem1, int m_extrem2);
    int getIndice ()const;
    int getExtrem1 ()const;
    int getExtrem2 ()const;
    void dessinerA(Svgfile& svgout)const;

    int poids;

};

#endif // ARETE_H_INCLUDED
