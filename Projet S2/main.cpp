#include <iostream>
#include "graphe.h"
#include "svgfile.h"
#include "couleur.h"

int main()
{
    std::cout<<"\t\t MENU PRINCIPAL\n"<<std::endl;
    int choice =0;
    do
    {
        std::cout<<"Quel graphe souhaitez-vous utiliser? \n";
        std::string nomF;
        std::cin>>nomF;
        std::cout<<std::endl;
        Graphe monGraphe{"g_" + nomF +".txt"};
        bool fermeture = 1;
        int a,choix=0;
        int i_debut,i_fin;
        double poids=0;
        do
        {
            /* std::cout<<std::endl<<"\t1) BFS "
                      <<std::endl<<"\t2) DFS "
                      <<std::endl<<"\t3) Recherche des composantes connexes "*/

            ///Affichage menu avec les choix
            std::cout<<"Que souhaitez-vous faire ?\n"<<std::endl
                     <<"\t1) Lire & afficher les donnees du graphe\n"
                     <<"\t2) Lire & afficher les donnees de ponderation \n"
                     <<"\t3) Dessiner le graphe SVG \n"
                     <<"\t4) Indice centralite de degre \n"
                     <<"\t5) Indice centralite de vecteur propre \n"
                     <<"\t6) Indice centralite de proximite\n"
                     <<"\t7) Sauvegarder les indices dans un fichier\n"
                     <<"\t8) Fermer ce graphe et en charger un autre\n"
                     <<"\t9) Quitter le programme\n"
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
                /*std::cout<<std::endl<<"Plus court chemin entre:"
                         <<std::endl<<"Choisir le sommet de depart : ";
                std::cin>>i_debut;
                std::cout<<std::endl<<"Choisir le sommet d'arrivee : ";
                std::cin>>i_fin;
                poids = monGraphe.c_prox(i_debut,i_fin);
                monGraphe.affichage(i_fin, poids);
                monGraphe.calcul_cp(i_debut, i_fin);
                std::cout<< std::endl;*/
                monGraphe.calcul_cp_auto();

                break;

            case 7 :
                monGraphe.sauvegarde(); ///sauvegarde des indices dans fichier txt
                std::cout<<"\tsauvegarde operationelle chef !\n"<<std::endl;
                break;
            case 9 :
                return fermeture;
            }
        } while (choix!=8);
    } while (choice==0);

    return 0;
}


