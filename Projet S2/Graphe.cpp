#include "graphe.h"

/// source : exemple de M.Fercoq et méthodes de Mme Palasi

Graphe::Graphe(std::string fichier)
{
    std::ifstream ifs(fichier); //ouverture en mode lecture
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + fichier );


    int ordre;
    ifs >> ordre;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");

    int numSommet;
    for (int i=0; i<ordre; ++i) //on crée chaque sommet à partir de son numéro
    {
        ifs>>numSommet;
        m_sommets.push_back( new Sommet{numSommet});
    }


    int taille;
    ifs >> taille;
    if ( ifs.fail())
        throw std::runtime_error ("Probleme lecture de la taille");

    int nb1, nb2,nb3;

    for (int j=0; j<taille; ++j) //pour chaque arc
    {
        //on recupère les données du fichier
        ifs>>nb1>>nb2>>nb3; //sommet 1 vers sommet 2 + poids de l'arc

        m_sommets[nb1]->remplir(m_sommets[nb2],nb3);//on rempli les adjacents de sommet[nb1]
    }


}


void Graphe::afficher ()const
{
    std::cout<<std::endl
             <<"ordre = "
             <<m_sommets.size();
    std::cout<<std::endl
             <<"listes d'adjacence :"
             <<std::endl;
    for (auto it : m_sommets)
        it->afficher();

}

void Graphe::recherchePlusCourtChemin(int i_debut, int i_fin)
{
    ///initialisation
    for (auto it : m_sommets)
        it->setMarquage(0);

    int tab_distance[m_sommets.size()]; //recupère les plus court chemin de s0 à chaque sommet parcouru
    //std::vector <Sommet*> sommetsParcourus; //recupère la liste et l'odre dans lequel les sommets sont parcouru
    int tab_predecesseurs[m_sommets.size()];

    for (size_t i=0; i<m_sommets.size(); ++i)
        tab_distance[i]=999; //~infini

    for (size_t i=0; i<m_sommets.size(); ++i)
        tab_predecesseurs[i]=99;


    Sommet*s=m_sommets[i_debut]; //s=s0
    tab_distance[i_debut]=0;
    m_sommets[i_debut]->setMarquage(1);//1 pour dire qu'on a trouver la plus petite distance
    //sommetsParcourus.push_back(m_sommets[i_debut]);

    int distance, d_min, id_d_min;

    ///recherche

    do
    {
        d_min=999;
        //on determine le plus proche de s0 en partant de s
        for (auto it : m_sommets)
        {
            if (s->estAdjacentA(it->getNum())) //si on peut aller de s à it
            {
                distance=s->getDist(it->getNum());

                if (tab_distance[it->getNum()]>tab_distance[s->getNum()]+distance)//si c'est plus court d'aller de s0 à it en passant par s
                {
                    //si on trouve un plus court chemin que celui en mémoire
                    tab_distance[it->getNum()]=tab_distance[s->getNum()]+distance;
                    tab_predecesseurs[it->getNum()]=s->getNum();
                }
            }

        }
        //recherche du plus près sommet de s0 qui n'a pas encore était étudié
        for (size_t i=0; i<m_sommets.size(); ++i) //on parcours la tab de distance
        {
            if (m_sommets[i]->getMarquage()!=1) //pas parcouru
            {
                if (tab_distance[i]<d_min) //si c'est le plus près
                {
                    d_min=tab_distance[i];
                    id_d_min=i; //on garde en mémoire l'identifiant du plus près
                }
            }
        }
        s=m_sommets[id_d_min]; //le plus proche sommet pas encore etudier devient le prochain sommet à parcourir
        s->setMarquage(1);//1 pour dire qu'on a trouver la plus petite distance
        //sommetsParcourus.push_back(s);

    }
    while (m_sommets[i_fin]->getMarquage()!=1);  //tant qu'on a pas trouver le plus court chemin jusqu'au sommet final


    ///affichage

    //on affiche la liste des sommets parcouru pour aller de s0 au sommet d'arrivé

    /*std::cout<<sommetsParcourus[0]->getNum();
    for (size_t i=1; i<sommetsParcourus.size();++i)
    {
        std::cout<<" -> "<<sommetsParcourus[i]->getNum();
    }*/
    std::cout<<std::endl;

    std::vector<Sommet*> sommetsParcourus; //liste de sommets en chemin
    sommetsParcourus.push_back(m_sommets[i_fin]);
    int pred;
    int temp=tab_predecesseurs[i_fin];
    if (temp!=99)
    {
        std::cout<<std::endl<<i_fin;
        if (i_debut!=temp)
        {
            do
            {//on remonte le tableau jusqu'à ce que le predecesseur soit s0
                pred = temp;
                std::cout<<" <-- "<<pred; //on aficche chaque predecesseur
                sommetsParcourus.push_back(m_sommets[pred]); //on ajoute à la liste chaque predecesseur
                temp=tab_predecesseurs[pred];

            }
            while (i_debut!=pred);

        }

        else //si pas d'intermédiaire entre s0 et le sommet de fin
            std::cout<<" <-- "<<i_debut;
    }

    //on affiche la longeur pour chaque arc parcouru
    std::cout<<" longeur = ";
    size_t taille=sommetsParcourus.size();

    if (taille!=1) //si s0 et le sommet final sont adjacents
    {
        for (size_t i=taille-1 ; i>1; --i) //sens inverse parce que pour remplir le vecteur on est partie de la fin
        {
            std::cout<<sommetsParcourus[i]->getDist(sommetsParcourus[i-1]->getNum())<<"+";
        }
        std::cout<<sommetsParcourus[1]->getDist(sommetsParcourus[0]->getNum())<<"=";
    }
    std::cout<<tab_distance[i_fin];







}


