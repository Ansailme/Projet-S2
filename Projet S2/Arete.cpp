#include "Arete.h"
#include "couleur.h"

Arete::Arete(int indice,Sommet* extremite1, Sommet* extremite2)
    :m_indice{indice}
{
    m_sommet[0]=extremite1;
    m_sommet[1]=extremite2;

}

Arete:: ~Arete()
{
    m_sommet[0]->effacer_Adj(m_sommet[1]);
    m_sommet[1]->effacer_Adj(m_sommet[0]);
}





int Arete::getIndice ()const
{
    return m_indice;
}

double Arete::getPoids()const
{
    return m_poids;
}

Sommet* Arete::getExtrem1 ()const
{
    return m_sommet[0];
}

Sommet* Arete::getExtrem2 ()const
{
    return m_sommet[1];
}





void Arete::setPoids(double new_poids)
{
    m_poids = new_poids;
}

void Arete::dessinerA(Svgfile& svgout)const
{
    Couleur noir{0,0,0}; //declaration d'une couleur
    svgout.addLine(m_sommet[0]->getX()*100,m_sommet[0]->getY()*100,m_sommet[1]->getX()*100,m_sommet[1]->getY()*100,noir); //dessin arete
    svgout.addText(((m_sommet[0]->getX()*100)+m_sommet[1]->getX()*100)/2,
                   ((m_sommet[0]->getY()*100)+m_sommet[1]->getY()*100)/2, getPoids(), noir); //dessin poids sur milieu d'arete

}




Sommet* Arete::recupExtrem1(int indice)
{
        if ((getIndice())==indice)
        {
            return m_sommet[0];
        }
}

Sommet* Arete::recupExtrem2(int indice)
{
        if ((getIndice())==indice)
        {
            return m_sommet[1];
        }
}

bool Arete::recup_poids_adj(double &poids,Sommet* prec, Sommet* suivant)const
{
    if(((m_sommet[0] == prec) && (suivant == m_sommet[1])) || (((prec == m_sommet[1])) && suivant == m_sommet[0]))
    {
        poids = m_poids;
        return true;
    }

    return false;
}

