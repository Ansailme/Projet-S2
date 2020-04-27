#include <iostream>
#include "Graphe.h"

/*
Source :
    file:///C:/Users/alexa/Downloads/Aide_TP2_TP3_partie2_Dijkstra.pdf
    https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-priority_queue-stl/?ref=lbp&fbclid=IwAR1xrePCIcKHmC-cql7nehODwp7ldLnewmUF3FdVSzs2qkQ1PWOfcCcWdK0
*/


int main()
{
    int premier,dernier;



    Graph tot("sommet&force.txt");
    tot.afficher_graphe();
    std::cout << "Entrer sommet 1: ";
    std::cin >> premier;
    std::cout << "Etrer dernier sommet: ";
    std::cin >> dernier;
    tot.chemin(premier, dernier);
    tot.affichage(dernier);

}
