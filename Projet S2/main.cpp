#include <iostream>
#include "graphe.h"
#include "svgfile.h"
#include "couleur.h"

int main()
{
    ///Affichage Menu Pricipal avec chargement du fichier graphe souhaité par l'user
    std::cout<<"\t\t MENU PRINCIPAL\n"
             <<"Quel graphe souhaitez-vous lire? \n";

        std::string nomF;
        std::cin>>nomF;
        std::cout<<std::endl;
    Graphe monGraphe{"g_" + nomF +".txt"};
    int a,choix=0;
    int i_debut,i_fin;
    double poids=0;

    do
    {
        /* std::cout<<std::endl<<"\t1) BFS "
                  <<std::endl<<"\t2) DFS "
                  <<std::endl<<"\t3) Recherche des composantes connexes "*/

        ///Affichage menu avec les choix
        std::cout<<"Que souhaitez-vous faire ?\n"
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
            monGraphe.afficherG(); ///lecture du graphe
            break;

        case 2:
            //monGraphe.verification();
            monGraphe.lectureFichierP(); ///lecture fichier pondération
            monGraphe.afficherPoids(); ///affichage fichier pondération
            //monGraphe.lienAS(); ///ecriture extremités - poids
            break;

        case 3 :
            //svgTest();
            monGraphe.dessinerGraphe (); ///dessiner le graphe en svgout
            break;

        case 4 :
            monGraphe.c_degre(); ///calcul centralité de degré
            break;

        case 5 :
            monGraphe.c_propre();  ///calcul centralité vecteur propre
            break;

        case 6 :
            ///Dijkstra : calcul + court chemin = centralité de proximité
            std::cout<<std::endl<<"Pour la recherche du plus court chemin :"
                     <<std::endl<<"Choisir le sommet de depart : ";
            std::cin>>i_debut;
            std::cout<<std::endl<<"Choisir le sommet d'arrivee : ";
            std::cin>>i_fin;
            poids = monGraphe.c_prox(i_debut,i_fin);
            monGraphe.affichage(i_fin, poids);
            monGraphe.calcul_cp(i_debut, i_fin);

            break;

        case 7 :
            monGraphe.sauvegarde(); ///sauvegarde des indices dans fichier txt
            std::cout<<"\tsauvegarde operationelle chef !"<<std::endl;
            break;
        }
    }
    while (choix!=8);

    return 0;
}


