#include <iostream>
#include "graphe.h"
#include "svgfile.h"
#include "couleur.h"

//void svgTest();

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
          std::cout<<"\t4) Afficher Graphe "
                   <<"\t5) Affcher Ponderation "
                   <<"\t6) svgtest"
                   <<"\t7) Quitter"
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
                break;

        case 5 :
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


/*
/// Code initial pour comprendre les ajouts de primitives
void svgTest()
{
    /// Sortie graphique dans le fichier output.svg
    /// ( options à voir svgfile.h au niveau du constructeur )
    Svgfile svgout;

    /// Dessin du repère cartésien (facultatif)
    svgout.addGrid();

    /// On a perdu les dessins de sphères (une autre fois peut-être)

    /// Nouveau : on peut toujours utiliser les couleurs "red" "green"...
    /// Mais on a maintenant un type Couleur qui prend 3 composantes RVB
    /// Exemple pour déclarer du Jaune (beaucoup Rouge + Vert, pas de bleu)
    /// Chaque canal est dans l'intervalle [0..255]
    Couleur jaune{255, 200, 0};

    /// Dessin de disque : xcentre ycentre rayon couleur
    svgout.addDisk(50, 100, 10, jaune);
    svgout.addDisk(200, 100, 30, Couleur{100, 150, 200});
    svgout.addDisk(300, 100, 30, "pink");
    svgout.addDisk(400, 100, 30);

    /// Dessin de cercle : xcentre ycentre rayon epaisseur couleur
    svgout.addCircle(100, 200, 30, 10, "red");
    svgout.addCircle(200, 200, 30, 5, "red");
    svgout.addCircle(300, 200, 30, 1, "red");

    /// Dessin de triangle : x1 y1 x2 y2 x3 y3 couleur_remplissage ...
    ///                         epaisseur_bordure couleur_bordure
    svgout.addTriangle(100,300, 200,300, 150,250, "green", 5, "orange");

    /// Dessin de triangle : x1 y1 x2 y2 x3 y3 couleur_remplissage
    svgout.addTriangle(300,300, 400,300, 350,250, "green");

    /// Dessin de texte : xcentre ycentre texte couleur
    svgout.addText(100, 320, "Hello Triangles !", Couleur{0,100,0} );

    /// Dessin de texte : xcentre ycentre texte couleur
    svgout.addText(342, 320, 6*7, "black");

    /// Dessin de croix : xcentre ycentre taille couleur
    svgout.addCross(400, 200, 25);

    /// Dessin de segments : x1 y1 x2 y2 couleur
    svgout.addLine(300, 70, 400, 70);
    svgout.addLine(300, 130, 400, 130);
    svgout.addLine(340, 70, 300, 30, "blue");
    svgout.addLine(360, 70, 400, 30, "red");

    /// L'objet svgout est automatiquement libéré à la sortie
    /// de ce sous-programme : le fichier output.svg est alors fermé

}
*/

