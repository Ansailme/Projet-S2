#include <iostream>
#include "graphe.h"



int main()
{
    Graphe monGraphe{"graphe_etoile1.txt"};

    int a,choix;
    do
    {
        std::cout<<std::endl;
        std::cout<<std::endl<<"\t1) BFS " //à voir
                 <<std::endl<<"\t2) DFS " //à boire
                 <<std::endl<<"\t3) Recherche des composantes connexes et cycle/chaine eulerienne"
                 <<std::endl<<"\t4) Afficher Graphe et Pondération"
                 <<std::endl<<"\t5) Quitter"
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
        case 4 :
                monGraphe.afficher();
                monGraphe.lectureFichierP("ponderation_etoile1.txt");
                monGraphe.afficherPoids();
        }

    }while (choix!=5);


    return 0;
}

