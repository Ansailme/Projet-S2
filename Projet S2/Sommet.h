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

//appeler la classe Arete pour pouvoir l'utiliser dans le sous-programme "get_voisin"
class Arete;

class Sommet
{
private :
    int m_num; //indice du sommet
    int m_x,m_y; //coordonnees
    int m_couleur; //0 -> Blanc //1->Gris //2->Noir
    int m_marquage; //savoir s'il est marque
    int m_poids_precedent; //valeur "tampon" pour retenir le poids precedent

    bool m_marque; //

    std::string m_lettre; //nom sommet
    std::vector<Sommet*> m_adjacents; //vecteur de sommets adjacents
    std::vector <std::pair <Sommet*,int>> m_voisin; //vecteur pour associer les valeurs de sommets adjacents au poids

    Sommet* m_precedent; //pointeur de tous les sommets precedents

public :
    Sommet (int num, std::string lettre, int x, int y); //constructeur
    ~Sommet(); //destructeur

    //recuperer donnees
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

    //attribuer de nouvelles valeurs
    void setCouleur(int nv);
    void setAdjacents(int i);
    // void setMarquage(int nv);

    //affichages
    void dessinerS(Svgfile& svgout) const; //affichage des sommets
    void afficher_num()const; //affichage de l'indice des sommets
    void afficher_result() const; //affichage des lettres des sommets pour calculer le plus court chemin
    int afficher_poids() const; //affichage du poids pour calculer le plus court chemin

    void init_marque(); //initialiser la couleur des sommets en blanc
    void marque(); //verifier le booleen
    bool estAdjacentA(int i); //verifier les adjacences a un sommet
    //bool estDegreImpair();
    size_t nb_voisin() const; //recuperer le nombre de voisins total a un sommet
    void ajouter_voisin(std::pair <Sommet*,int> cote); //ajouter un nouveau voisin
    void remplir(Sommet* adjacent); //ajouter un nouveau sommet
    void connexite(int arriver, int& k); //parcours de differents chemins pour la k-connexite
    void effacer_Adj(Sommet* a); //effacer l'adjacence entre 2 sommets pour les dissocier
    void reinitialiserCouleur(); //remettre la couleur a blanc pour qu'un sommet ne soit plus marqué

};

#endif // SOMMET_H_INCLUDED
