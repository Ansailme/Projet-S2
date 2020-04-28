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
    std::string m_lettre;
    int m_x,m_y;
    int m_num;
    int m_couleur; //0 -> B //1->G //2->N
    std::vector<Sommet*> m_adjacents;

public :
    Sommet (int num, std::string lettre, int x, int y);
    std::string getLettre() const;
    int getX() const;
    int getY() const;
    int getNum ()const;
    void afficher_num()const;
    void dessinerS(int x,int y) const;
    void remplir(Sommet* adjacent);
    void reinitialiserCouleur();
    void setCouleur(int nv);
    void setAdjacents(int i);
    int getCouleur()const;
    bool estAdjacentA(int i);
    bool estDegreImpair();
};

#endif // SOMMET_H_INCLUDED
