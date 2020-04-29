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
    Couleur rouge {255,0,0};
    Couleur vert {0,255,0};
    Couleur bleu {0,0,255};
    Couleur jaune{255,200,0};
    Couleur deg{(m_adjacents.size())*50, 255-m_adjacents.size()*50,0};

    svgout.addDisk(m_x*100,m_y*100,5,deg);
    svgout.addText(m_x*100-5,m_y*100-5,m_lettre,noir);
}


void Sommet::reinitialiserCouleur()
{
    m_couleur=0;
}

void Sommet::setCouleur(int nv)
{
    m_couleur=nv;
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


bool Sommet::estAdjacentA(int i)
{
    bool adjacent=false;
    for (auto it : m_adjacents)
        if (it->getNum()==i)
            adjacent=true;
    return adjacent;
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
