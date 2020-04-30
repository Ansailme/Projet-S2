#include "sommet.h"
#include "svgfile.h"
#include "couleur.h"

Sommet::Sommet (int num, std::string lettre, int x, int y)
    :m_num{num},m_couleur {0}, m_lettre{lettre},m_x{x},m_y{y}
{}


void Sommet::remplir(Sommet* adjacent)
{
     m_adjacents.push_back(adjacent);
}

int Sommet::getNum ()const
{
    return m_num;
}

std::string Sommet::getLettre() const
{
    return m_lettre;
}

int Sommet::getX() const
{
    return m_x;
}

int Sommet::getY() const
{
    return m_y;
}


void Sommet::afficher_num()const
{
    std::cout<<std::endl<<"\t sommet "
                        <<m_num<<" : ";
    for (auto it : m_adjacents)
        std::cout<<it->getNum()<<" ";
}


void Sommet::dessinerS(Svgfile& svgout) const
{
    Couleur noir{0,0,0};
    Couleur deg{(85-m_adjacents.size())*50, (200-m_adjacents.size())*100,(50-m_adjacents.size())*60};

    svgout.addDisk(m_x*100,m_y*100,15,deg);
    svgout.addText(m_x*100-30,m_y*100-20,m_lettre,noir);
}


void Sommet::reinitialiserCouleur()
{
    m_couleur=0;
}

void Sommet::setCouleur(int nv)
{
    m_couleur=nv;
}

bool Sommet::estAdjacentA(int i)
{
    bool adjacent=false;
    for (auto it : m_adjacents)
        if (it->getNum()==i)
            adjacent=true;
    return adjacent;
}

void Sommet::setAdjacents(int i)
{
    for (auto it : m_adjacents)
    {
        if (i==1)//si gris
            if (it->getCouleur()!=2)//verifie que le sommet a pas déjà été étudier
                it->setCouleur(i); //met en gris
    }
}

int Sommet::getCouleur()const
{
    return m_couleur;
}


bool Sommet::estDegreImpair()
{
    bool temp;

    if(m_adjacents.size()%2==0)
        temp=false;
    else
        temp=true;

    return temp;
}


/*--------------------------------------------------------*/

void Sommet::afficher_result() const
{
    std::cout << m_num ;
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

void Sommet::ajouter_voisin(std::pair <Sommet*,int> cote)
{
    m_voisin.push_back(cote);
}
