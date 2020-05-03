#include <iostream>
#include "graphe.h"
#include "svgfile.h"
#include "couleur.h"
#include "windows.h"

///source couleur :
///-https://www.daniweb.com/programming/software-development/code/216345/add-a-little-color-to-your-console-text

int main()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //utilisation de la couleur sur la console

    int choice =0;
    do
    {
        int k=15;
        SetConsoleTextAttribute(hConsole, k); //initialisation de la couleur à chaque utilisation de cette fonction
        std::cout<<"\n\n\t\tACCESSIBILITE & VULNERABILITE DES RESEAUX \n";
        std::cout<<"\n\t\t\t    MENU PRINCIPAL\n";
        k=14;
        SetConsoleTextAttribute(hConsole, k);
        std::cout<<"\n\t\tQuel graphe souhaitez-vous charger? \n";
        std::string nomF;
        std::cin>>nomF;
        std::cout<<std::endl;
        Graphe monGraphe{"g_"+nomF +".txt"};
        bool fermeture = 1;
        int choix=0, s=0;
        int i_debut,i_fin;
        double poids=0;
        int f1=0, f2=0;
        int verif=0;
        int lectureF2=0;
        do
        {
            ///Affichage menu avec les choix
            int k=15;
            SetConsoleTextAttribute(hConsole, k);
            std::cout<<"\tQue souhaitez-vous faire ?\n"<<std::endl
                     <<"\t1) Donnees du graphe\n"
                     <<"\t2) Charger un fichier de ponderation \n"
                     <<"\t3) Dessiner le graphe \n"
                     <<"\t4) Calculer - afficher les indices\n"
                     <<"\t5) Sauvegarder les indices dans un fichier\n"
                     <<"\t6) Calculer le plus court chemin\n"
                     <<"\t7) Connexite du graphe\n"
                     <<"\t8) Fermer ce graphe et en charger un autre\n"
                     <<"\t9) Supprimer une arete\n"
                     <<"\t10) Calcul des differences d'indice\n"
                     <<"\t11) Quitter le programme\n"
                     << std::endl;
            k=14;
            SetConsoleTextAttribute(hConsole, k);
            std::cout<<"Faites votre choix : ";
            std::cin >> choix;
            std::cout<<std::endl;
            k=15;
            SetConsoleTextAttribute(hConsole, k);


            switch(choix)
            {
            case 1 :
                monGraphe.afficherG(); ///lecture du graphe
                break;

            case 2:
                //monGraphe.verification();
                do
                {
                    lectureF2=monGraphe.lectureFichierP(); ///lecture fichier pondération
                }
                while (lectureF2==1);
                monGraphe.afficherPoids(); ///affichage fichier pondération
                break;

            case 3 :
                monGraphe.dessinerGraphe (); ///dessiner le graphe en svgout
                break;

            case 4 :
                k=11;
                SetConsoleTextAttribute(hConsole, k);
                monGraphe.c_degre(); ///calcul centralité de degré
                monGraphe.c_propre(); ///calcul centralité vecteur propre
                monGraphe.calcul_cp_auto(); ///calcul centralité proximité
                monGraphe.c_intermediarite();
                break;

            case 5 :
                monGraphe.sauvegarde(s); ///sauvegarde des indices dans fichier txt
                k=10;
                SetConsoleTextAttribute(hConsole, k);
                std::cout<<"\tsauvegarde du fichier "<<s<<" operationelle chef !\n"<<std::endl;
                break;

            case 6 :
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
                    monGraphe.affichage(i_fin, poids); //affichage du plus court chemin
                    std::cout<< std::endl;
                }
                break;

            case 7 :
                k=11;
                SetConsoleTextAttribute(hConsole, k);
                monGraphe.recherchecompoConnexes();
                monGraphe.connexite();
                break;

            case 8 :
                break;

            case 9:
                std::cout << "Etes-vous sur ? 1:oui 0:non" <<std::endl;
                std::cin>>verif;
                std::cout << std::endl;
                if(verif ==1)
                {
                    monGraphe.supp_arete();
                    s=s+1;
                }
                std::cout<<std::endl;
                std::cout<<"\nVoulez vous re-calculer les indices ? 1:oui 0:non "<<std::endl;
                std::cin>>verif;
                std::cout<<std::endl;
                if (verif == 1)
                {
                    k=11;
                    SetConsoleTextAttribute(hConsole, k);
                    monGraphe.c_degre();
                    monGraphe.c_propre();
                    monGraphe.calcul_cp_auto();
                    monGraphe.c_intermediarite();
                    k=12;
                    SetConsoleTextAttribute(hConsole, k);
                    std::cout << "\tVeuillez a bien sauvegarder la modification en tapant 5 \n"<< std::endl;
                }
                break;

            case 10 :
                std::cout<<"Quels fichiers comptez-vous comparer ?\n"<< std::endl;
                k=10;
                SetConsoleTextAttribute(hConsole, k);
                std::cout<<" fichier : ";
                std::cin >> f1;
                std::cout<<" fichier : ";
                std::cin >> f2;
                k=15;
                SetConsoleTextAttribute(hConsole, k);
                monGraphe.calculDiff_indice(f1,f2);
                break;

            case 11 :
                return fermeture;
                break;
            case 12 :
                std::cout
                            <<std::endl<<"Choisir le sommet de depart : ";
                    std::cin>>i_debut;
                monGraphe.BFS(i_debut);
            }

        }
        while (choix!=8);
    }
    while (choice==0);


    return 0;
}

