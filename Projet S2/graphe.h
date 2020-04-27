#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED

#include "Sommet.h"


class Graph
{
private:
    std::vector <Sommet*> total;

public:
    Graph(std::string nomfichier);
    ~Graph();
    void chemin(int premier, int arrive);
    void affichage(int arrive) const;
    void afficher_graphe() const;


};

#endif // GRAPHE_H_INCLUDED



//total[i]->get_voisin()[j].first/second
