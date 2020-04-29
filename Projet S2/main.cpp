#include <iostream>
#include "graphe.h"
#include "svgfile.h"
#include "couleur.h"

int main()
{
    Graphe monGraphe{"graphe_etoile3.txt"};
    int a,choix=0;

    do
    {
        std::cout<<std::endl;
       /* std::cout<<std::endl<<"\t1) BFS " //à voir
                 <<std::endl<<"\t2) DFS " //à boire
                 <<std::endl<<"\t3) Recherche des composantes connexes "*/
          std::cout<<"\t\t MENU PRINCIPAL\n"
                    <<"\t2) Degre sommet \n"
                    <<"\t3) Decentralite de vecteur propre \n"
                    <<"\t4) Afficher Graphe \n"
                    <<"\t5) Afficher Ponderation \n"
                    <<"\t6) svgtest\n"
                    <<"\t7) sauvegarde\n"
                    <<"\t8) Quitter\n"
                    << std::endl;

                   std::cout<<"Faites votre choix : ";
                   std::cin >> choix;
                   std::cout<<std::endl;


        switch(choix)
        {
        case 1 :
            std::cout<<std::endl<<"Premier ? ";
            std::cin>>a;
            monGraphe.BFS(a);
            break;
        case 2:
            monGraphe.c_degre();
            break;
        case 3 :
            //monGraphe.c_propre();
            break;
        case 4 :
                monGraphe.afficher();
                break;

        case 5 :
                //monGraphe.verification();
                monGraphe.lectureFichierP("ponderation_etoile1.txt");
                monGraphe.afficherPoids();
                break;
        case 6 :
                //svgTest();
                monGraphe.dessinerGraphe ();
                break;
        case 7 :
            monGraphe.sauvegarde("sauvegarde.txt");
            std::cout<<"\tsauvegarde operationnelle chef !"<<std::endl;
            break;

        }

    }while (choix!=8);


    return 0;
}

