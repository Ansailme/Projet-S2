#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED

#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <map>
#include "svgfile.h"


class Sommet
{
private :
    std::string m_lettre;
    int m_x,m_y;
    int m_num;
    int m_couleur; //0 -> B //1->G //2->N
    int m_marquage;
    std::vector<Sommet*> m_adjacents;

    /*-------------------------*/

    std::vector <std::pair <Sommet*,int>> m_voisin;
    Sommet* m_precedent;
    int m_poids_precedent;
    bool m_marque;

public :
    Sommet (int num, std::string lettre, int x, int y);
    std::string getLettre() const;
    int getX() const;
    int getY() const;
    int getNum ()const;
    void afficher_num()const;
    void dessinerS(Svgfile& svgout) const;
    void remplir(Sommet* adjacent);
    void reinitialiserCouleur();
    void setCouleur(int nv);
    void setAdjacents(int i);
    int getCouleur()const;
    bool estAdjacentA(int i);
    bool estDegreImpair();
    void setMarquage(int nv);
    int getDist (int i);
    int getMarquage()const;

    /*----------------------------*/

    void afficher_result() const;
    int afficher_poids() const;
    std::pair <Sommet*,int> get_voisin(int i, Sommet* p);
    bool get_marque() const;
    bool get_marque_voisin(int i) const;
    size_t nb_voisin() const;
    void marque();

};

#endif // SOMMET_H_INCLUDED
