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
    Sommet* m_sommet[2]; //tableau de 2 sommets extremités d'1 arete
    double m_poids; //poids arete

public :
    Arete (int indice,Sommet* extrem1, Sommet* extrem2);
    int getIndice ()const;
    Sommet* getExtrem1 ()const;
    Sommet* getExtrem2 ()const;
    double getPoids()const;

    void setPoids(double new_poids);
    bool recup_poids_adj(double &poids,Sommet* prec,Sommet* suivant)const;

    void dessinerA(Svgfile& svgout)const;


};

#endif // ARETE_H_INCLUDED
