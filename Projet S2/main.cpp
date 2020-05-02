#include <iostream>
#include "graphe.h"
#include "svgfile.h"
#include "couleur.h"

int main()
{
    std::cout<<"\n\t\t MENU PRINCIPAL\n"<<std::endl;
    int choice =0;
    do
    {
        std::cout <<"Graphes disponibles : \n\t-etoile1-2-3-4 \n\t-cube \n\t-france \n\t-monde\n";
        std::cout<<"\n\nQuel graphe souhaitez-vous utiliser? \n";
        std::string nomF;
        std::cin>>nomF;
        std::cout<<std::endl;
        Graphe monGraphe{"g_" + nomF +".txt"};
        bool fermeture = 1;
        int a,choix=0, s=0, modif=-1;
        int i_debut,i_fin;
        double poids=0;
        int f1=0, f2=0;
        int verif=0;
        do
        {
            ///Affichage menu avec les choix
            std::cout<<"Que souhaitez-vous faire ?\n"<<std::endl
                     <<"\t1) Lire & afficher les donnees du graphe\n"
                     <<"\t2) Lire & afficher les donnees de ponderation \n"
                     <<"\t3) Dessiner le graphe SVG \n"
                     <<"\t4) Indice centralite de degre \n"
                     <<"\t5) Indice centralite de vecteur propre \n"
                     <<"\t6) Indice centralite de proximite\n"
                     <<"\t7) Calcul plus court chemin\n"
                     <<"\t8) Sauvegarder les indices dans un fichier\n"
                     <<"\t9) Fermer ce graphe et en charger un autre\n"
                     <<"\t10) Connexite\n"
                     <<"\t11) Supprimer une arete\n"
                     <<"\t12) Calcul des differences\n"
                     <<"\t13) Quitter le programme\n"


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
                monGraphe.lectureFichierP(); ///lecture fichier pond�ration
                monGraphe.afficherPoids(); ///affichage fichier pond�ration
                break;

            case 3 :
                //svgTest();
                monGraphe.dessinerGraphe (); ///dessiner le graphe en svgout
                break;

            case 4 :
                std::cout
                         <<std::endl<<"Choisir le sommet de depart : ";
                std::cin>>i_debut;
                monGraphe.DFS(i_debut);
                //monGraphe.c_degre(); ///calcul centralit� de degr�
                break;

            case 5 :
                monGraphe.c_propre();  ///calcul centralit� vecteur propre
                break;

            case 6 :
                ///Dijkstra : calcul + court chemin = centralit� de proximit�
                monGraphe.calcul_cp_auto();
                break;

            case 7 :
                std::cout << "Etes-vous sur ? 1:oui 0:non" <<std::endl;
                std::cin>>verif;
                std::cout << std::endl;
                if(verif ==1)
                {
                    std::cout<<std::endl<<"Plus court chemin entre:"
                         <<std::endl<<"Choisir le sommet de depart : ";
                std::cin>>i_debut;
                std::cout<<std::endl<<"Choisir le sommet d'arrivee : ";
                std::cin>>i_fin;
                poids = monGraphe.c_prox(i_debut,i_fin);
                std::cout<< std::endl;
                monGraphe.affichage(i_fin, poids);
                std::cout<< std::endl;
                }
                else
                break;


            case 8 :
                monGraphe.sauvegarde(s); ///sauvegarde des indices dans fichier txt
                std::cout<<"\tsauvegarde du fichier operationelle chef !\n"<<std::endl;
                break;

            case 10:
                monGraphe.recherchecompoConnexes();
                break;

            case 11 :
                std::cout << "Etes-vous sur ? 1:oui 0:non" <<std::endl;
                std::cin>>verif;
                std::cout << std::endl;
                if(verif ==1)
                {
                    monGraphe.supp_arete();
                    s=s+1;
                }

                break;

            case 12 :
                std::cout<<"Quels fichiers comptez-vous comparer ?\n"<< std::endl;
                std::cin >> f1 >> f2;
                monGraphe.calculDiff_indice(f1,f2);
                break;

            case 13 :
                return fermeture;
                break;
                }


        } while (choix!=9);
    } while (choice==0);

    return 0;
}


