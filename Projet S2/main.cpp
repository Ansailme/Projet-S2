#include <iostream>
#include "graphe.h"



int main()
{
    Graphe monGraphe{"graphe_etoile1.txt"};
    monGraphe.afficher();

/*
    int a,choix;
    monGraphe.afficher();
    do
    {
        std::cout<<std::endl;
        std::cout<<std::endl<<"\t1) BFS"
                 <<std::endl<<"\t2) DFS"
                 <<std::endl<<"\t3) Recherche des composantes connexes et cycle/chaine eulerienne"
                 <<std::endl<<"\t4) Quitter"
                 <<std::endl<<"Faites votre choix : ";
        std::cin>>choix;
        switch(choix)
        {
        case 1 :
            std::cout<<std::endl<<"Premier ? ";
            std::cin>>a;
            monGraphe.BFS(a);
            break;
        case 2:
            std::cout<<std::endl<<"Premier ? ";
            std::cin>>a;
            monGraphe.DFS(a);
            break;
        case 3 :
            monGraphe.recherchecompoConnexes();
            break;
        }

    }while (choix!=4);
*/


    return 0;
}

