#include "Graphe.h"

Graph::Graph(std::string nomfichier)
{
    std::ifstream isf(nomfichier);
    int ordre =0, taille =0;

    isf >> ordre;
    for(int i=0;i<ordre;i++)
    {
        int id;
        isf >> id;
        total.push_back(new Sommet(id));
    }
    isf >> taille;
    for(int i=0;i<taille;i++)
    {
        int s1,s2,poids;
        isf >> s1;
        isf >> s2;
        isf >> poids;

        std::pair <Sommet*,int> nouveau{total[s2],poids};
        total[s1]->ajouter_voisin(nouveau);
    }
}

Graph::~Graph()
{
    for(auto s : total)
    {
        delete s;
    }
}

void Graph::afficher_graphe() const
{
    for(auto s : total)
    {
        std::cout << s->get_id() << ":" ;
        s->afficher();
        std::cout << std::endl;
    }
}

void Graph::chemin(int premier, int arrive)
{
    auto cmp = [] (std::pair <Sommet*,int> p1, std::pair <Sommet*,int> p2)
    {return p2.second<p1.second;};

    std::priority_queue <std::pair <Sommet*,int>, std::vector <std::pair <Sommet*,int>>, decltype(cmp) > file(cmp);

    file.push({total[premier],0});

    while(!file.empty() && !total[arrive]->get_marque())
    {
       Sommet* p=file.top().first;

       for(int i=0;i<(int)p->nb_voisin();i++)
       {
           if(!p->get_marque_voisin(i))
           {
               std::pair <Sommet*,int> tampon = p->get_voisin(i,p);
               tampon.second+=file.top().second;
               file.push(tampon);
           }
       }
        file.pop();
        p->marque();
    }
}

void Graph::affichage(int arrive) const
{
    int somme = 0;

    if(!total[arrive]->get_marque())
    {
        std::cout << "\nle point d'arrive n'est pas atteignable par ce point de depart. \n";
        return;
    }

    total[arrive]->afficher_result();

    std::cout << " : longueur ";

    somme=total[arrive]->afficher_poids();

    std::cout <<  "= " << somme;
}
