#include "Arete.h"
#include "couleur.h"

Arete::Arete(int indice, int extrem1, int extrem2,Sommet* extremite1, Sommet* extremite2)
    :m_indice{indice}, m_extrem1{extrem1},m_extrem2{extrem2}
{
    m_sommet[0]=extremite1;
    m_sommet[1]=extremite2;

}

int Arete::getIndice ()const
{
    return m_indice;
}

int Arete::getExtrem1 ()const
{
    return m_extrem1;
}

int Arete::getExtrem2 ()const
{
    return m_extrem2;
}

void Arete::dessinerA(Svgfile& svgout)const
{
    Couleur noir{0,0,0};
    svgout.addLine(m_sommet[0]->getX()*100,m_sommet[0]->getY()*100,m_sommet[1]->getX()*100,m_sommet[1]->getY()*100,noir);
}

