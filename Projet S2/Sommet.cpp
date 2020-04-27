#include "Sommet.h"

Sommet::Sommet(const int id)
:m_id{id},m_precedent{nullptr}, m_poids_precedent{-1},m_marque{false}
{
}

int Sommet::get_id() const
{
    return m_id;
}

/*
const std::vector <std::pair <Sommet*,int>> & Sommet::get_voisins() const
{
    return &m_voisin;
}
*/

void Sommet::ajouter_voisin(std::pair <Sommet*,int> cote)
{
    m_voisin.push_back(cote);
}

void Sommet::afficher() const
{
    for(auto s : m_voisin)
    {
        std::cout << s.first->get_id() << " " ;
    }
}

void Sommet::afficher_result() const
{
    std::cout << m_id ;
    if(m_precedent!=nullptr)
    {
        std::cout << "<--";
        m_precedent->afficher_result();
    }
}

int Sommet::afficher_poids() const
{

    if(m_precedent!=nullptr)
    {
        std::cout << m_poids_precedent ;
        std::cout << "+";
        return m_poids_precedent+m_precedent->afficher_poids();
    }
    return 0;
}

std::pair <Sommet*,int> Sommet::get_voisin(int i, Sommet* p)
{
    if( m_voisin[i].first->m_poids_precedent<0 ||  m_voisin[i].first->m_poids_precedent>m_voisin[i].second)
    {
        m_voisin[i].first->m_precedent=p;
        m_voisin[i].first->m_poids_precedent=m_voisin[i].second;
    }

    return m_voisin[i];
}

bool Sommet::get_marque() const
{
    return m_marque;
}

bool Sommet::get_marque_voisin(int i) const
{
    return m_voisin[i].first->m_marque;
}

size_t Sommet::nb_voisin() const
{
    return m_voisin.size();
}

void Sommet::marque()
{
    m_marque=true;
}

