#include "sommet.h"

Sommet::Sommet (int num)
    :m_num{num},m_couleur {0}
{}

void Sommet::remplir(Sommet* adjacent)
{
     m_adjacents.push_back(adjacent);

}

int Sommet::getNum ()const
{
    return m_num;
}

void Sommet::afficher ()const
{
    std::cout<<std::endl<<"\t sommet "
                        <<m_num<<" : ";
    for (auto it : m_adjacents)
        std::cout<<it->getNum()<<" ";
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
