#include "sommet.h"
#include "svgfile.h"
#include "couleur.h"
#include "Arete.h"

//constructeur
Sommet::Sommet (int num, std::string lettre, int x, int y)
    :m_num{num},m_couleur {0}, m_lettre{lettre},m_x{x},m_y{y}
{}

//destructeur
Sommet::~Sommet()
{}



//recuperer les donnees
int Sommet::getX() const
{
    return m_x;
}

int Sommet::getY() const
{
    return m_y;
}

int Sommet::getNum ()const
{
    return m_num;
}

std::string Sommet::getLettre() const
{
    return m_lettre;
}

size_t Sommet::getNbAdj () const
{
    return m_adjacents.size();
}

int Sommet::getCouleur()const
{
    return m_couleur;
}

bool Sommet::get_marque() const
{
    return m_marque;
}

bool Sommet::get_marque_voisin(int i) const
{
    return m_voisin[i].first->m_marque;
}

std::pair <Sommet*,double> Sommet::get_voisin(Sommet* p, double poids_total,std::vector<Arete*> m_arete)
{
    double poids=0;

    m_precedent = p;

    for(auto a : m_arete)
    {
        if(a->recup_poids_adj(poids,p,this))
        {
            break;
        }
    }

    /*
    if( m_voisin[i].first->m_poids_precedent<0 ||  m_voisin[i].first->m_poids_precedent>m_voisin[i].second)
    {
        m_voisin[i].first->m_precedent=p;
        m_voisin[i].first->m_poids_precedent=m_voisin[i].second;
    }
    */
    return std::pair <Sommet*,double> {this, poids_total+poids};
    //return m_voisin[i];
}





//attribuer des nouvelles valeurs
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





//affichage des sommets
void Sommet::dessinerS(Svgfile& svgout) const
{
    Couleur noir{0,0,0};
    Couleur deg{(85-m_adjacents.size())*50, (200-m_adjacents.size())*100,(50-m_adjacents.size())*60};
    Couleur rouge{255,0,0};

    svgout.addDisk(m_x*100,m_y*100,15,deg);
    svgout.addText(m_x*100-30,m_y*100-20,m_lettre,noir);
    svgout.addDisk(m_x*100,m_y*100,2, rouge);
    //svgout.addTriangle(m_x*100-50,m_y*100+50,m_x*100-50,m_y*100+50,m_x*100,m_y*100, noir); //tentative triangle de fleche
    //svgout.addTriangle(m_x*100-5,m_y*100+5,m_x*100+5,m_y*100+5,m_x*100,m_y*100,noir,1, noir);
}

//affichage de l'indice des sommets
void Sommet::afficher_num()const
{
    std::cout<<std::endl<<"\t sommet "
             <<m_num<<" : ";
    for (auto it : m_adjacents)
        std::cout<<it->getNum()<<" ";
}

//affichage des lettres des sommets pour calculer le plus court chemin
void Sommet::afficher_result() const
{
    std::cout << m_lettre ;
    if(m_precedent!=nullptr)
    {
        std::cout << "<--";
        m_precedent->afficher_result();
    }
}

//affichage du poids pour calculer le plus court chemin
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





//initialiser la couleur des sommets en blanc
void Sommet::init_marque()
{
    m_marque = 0;
    m_precedent = nullptr;

}

//verifier le booleen
void Sommet::marque()
{
    m_marque=true;
}

//verifier les adjacences a un sommet
bool Sommet::estAdjacentA(int i)
{
    bool adjacent=false;
    for (auto it : m_adjacents)
        if (it->getNum()==i)
            adjacent=true;
    return adjacent;
}

/*
bool Sommet::estDegreImpair()
{
    bool temp;

    if(m_adjacents.size()%2==0)
        temp=false;
    else
        temp=true;

    return temp;
}*/

//recuperer le nombre de voisins total a un sommet
size_t Sommet::nb_voisin() const
{
    return m_voisin.size();
}

//ajouter un nouveau voisin
void Sommet::ajouter_voisin(std::pair <Sommet*,int> cote)
{
    m_voisin.push_back(cote);
}

//ajouter un nouveau sommet
void Sommet::remplir(Sommet* adjacent)
{
    m_adjacents.push_back(adjacent);
}

//parcours de differents chemins pour la k-connexite
void Sommet::connexite(int arriver, int& k)
{
    if(getCouleur() == 2)
    {
        return;
    }

    if(arriver == getNum())
    {
        k++;
        return;
    }

    m_couleur = 2;

    for(int i=0;i<m_adjacents.size();++i)
    {
        m_adjacents[i]->connexite(arriver,k);
    }
}

//effacer l'adjacence entre 2 sommets pour les dissocier
void Sommet::effacer_Adj(Sommet* a)
{
    for (int i=0; i<m_adjacents.size();++i)
    {
        if ((m_adjacents[i])== a)
        {
            m_adjacents.erase(m_adjacents.begin()+i);
        }
    }
}

//remettre la couleur a blanc pour qu'un sommet ne soit plus marqué
void Sommet::reinitialiserCouleur()
{
    m_couleur=0;
}

