#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED

#include "Arete.h"


class Graphe
{
private :
    int m_orient; // 0 si non-oriente // 1 si oriente
    int m_ordre;
    int m_taille;

    std::vector <Sommet* > m_sommets;
    std::vector <Sommet* > m_sommetD;
    std::vector <Arete* > m_aretes;
    std::vector <double> deg;
    std::vector <double> cvp;
    std::vector <int> cp;

public :
    Graphe (std::string fichier);
    ~Graphe();
    void lectureFichierP();
    void afficherG()const;
    void afficherPoids()const;
    void dessinerGraphe()const;
    void verification();
    void c_degre();
    void c_propre();
    void sauvegarde();

    void BFS(int premier);
    Sommet* recupSommet(int indice);
    void DFS(int premier);
    void recuDFS(std::map<int, int>& i_preds,Sommet* s);
    void recherchecompoConnexes();
    void recherchePlusCourtChemin(int i_debut,int i_fin);

    /*-----------------*/

    double c_prox(int premier, int arrive);
    void affichage(int arrive, double poids) const;
    void lienAS();
    void lectureFichierAS();

};



#endif // GRAPHE_H_INCLUDED



//total[i]->get_voisin()[j].first/second
