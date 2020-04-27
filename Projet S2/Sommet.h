#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED

#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <map>

class Sommet
{
private :
    int m_num;
    int m_couleur; //0 -> B //1->G //2->N
    std::vector<Sommet*> m_adjacents;

public :
    Sommet (int num);
    int getNum ()const;
    void afficher ()const;
    void remplir(Sommet* adjacent);
    void reinitialiserCouleur();
    void setCouleur(int nv);
    void setAdjacents(int i);
    int getCouleur()const;
    bool estAdjacentA(int i);
    bool estDegreImpair();


};

#endif // SOMMET_H_INCLUDED
