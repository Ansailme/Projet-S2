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
    double m_poids=0; //poids arete
    Sommet* m_sommet[2]; //tableau de 2 sommets extremités d'1 arete

public :
    Arete (int indice,Sommet* extrem1, Sommet* extrem2);
    ~Arete();

    int getIndice ()const;
    double getPoids()const;
    Sommet* getExtrem1 ()const;
    Sommet* getExtrem2 ()const;

    void setPoids(double new_poids);
    void dessinerA(Svgfile& svgout)const;

    Sommet* recupExtrem1(int indice);
    Sommet* recupExtrem2(int indice);
    bool recup_poids_adj(double &poids,Sommet* prec,Sommet* suivant)const;

};

#endif // ARETE_H_INCLUDED
