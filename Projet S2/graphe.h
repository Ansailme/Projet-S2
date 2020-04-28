#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED

#include "sommet.h"
#include "Arete.h"

class Graphe
{
private :
    int m_orient; // 0 si non-oriente // 1 si oriente
    std::vector <Sommet* > m_sommets;
    std::vector <Arete* > m_aretes;

public :
    Graphe (std::string fichier);
    ~Graphe();
    void lectureFichierP(std::string fichier2);
    void afficher()const;
    void afficherPoids()const;
    void dessinerGraphe() const;
    void verification();
    void BFS(int premier);
    Sommet* recupSommet(int indice);
    void DFS(int premier);
    void recuDFS(std::map<int, int>& i_preds,Sommet* s);
    void recherchecompoConnexes();
};



#endif // GRAPHE_H_INCLUDED



//total[i]->get_voisin()[j].first/second
