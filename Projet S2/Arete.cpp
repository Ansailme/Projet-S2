#include "Arete.h"
#include "couleur.h"
#include "Graphe.h"

//constructeur
Arete::Arete(int indice,Sommet* extremite1, Sommet* extremite2)
    :m_indice{indice}
{
    m_sommet[0]=extremite1; //on attribue la 1ere case du tableau a la 1ere extremite (sommet1)
    m_sommet[1]=extremite2; //on attribue la 2eme case du tableau a la 2eme extremite (sommet2)

}

//destructeur
Arete:: ~Arete()
{
    m_sommet[0]->effacer_Adj(m_sommet[1]); //on dissocie les sommets d'une arete
    m_sommet[1]->effacer_Adj(m_sommet[0]); //par ex le sommet 1 ne sera plus relie au sommet 2 et inversement
}




//recuperer des donnees
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




//attribuer des nouvelles donnees
void Arete::setPoids(double new_poids)
{
    m_poids = new_poids;
}

//affichage aretes
void Arete::dessinerA(Svgfile& svgout, Graphe* graphe)
{
    if(graphe->Orientation() == true)
    {
        Couleur noir{0,0,0}; //declaration d'une couleur
    svgout.addLine(m_sommet[0]->getX()*100,m_sommet[0]->getY()*100,m_sommet[1]->getX()*100,m_sommet[1]->getY()*100,noir); //dessin arete
    svgout.addText(((m_sommet[0]->getX()*100)+m_sommet[1]->getX()*100)/2,
                   ((m_sommet[0]->getY()*100)+m_sommet[1]->getY()*100)/2, getPoids(), noir); //dessin poids sur milieu d'arete

    }
    else
    {
        Couleur noir{0,0,0}; //declaration d'une couleur
        Couleur test{255,150,50};
    svgout.addLine(m_sommet[0]->getX()*100,m_sommet[0]->getY()*100,m_sommet[1]->getX()*100,m_sommet[1]->getY()*100,test); //dessin arete
    svgout.addText(((m_sommet[0]->getX()*100)+m_sommet[1]->getX()*100)/2,
                   ((m_sommet[0]->getY()*100)+m_sommet[1]->getY()*100)/2, getPoids(), noir); //dessin poids sur milieu d'arete
    }
}



//recuperer les extremites d'une arrete
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

//recuperer les poids des aretes adjacentes au sommet
bool Arete::recup_poids_adj(double &poids,Sommet* prec, Sommet* suivant)const
{
    if(((m_sommet[0] == prec) && (suivant == m_sommet[1])) || (((prec == m_sommet[1])) && suivant == m_sommet[0]))
    {
        poids = m_poids;
        return true;
    }

    return false;
}

