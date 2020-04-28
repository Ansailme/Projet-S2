#include <iostream>
#include "graphe.h"
#include "svgfile.h"
#include "couleur.h"

int main()
{
    Graphe monGraphe{"graphe_etoile1.txt"};

    int a,choix;
    do
    {
        std::cout<<std::endl;
       /* std::cout<<std::endl<<"\t1) BFS " //à voir
                 <<std::endl<<"\t2) DFS " //à boire
                 <<std::endl<<"\t3) Recherche des composantes connexes et cycle/chaine eulerienne"*/
          std::cout<<"\t4) Afficher Graphe \n"
                   <<"\t5) Afficher Ponderation \n"
                   <<"\t6) svgtest\n"
                   <<"\t7) Quitter\n"
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
            monGraphe.c_degre();
            /*std::cout<<std::endl<<"Premier ? ";
            std::cin>>a;
            monGraphe.DFS(a);*/
            break;
        case 3 :
                monGraphe.recherchecompoConnexes();
            break;
        case 4 :
                monGraphe.afficher();
                break;

        case 5 :
                monGraphe.verification();
                monGraphe.lectureFichierP("ponderation_etoile1.txt");
                monGraphe.afficherPoids();
                break;
        case 6 :
                //svgTest();
                monGraphe.dessinerGraphe ();
                break;

        }

    }while (choix!=7);


    return 0;
}

