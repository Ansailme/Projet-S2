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
private:
    int m_id;
    std::vector <std::pair <Sommet*,int>> m_voisin;
    Sommet* m_precedent;
    int m_poids_precedent;
    bool m_marque;

public:
    Sommet(const int id);
    ~Sommet()=default;
    int get_id() const;
    //const std::vector <std::pair <Sommet*,int>> &get_voisins() const;
    void ajouter_voisin(std::pair <Sommet*,int> cote);
    void afficher() const;
    void afficher_result() const;
    int afficher_poids() const;
    std::pair <Sommet*,int> get_voisin(int i, Sommet* p);
    bool get_marque() const;
    bool get_marque_voisin(int i) const;
    size_t nb_voisin() const;
    void marque();

};
#endif // SOMMET_H_INCLUDED
