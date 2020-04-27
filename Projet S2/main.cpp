#include "graphe.h"

int main()
{
    Graphe a("data.txt");
    int i_debut,i_fin;
    a.afficher();
    int stop;
    do
    {
        std::cout<<std::endl<<"Pour la recherche du plus court chemin :"
                 <<std::endl<<"Choisir le sommet de depart : ";
        std::cin>>i_debut;
        std::cout<<std::endl<<"Choisir le sommet d'arrivee : ";
        std::cin>>i_fin;
        a.recherchePlusCourtChemin(i_debut,i_fin);
        std::cout<<std::endl<<"Pour quitter tapez 1 sinon taper 0"<<std::endl;
        std::cin>>stop;
    }while (stop!=1);

    return 0;
}


