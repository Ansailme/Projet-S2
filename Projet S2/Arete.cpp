#include "Arete.h"
#include "couleur.h"

Arete::Arete(int indice,Sommet* extremite1, Sommet* extremite2)
    :m_indice{indice}
{
    m_sommet[0]=extremite1;
    m_sommet[1]=extremite2;

}

int Arete::getIndice ()const
{
    return m_indice;
}

Sommet* Arete::getExtrem1 ()const
{
    return m_sommet[0];
}

Sommet* Arete::getExtrem2 ()const
{
    return m_sommet[1];
}

double Arete::getPoids()const
{
    return m_poids;
}

void Arete::setPoids(double new_poids)
{
    m_poids = new_poids;
}

void Arete::dessinerA(Svgfile& svgout)const
{
    Couleur noir{0,0,0};

    svgout.addLine(m_sommet[0]->getX()*100,m_sommet[0]->getY()*100,m_sommet[1]->getX()*100,m_sommet[1]->getY()*100,noir);
    svgout.addText(((m_sommet[0]->getX()*100)+m_sommet[1]->getX()*100)/2,((m_sommet[0]->getY()*100)+m_sommet[1]->getY()*100)/2, getPoids(), noir);

}

