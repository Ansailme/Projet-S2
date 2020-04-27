#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED

#include "sommet.h"

class Graphe
{
private :
    std::vector <Sommet*> m_sommets;

public :
    Graphe (std::string fichier);
    void afficher ()const;
    void recherchePlusCourtChemin(int i_debut, int i_fin);
    void affichageLongeur(int i_fin, int temp);
};


#endif // GRAPHE_H_INCLUDED
