#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED

#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <map>
#include "svgfile.h"
#include <iomanip>

class Arete;

class Sommet
{
private :
    int m_num;
    int m_x,m_y;
    int m_couleur; //0 -> B //1->G //2->N
    int m_marquage;
    int m_poids_precedent;

    bool m_marque;

    std::string m_lettre; //denomination sommet
    std::vector<Sommet*> m_adjacents;
    std::vector <std::pair <Sommet*,int>> m_voisin;

    Sommet* m_precedent;

public :
    Sommet (int num, std::string lettre, int x, int y);
    ~Sommet();

    int getX() const;
    int getY() const;
    int getNum ()const;
    std::string getLettre() const;
    size_t getNbAdj ()const;
    int getCouleur()const;
    //int getDist (int i);
    //int getMarquage()const;
    bool get_marque() const;
    bool get_marque_voisin(int i) const;
    std::pair <Sommet*,double> get_voisin(Sommet* p,double poids_total,std::vector<Arete*> m_arete);

    void setCouleur(int nv);
    void setAdjacents(int i);
   // void setMarquage(int nv);

    void dessinerS(Svgfile& svgout) const;
    void afficher_num()const;
    void afficher_result() const;
    int afficher_poids() const;

    void init_marque();
    void marque();
    bool estAdjacentA(int i);
    bool estDegreImpair();
    size_t nb_voisin() const;
    void ajouter_voisin(std::pair <Sommet*,int> cote);
    void remplir(Sommet* adjacent);
    void connexite(int arriver, int& k);
    void effacer_Adj(Sommet* a);
    void reinitialiserCouleur();

};

#endif // SOMMET_H_INCLUDED
