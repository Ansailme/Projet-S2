#include "graphe.h"
#include <queue>
#include <map>

///Source : code TP1 M.Fercoq

///Un constructeur qui charge un graphe en m�moire � partir d�un fichier texte
Graphe::Graphe(std::string fichier)
{
    std::ifstream ifs{fichier}; //ouverture en mode lecture
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + fichier );

    ifs >> m_orient;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture de l'orientation");

    int ordre;
    ifs >> ordre;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");

    int indice,x,y;
    char lettre;
    for(int i=0;i<ordre;++i)
    {
        m_sommets.push_back(new Sommet{i});
        ifs>>indice>>lettre>>x>>y;
    }
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture donnees du graphe");

    int taille;
    ifs >> taille;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture taille du graphe");

    int nb1, nb2, indiceTaille;
    for (int j=0; j<taille; ++j) //pour chaque arrete/arc on lit les extremit�s
    {
        ifs>>indiceTaille>>nb1>>nb2;
        if (m_orient==0) //si non oriente
        {
            m_sommets[nb1]->remplir(m_sommets[nb2]); //on ajoute le sommet nb2 comme adejacent au sommet nb1
            m_sommets[nb2]->remplir(m_sommets[nb1]); //on ajoute le sommet nb1 comme adejacent au sommet nb2
        }
        else //si oriente
            m_sommets[nb1]->remplir(m_sommets[nb2]); //on ajoute le sommet nb2 comme adejacent au sommet nb1
    }
    ifs.close();
}


void Graphe::afficher ()const
{
    std::cout<<std::endl;
    std::cout<<"graphe ";
    if (m_orient==0)
        std::cout<<"non oriente";
    else
        std::cout<<"oriente";
    std::cout<<std::endl
             <<"ordre = "
             <<m_sommets.size();
    std::cout<<std::endl
             <<"listes d'adjacence :"
             <<std::endl;
    for (auto it : m_sommets)
        it->afficher();



}

void Graphe::BFS(int premier)
{
    std::vector<int> i_preds(m_sommets.size());
    int i;

    ///initalisation � 99 pour voir lesquels vont �tre parcourus ou non
    for (size_t i=0; i<i_preds.size(); ++i)
        i_preds[i]=99;

    ///initialisation des couleurs � blanc
    for (auto it : m_sommets)
        it->reinitialiserCouleur();

    std::queue<Sommet*> file;
    file.push(m_sommets[premier]); //enfile le premier
    m_sommets[premier]->setCouleur(1); //on met le premier en gris

    ///parcours
    while (!file.empty())
    {
        i = file.front()->getNum(); //valeur qui va �tre pop
        file.pop(); //depifiler
        m_sommets[i]->setCouleur(2); //met le premier en noir
        for (auto it : m_sommets)
        {
            if (it->estAdjacentA(i))//fonction qui permet de savoir si i et it sont adjacents
            {
                if (it->getCouleur()==0) //si ne fait pas d�j� partie de la file
                {
                    file.push(it);
                    i_preds[it->getNum()]=i;
                }

            }

        }
        m_sommets[i]->setAdjacents(1); //met les adjacents en gris

    }

    ///affichage
    int pred;
    for (size_t i=0; i<i_preds.size(); ++i)
    {

        int temp=i_preds[i]; //valeur tempon
        if (temp!=99) //s'il a �t� parcouru
        {
            std::cout<<std::endl<<i;
            if (premier!=temp) //si le sommet i n'est pas un adjacent du premier
            {
                //on remonte le tableau de predecesseur en predesseur jusqu'� ce qu'on remonte au premier
                do
                {
                    pred = temp;
                    std::cout<<" <-- "<<pred;
                    temp=i_preds[pred];

                }
                while (premier!=pred);

            }

            else
                std::cout<<" <-- "<<premier;
        }

    }


}

void Graphe::DFS(int premier)
{
    std::map<int, int> i_preds;

    ///mets les sommets en blancs
    for (auto it : m_sommets)
        it->reinitialiserCouleur();

    ///parcours
    recuDFS(i_preds,m_sommets[premier]);

    ///affichage
    int pred;
    for (auto it : i_preds)
    {
        if (it.first!=premier)
        {
            int temp=it.second; //valeur tempon
            std::cout<<std::endl<<it.first;
            if (temp!=premier) //si le sommet i n'est pas un adjacent au premier
            {
                do
                {
                    //on remonte le tableau de predecesseur en predesseur jusqu'� ce qu'on remonte au premier
                    pred=temp;
                    std::cout<<" <-- "<<pred;
                    temp=i_preds[pred];

                }
                while (pred!=premier);
            }
            else
            {
                std::cout<<" <-- "<<premier;
            }

        }

    }


}

void Graphe::recuDFS(std::map<int, int>& i_preds,Sommet* s)
{
    //algorithme recurence de Mme Palasi
    s->setCouleur(1);//gris
    for (auto it : m_sommets)
    {
        if (it->estAdjacentA(s->getNum()))
        {
            if (it->getCouleur()==0) //si ne fait pas d�j� partie de la pile
            {
                i_preds[it->getNum()]=s->getNum();
                recuDFS(i_preds,it); //par recurence

            }
        }

    }
    s->setCouleur(2); //met en noir

}

void Graphe::recherchecompoConnexes()
{
    int nbCompo=0;
    bool stop = false;
    std::map<int, int> i_preds; //liste des prdecesseurs pour le DFS
    std::map<int,std::vector<int>> compoConnexes; //num�ro et identidfiant des sommets de chaque composante

    ///mets les sommets en blancs
    for (auto it : m_sommets)
        it->reinitialiserCouleur();

    ///recherche de composante de sommets
    do
    {
        stop=false;
        for (auto it : m_sommets)
        {

            if (it->getCouleur()!=2 && !stop)
            {
                //si on d�couvre un nouveau sommet qui n'a pas encore �t� rang� dan sune composante connexe
                ++nbCompo; //nouvelle composante
                compoConnexes[nbCompo].push_back(it->getNum()); //on ajoute le premier dans une nouvel composante que l'on cr�e
                recuDFS(i_preds,it); //recherche de tous les sommets de la composante avec un DFS
                if (!i_preds.empty())
                    for (auto et : i_preds)
                        compoConnexes[nbCompo].push_back(et.first); //on ajoute tous les sommets trouv� � la composante


                stop=true; //on s'occupe d'une composante � la fois
            }

        }
        i_preds.clear(); //on recommence en vidant la liste de sommets

    }
    while (stop); //tant qu'il a des sommets qui n'ont pas �t� parcouru

    ///affichage
    for (auto it : compoConnexes)
    {
        std::cout<<std::endl<<"Composante connexe "<<it.first<<" : ";
        for (auto et : it.second)
            std::cout<<et<<" ";
    }


    if (m_orient==0) //si le graphe est non oriente
    {
        int i;
        ///recherche de chaine ou cycle eul�rien
        for (auto it : compoConnexes)
            i=it.first;
        if (i!=1) //graphe non connexe car plusiseurs composantes connexes
            std::cout<<std::endl<<"Le graphe n'admet ni une chaine ni un cycle eulerien car il n'est pas connexe";
        else
        {
            int nbSommetDegImpaire=0;
            for (auto it :m_sommets)
            {
                if (it->estDegreImpair()) //revoie vrai si le sommet est de degr� impair
                {
                    ++nbSommetDegImpaire; //compte le nb de sommets impairs
                }

            }
            if (nbSommetDegImpaire==0)
                std::cout<<std::endl<<"Le graphe admet un cycle eulerien";
            else if (nbSommetDegImpaire==2)
                std::cout<<std::endl<<"Le graphe admet une chaine eulerienne";
            else
                std::cout<<std::endl<<"Le graphe n'admet ni une chaine ni un cycle eulerien car il poss�de 1 ou plus de 2 sommets de degre impaire";
        }
    }
    else
        std::cout<<std::endl<<"Le graphe n'admet ni une chaine ni un cycle eulerien car il est oriente";

}

Sommet* Graphe::recupSommet (int indice)
{
    return m_sommets[indice];
}


Graphe::~Graphe()
{
    for (auto it : m_sommets)
        delete it;
}
