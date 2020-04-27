#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED

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
    int m_indice2;
    int m_poids;
    int m_extrem1;
    int m_extrem2;

public :
    Arete (int indice, int indice2, int poids,int m_extrem1, int m_extrem2);
    int getIndice ()const;
    int getIndice2()const;
    int getPoids () const;
    int getExtrem1 ()const;
    int getExtrem2 ()const;

};

#endif // SOMMET_H_INCLUDED
