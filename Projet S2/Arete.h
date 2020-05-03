#ifndef ARETE_H_INCLUDED
#define ARETE_H_INCLUDED

#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <map>
#include "Sommet.h"

//appeler la classe Graphe pour pouvoir l'utiliser dans le sous-programme "void dessinerA"
class Graphe;

class Arete
{
private :
    int m_indice; //indice des aretes
    double m_poids=0; //poids aretes
    Sommet* m_sommet[2]; //tableau de 2 sommets pour les extremités d'une arete

public :
    Arete (int indice,Sommet* extrem1, Sommet* extrem2); //constructeur
    ~Arete(); //destructeur

    //recupere les donnees
    int getIndice ()const;
    double getPoids()const;
    Sommet* getExtrem1 ()const;
    Sommet* getExtrem2 ()const;


    void setPoids(double new_poids); //attribuer des nouvelles donnees
    void dessinerA(Svgfile& svgout, Graphe* graphe); ////affichage aretes

    //recuperer les extremites d'une arrete
    Sommet* recupExtrem1(int indice);
    Sommet* recupExtrem2(int indice);
    //recuperer les poids des aretes adjacentes au sommet
    bool recup_poids_adj(double &poids,Sommet* prec,Sommet* suivant)const;

};

#endif // ARETE_H_INCLUDED
