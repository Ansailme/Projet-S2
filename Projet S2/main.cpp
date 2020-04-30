#include <iostream>
#include "graphe.h"
#include "svgfile.h"
#include "couleur.h"

int main()
{
    std::cout<<"\t\t MENU PRINCIPAL\n"
            <<"Quel graphe souhaitez vous lire? (taper g_ .txt)\n";
    std::string nomF;
    std::cin>>nomF;
    std::cout<<std::endl;
    Graphe monGraphe{nomF};
    int a,choix=0;
    int i_debut,i_fin;

    do
    {
        std::cout<<std::endl;
        /* std::cout<<std::endl<<"\t1) BFS " //à voir
                  <<std::endl<<"\t2) DFS " //à boire
                  <<std::endl<<"\t3) Recherche des composantes connexes "*/

        std::cout<<"Que voulez vous faire ?\n"
                 <<"\t1) Afficher Graphe\n"
                 <<"\t2) Lire & Afficher Ponderation \n"
                 <<"\t3) Svgtest \n"
                 <<"\t4) Centralite de degre \n"
                 <<"\t5) Centralite de vecteur propre \n"
                 <<"\t6) Centralite de proximite\n"
                 <<"\t7) Sauvegarde\n"
                 <<"\t8) Quitter\n"
                 << std::endl;

        std::cout<<"Faites votre choix : ";
        std::cin >> choix;
        std::cout<<std::endl;


        switch(choix)
        {
        case 1 :
            monGraphe.afficher();
            break;

        case 2:
            //monGraphe.verification();
            monGraphe.lectureFichierP();
            monGraphe.afficherPoids();
            break;

        case 3 :
            //svgTest();
            monGraphe.dessinerGraphe ();
            break;

        case 4 :
            monGraphe.c_degre();
            break;

        case 5 :
            monGraphe.c_propre();
            break;

        case 6 :

            std::cout<<std::endl<<"Pour la recherche du plus court chemin :"
                     <<std::endl<<"Choisir le sommet de depart : ";
            std::cin>>i_debut;
            std::cout<<std::endl<<"Choisir le sommet d'arrivee : ";
            std::cin>>i_fin;
            monGraphe.recherchePlusCourtChemin(i_debut,i_fin);
            break;

        case 7 :
            monGraphe.sauvegarde("sauvegarde.txt");
            std::cout<<"\tsauvegarde operationelle chef !"<<std::endl;
            break;
        }
    }
    while (choix!=8);

    return 0;
}


