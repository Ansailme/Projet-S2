#include "graphe.h"
#include "svgfile.h"
#include "couleur.h"
#include "util.h"

#include <queue>
#include <map>
#include <iostream>

///Source : code TP1 M.Fercoq

///Un constructeur qui charge un graphe en mémoire à partir d’un fichier texte
Graphe::Graphe(std::string fichier)
{
    std::ifstream ifs{fichier}; //ouverture en mode lecture
    if (!ifs)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + fichier );

    ifs >> m_orient;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture de l'orientation");

    ifs >> m_ordre;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");

    int num,x,y;
    std::string lettre;
    deg.resize(m_ordre);
    for(int i=0; i<m_ordre; ++i)
    {
        ifs>>num>>lettre>>x>>y;
        m_sommets.push_back(new Sommet{i,lettre,x,y});
        deg[i]=0;
    }
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture donnees du graphe");

    int taille;
    ifs >> taille;
    if ( ifs.fail() )
        throw std::runtime_error("Probleme lecture taille du graphe");

    int nb1, nb2, indiceTaille;
    for (int j=0; j<taille; ++j) //pour chaque arrete/arc on lit les extremités
    {
        ifs>>indiceTaille>>nb1>>nb2;
        m_aretes.push_back(new Arete {j, nb1, nb2,m_sommets[nb1],m_sommets[nb2]});
        deg[nb1]+= 1;
        deg[nb2]+= 1;

        if(m_orient==0) //si non oriente
        {
            m_sommets[nb1]->remplir(m_sommets[nb2]); //on ajoute le sommet nb2 comme adejacent au sommet nb1
            m_sommets[nb2]->remplir(m_sommets[nb1]); //on ajoute le sommet nb1 comme adejacent au sommet nb2
        }
        else //si oriente
            m_sommets[nb1]->remplir(m_sommets[nb2]); //on ajoute le sommet nb2 comme adejacent au sommet nb1
    }

    ifs.close();

}

void Graphe::lectureFichierP(std::string fichier2)
{
    std::ifstream ifs2{fichier2}; //ouverture en mode lecture
    if (!ifs2)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + fichier2 );

    int nbr_arete;
    ifs2 >> nbr_arete;
    if ( ifs2.fail() )
        throw std::runtime_error("Probleme lecture nombre d'arete du graphe");

    int indiceTaille2, poids;
    for(int k=0; k<nbr_arete; k++)
    {
        ifs2>>indiceTaille2>>poids;
        m_aretes[indiceTaille2]->poids = poids;
    }
    if ( ifs2.fail() )
        throw std::runtime_error("Probleme lecture donnees du graphe");

    ifs2.close();
}


void Graphe::afficher()const
{
    std::cout<<"\tfichier topologie\n";

    if (m_orient==0)
        std::cout<<"non oriente";
    else
        std::cout<<"oriente";

    std::cout<<" d'ordre : "<< m_sommets.size();
    std::cout << std::endl;
    std::cout << std::endl;

    std::cout << "affichge sommet :\n";
    for( auto s : m_sommets)
    {
        std::cout << "\t"<<s->getNum()<<" ";
        std::cout << s->getLettre()<<" ";
        std::cout << s->getX()<<" ";
        std::cout << s->getY()<<" ";
        std::cout << std::endl;
    }

    std::cout << "taille : " << m_aretes.size();

    std::cout << "\naffichage arrete :\n";
    for(auto s : m_aretes)
    {
        std::cout<<"\t"<<s->getIndice()<<" ";
        std::cout<<s->getExtrem1()<<" ";
        std::cout<<s->getExtrem2()<<" ";
        std::cout << std::endl;
    }
}


void Graphe::afficherPoids()const
{



    std::cout << "\tfichier de ponderation\n " << std::endl;
    std::cout << "nombre d'aretes : " << m_aretes.size() << std::endl;
    for(auto s : m_aretes)
    {
        std::cout << "\t" << s->getIndice() << " ";
        std::cout << "\t" << s->poids << std::endl;
    }



    std::cout << "\n\nAsssociation 2 fichiers :\n";
    for(auto s : m_aretes)
    {
        std::cout<<"\t"<<s->getIndice()<<" ";
        std::cout<<s->getExtrem1()<<" ";
        std::cout<<s->getExtrem2()<<" ";
        std::cout<<s->poids;
        std::cout << std::endl;
    }
}


void Graphe::c_degre()
{
    for (unsigned int i=0; i<m_sommets.size(); ++i)
    {
        std::cout << "sommet " << i << " indice de centralite : " << deg[i] << std::endl;
        std::cout << "sommet " << i << " indice de centralite normalise: " << (deg[i]*(1.0/(m_ordre-1))) << std::endl;
    }
}

/*
void Graphe::c_propre()
{
    double lambda=0,lambda_prec=0;
    int Cvp=1

    for(int i=0; i<m_sommets.size(); ++i)
    {
        if(lambda-lambda_prec > 1)
        {
            lambda = sqrt(deg[i]*deg[i]);
            Cvp[i] = deg[i]/lambda;
            lambda_prec = lambda;
        }
        else
        {
            std::cout << "fin";
        }

    }

}
*/

void Graphe::verification()
{
    for(int j=0; j<m_aretes.size(); ++j)
    {
        std::cout << std::endl;
        std::cout << m_aretes[j]->m_sommet[0]->getX() << " " << m_aretes[j]->m_sommet[0]->getY();
        std::cout << std::endl;
        std::cout << m_aretes[j]->m_sommet[1]->getX() << " " << m_aretes[j]->m_sommet[1]->getY();
        std::cout << std::endl;
    }
}



void Graphe::dessinerGraphe() const
{
    Svgfile svgout;
    svgout.addGrid();

    for(auto s : m_sommets)
    {
        s->dessinerS(svgout);
    }

    for(auto s : m_aretes)
    {
        s->dessinerA(svgout);
    }

}

void Graphe::BFS(int premier)
{
    std::vector<int> i_preds(m_sommets.size());
    int i;

    ///initalisation à 99 pour voir lesquels vont être parcourus ou non
    for (size_t i=0; i<i_preds.size(); ++i)
        i_preds[i]=99;

    ///initialisation des couleurs à blanc
    for (auto it : m_sommets)
        it->reinitialiserCouleur();

    std::queue<Sommet*> file;
    file.push(m_sommets[premier]); //enfile le premier
    m_sommets[premier]->setCouleur(1); //on met le premier en gris

    ///parcours
    while (!file.empty())
    {
        i = file.front()->getNum(); //valeur qui va être pop
        file.pop(); //depifiler
        m_sommets[i]->setCouleur(2); //met le premier en noir
        for (auto it : m_sommets)
        {
            if (it->estAdjacentA(i))//fonction qui permet de savoir si i et it sont adjacents
            {
                if (it->getCouleur()==0) //si ne fait pas déjà partie de la file
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
        if (temp!=99) //s'il a été parcouru
        {
            std::cout<<std::endl<<i;
            if (premier!=temp) //si le sommet i n'est pas un adjacent du premier
            {
                //on remonte le tableau de predecesseur en predesseur jusqu'à ce qu'on remonte au premier
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
                    //on remonte le tableau de predecesseur en predesseur jusqu'à ce qu'on remonte au premier
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
            if (it->getCouleur()==0) //si ne fait pas déjà partie de la pile
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
    std::map<int,std::vector<int>> compoConnexes; //numéro et identidfiant des sommets de chaque composante

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
                //si on découvre un nouveau sommet qui n'a pas encore été rangé dan sune composante connexe
                ++nbCompo; //nouvelle composante
                compoConnexes[nbCompo].push_back(it->getNum()); //on ajoute le premier dans une nouvel composante que l'on crée
                recuDFS(i_preds,it); //recherche de tous les sommets de la composante avec un DFS
                if (!i_preds.empty())
                    for (auto et : i_preds)
                        compoConnexes[nbCompo].push_back(et.first); //on ajoute tous les sommets trouvé à la composante


                stop=true; //on s'occupe d'une composante à la fois
            }

        }
        i_preds.clear(); //on recommence en vidant la liste de sommets

    }
    while (stop); //tant qu'il a des sommets qui n'ont pas été parcouru

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
        ///recherche de chaine ou cycle eulérien
        for (auto it : compoConnexes)
            i=it.first;
        if (i!=1) //graphe non connexe car plusiseurs composantes connexes
            std::cout<<std::endl<<"Le graphe n'admet ni une chaine ni un cycle eulerien car il n'est pas connexe";
        else
        {
            int nbSommetDegImpaire=0;
            for (auto it :m_sommets)
            {
                if (it->estDegreImpair()) //revoie vrai si le sommet est de degré impair
                {
                    ++nbSommetDegImpaire; //compte le nb de sommets impairs
                }

            }
            if (nbSommetDegImpaire==0)
                std::cout<<std::endl<<"Le graphe admet un cycle eulerien";
            else if (nbSommetDegImpaire==2)
                std::cout<<std::endl<<"Le graphe admet une chaine eulerienne";
            else
                std::cout<<std::endl<<"Le graphe n'admet ni une chaine ni un cycle eulerien car il possède 1 ou plus de 2 sommets de degre impaire";
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
