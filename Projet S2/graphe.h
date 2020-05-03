#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED

#include "Arete.h"


class Graphe
{
private :
    int m_orient; // 0 si non-oriente // 1 si oriente
    int m_ordre; //nb de sommets
    int m_taille; //nb d'aretes

    std::vector <double> deg; //indice de degre de sommet
    std::vector <double> cvp; //indice de vecteur propre
    std::vector <double > cp; //indice de proximite
    std::vector <double > cpn; //indice de proximite normalise
    std::vector <double> cint; //indice d'intermediarite
    std::vector <double> cintn; //indice d'intermediarite normalisé
    std::vector <Sommet* > m_sommets; //vecteur de sommets
    std::vector <Arete* > m_aretes; //vecteur d'aretes


public :
    Graphe (std::string fichier);
    ~Graphe();

    int lectureFichierP();
    bool Orientation();
    void afficherG()const;
    void afficherPoids()const;
    void affichage(int arrive, double poids) const; //affichage Didjkstra
    void dessinerGraphe();

    void c_degre(); //calcul centralité de degre
    void c_propre(); //calcul de centralite vecteur propre
    double c_prox(int premier, int arrive); //calcul poidsTot : dijkstra
    void c_intermediarite();
    void verification();
    void calcul_cp (int i_debut, int i_fin); //calcul centralité promixité à la main
    void calcul_cp_auto(); //calcul centralité promixité automatisé pour tout sommet
    void calculDiff_indice (int f1, int f2);

    void BFS(int premier);
    void DFS(int premier);
    void recuDFS(std::map<int, int>& i_preds,Sommet* s);
    void recherchecompoConnexes();
    void connexite();
    Sommet* recupSommet(int indice);

    void sauvegarde(int s); //sauvegarde de tous les indices dans fichier
    void supp_arete();

};



#endif // GRAPHE_H_INCLUDED



//total[i]->get_voisin()[j].first/second
