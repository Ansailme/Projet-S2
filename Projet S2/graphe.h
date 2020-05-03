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
    Graphe (std::string fichier); //Constructeur
    ~Graphe(); //destructeur

    int lectureFichierP(); //lecture des fichiers
    bool Orientation(); //verification de l'orientation du graphe
    void afficherG()const; //affichage du fichier topologique
    void afficherPoids()const; //affichage du fichier de pondération
    void affichage(int arrive, double poids) const; //affichage du parcours du plus court chemin (Dijkstra)
    void dessinerGraphe(); //dessiner le graphe dans svgfile

    void c_degre(); //calcul centralité de degre
    void c_propre(); //calcul de centralite vecteur propre
    double c_prox(int premier, int arrive); //calcul poidsTot : dijkstra
    void c_intermediarite();
    void verification();

    void calcul_cp (int i_debut, int i_fin); //calcul centralité promixité à la main
    void calcul_cp_auto(); //calcul centralité promixité automatisé pour tout sommet
    void calculDiff_indice (int f1, int f2); //calcul de la difference des indices entre 2 fichiers

    void BFS(int premier, int arrive); //calcul du BFS
    void DFS(int premier); //calcul DFS
    void recuDFS(std::map<int, int>& i_preds,Sommet* s); //calcul du chemin pour le DFS
    void recherchecompoConnexes(); //recherche des composantes connexes
    void connexite(); //k-connexité
    Sommet* recupSommet(int indice); //recuperer l'indice du sommet

    void sauvegarde(int s); //sauvegarde de tous les indices dans fichier
    void supp_arete(); //Supprimer une ou plusieurs aretes

};



#endif // GRAPHE_H_INCLUDED



//total[i]->get_voisin()[j].first/second
