#include "graphe.h"
#include "svgfile.h"
#include "couleur.h"
#include "util.h"
#include <cmath>
#include <queue>
#include <map>
#include <iostream>
#include "windows.h"

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); //utilisation de la couleur sur la console

///Source constructeur graphe : code TP1 M.Fercoq

///Un constructeur qui charge un graphe en mémoire à partir d’un fichier texte

Graphe::Graphe(std::string fichier)
{
    std::ifstream ifs{fichier}; //ouverture en mode lecture
    if (!ifs) //si le fichier n'existe pas, indication pour charger un autre graphe
    {
        int k=12;
        SetConsoleTextAttribute(hConsole, k);
        std::cout << "Ce graphe n'existe pas, chargez en un autre" << std::endl ;
        std::cout<<"\n\t\t! Tapez 8 !"<<std::endl<<std::endl;
    }

    else
    {
        ifs >> m_orient; //recuperer l'orientation du graphe
        if ( ifs.fail() )
            throw std::runtime_error("Probleme lecture de l'orientation");

        ifs >> m_ordre; //recuperer l'ordre du graphe
        if ( ifs.fail() )
            throw std::runtime_error("Probleme lecture ordre du graphe");

        int num,x,y;
        std::string lettre;
        deg.resize(m_ordre);
        for(int i=0; i<m_ordre; ++i) //parcours le nombre total de sommets
        {
            ifs>>num>>lettre>>x>>y; //recuperer l'indice, le nom et les coordonnées des sommets
            m_sommets.push_back(new Sommet{i,lettre,x,y}); //alloue une nouvelle place pour les données d'un nouveau sommet
            deg[i]=0; //initialistaion des degrés d'un sommet à 0
        }
        cp.reserve(m_sommets.size()); //reserve de la place pour les calculs d'indice du vecteur propre normalisé et non normalisé
        cpn.reserve(m_sommets.size());

        if ( ifs.fail() )
            throw std::runtime_error("Probleme lecture donnees du graphe");

        int taille;
        ifs >> taille; //recupere la taille du graphe
        if ( ifs.fail() )
            throw std::runtime_error("Probleme lecture taille du graphe");

        int nb1, nb2, indiceTaille;
        for (int j=0; j<taille; ++j) //pour chaque arrete/arc on lit les extremités
        {
            ifs>>indiceTaille>>nb1>>nb2; //recuperer l'indice des aretes, et ses 2 extremités
            m_aretes.push_back(new Arete {j,m_sommets[nb1],m_sommets[nb2]});////alloue une nouvelle place pour les données d'une nouvelle arete

            if(m_orient==0) //si graphe non oriente
            {
                m_sommets[nb1]->remplir(m_sommets[nb2]); //on ajoute le sommet nb2 comme adjacent au sommet nb1
                m_sommets[nb2]->remplir(m_sommets[nb1]); //on ajoute le sommet nb1 comme adjacent au sommet nb2
            }
            else //si oriente
                m_sommets[nb1]->remplir(m_sommets[nb2]); //on ajoute le sommet nb2 comme adejacent au sommet nb1
        }

        ifs.close(); //fermeture du fichier

        //effacer toutes les sauvegardes faites précédemment
        remove("sauvegarde0.txt");
        remove("sauvegarde_brut0.txt");
        remove("sauvegarde1.txt");
        remove("sauvegarde_brut1.txt");
        remove("sauvegarde2.txt");
        remove("sauvegarde_brut2.txt");
        remove("sauvegarde3.txt");
        remove("sauvegarde_brut3.txt");

    }
}

//destructeur
Graphe::~Graphe()
{
    for (auto it : m_sommets)
        delete it;
}


//lecture des fichiers
int Graphe::lectureFichierP()
{
    int k=15;
    SetConsoleTextAttribute(hConsole, k);
    std::cout<< std::endl <<"Quel fichier ponderation souhaitez-vous lire?\n";
    std::string fichier2;
    std::cin>>fichier2;
    std::ifstream ifs2{"p_" + fichier2 + ".txt"}; //ouverture du fichier
    if (!ifs2) //si le fichier n'existe pas
    {
        int k=12;
        SetConsoleTextAttribute(hConsole, k);
        std::cout << "Ce fichier ponderation n'existe pas, chargez en un autre" << std::endl ;
        return 1;
    }
    else
    {
        int k=15;
        SetConsoleTextAttribute(hConsole, k);
        int nbr_arete;
        ifs2 >> nbr_arete; //recupere le nombre d'aretes total
        if ( ifs2.fail() )
            throw std::runtime_error("Probleme lecture nombre d'arete du graphe");

        int indiceTaille2;
        double poids;
        for(int k=0; k<nbr_arete; k++) //parcours de toutes les aretes
        {
            ifs2>>indiceTaille2>>poids; //recupere l'indice de l'arete, et son poids
            m_aretes[indiceTaille2]->setPoids(poids); //on associe le poids a l'arete
        }
        if ( ifs2.fail() )
            throw std::runtime_error("Probleme lecture donnees du graphe");
    }

    ifs2.close(); //fermeture du fichier
    return 0;
}

//verification de l'orientation du graphe
bool Graphe::Orientation()
{
    bool verif;

    if(m_orient == 0)
        verif = true;

    if(m_orient == 1)
        verif = false;

    return verif; //si le graphe est orienté, le sous programme renvoit la valeur 1, sinon 0
}

//affichage du fichier topologique
void Graphe::afficherG()const
{
    std::cout<<"\tfichier topologie\n";

    if (m_orient==0)
        std::cout<<"\nGrahe non oriente";
    else
    {
        std::cout<<"Graphe oriente";
    }

    std::cout<<"\nordre du graphe : "<< m_sommets.size();
    std::cout << "\nsommets :\n";
    for( auto s : m_sommets) //parcours de tous les sommets
    {
        //ecrit l'indice, la lettre et les coordonnées
        std::cout << "\t"<<s->getNum()<<" ";
        std::cout << s->getLettre()<<" ";
        std::cout << s->getX()<<" ";
        std::cout << s->getY()<<" ";
        std::cout << std::endl;
    }

    std::cout << "\ntaille du graphe : " << m_aretes.size();
    std::cout << std::endl;
    std::cout << "aretes :\n";
    for(auto s : m_aretes) //parcours de toutes les aretes
    {
        //ecrit l'indice de l'arete, et ses extremités (sommet)
        std::cout<<"\t"<<s->getIndice()<<" ";
        std::cout<<s->getExtrem1()->getNum()<<" ";
        std::cout<<s->getExtrem2()->getNum()<<" ";
        std::cout << std::endl;
    }
    std::cout<<std::endl;
}

//affichage du fichier de pondération
void Graphe::afficherPoids()const
{

    std::cout << "\n\tfichier de ponderation\n " << std::endl;
    std::cout << "\ntaille du graphe : " << m_aretes.size() << std::endl;
    for(auto s : m_aretes) //parcours de toutes les aretes
    {
        //ecrit l'indice des artes, l'indice des extremites de ses sommets, et leur poids
        std::cout << "\t" << s->getIndice() << " ";
        std::cout<<s->getExtrem1()->getNum()<<" ";
        std::cout<<s->getExtrem2()->getNum()<<" ";
        std::cout << "\t" << s->getPoids() << std::endl;
    }
    std::cout<<std::endl;
}

//affichage du parcours du plus court chemin (Dijkstra)
void Graphe::affichage(int arrive, double poids) const
{
    if(!m_sommets[arrive]->get_marque())
    {
        std::cout << "\nle point d'arrive n'est pas atteignable par ce point de depart. \n" << std::endl;
        return;
    }

    m_sommets[arrive]->afficher_result(); //on appelle la fonction pour afficher le parcours des sommets
    std::cout << " : poids total parcouru";

    std::cout <<  "= " << poids << std::endl; //affichage du poids total
}

//dessiner le graphe dans svgfile
void Graphe::dessinerGraphe()
{
    Svgfile svgout;
    svgout.addGrid(); //appelle la grille

    for(auto s : m_sommets) //parcours de tous les sommets
    {
        s->dessinerS(svgout); //appelle chaque sommet
    }

    for(auto s : m_aretes) //parcours de toutes les aretes
    {
        s->dessinerA(svgout, this); //appelle chaque arete
    }

    if (m_aretes[1]->getPoids()==0) // verification blindage
        std::cout <<"mais fichier ponderation non lu : poids = 0\n\n"<<std::endl;
}



///--- calculs ---///


//centralite de degré
void Graphe::c_degre()
{
    for(unsigned int i=0; i<m_sommets.size(); ++i) //parcours de tous les sommets
    {
        deg[i]=0; //initialise tous les degres des sommets à 0 à chaque fois qu'on change de sommet de "référence"
        for(unsigned int j=0; j<m_sommets.size(); ++j) //parcours de tous les sommets
        {
            if(m_sommets[i]->estAdjacentA(j) == true) //verifie si les sommets sont bien adjacents
            {
                deg[i]+=1; //si oui, on implémente le degré
            }
        }
    }

    //affichage et calcul pour le degré normalisé
    std::cout <<"\n\tINDICES CENTRALITE DEGRE / NORMALISE\n";
    for (unsigned int i=0; i<m_sommets.size(); ++i)//parcours de tous les sommets
    {
        std::cout << "\n\t\tsommet " << i <<" : "<< m_sommets[i]->getNbAdj() //affiche le nombre total d'adjacences
                  <<" et "<< (m_sommets[i]->getNbAdj())*(1.0/(m_ordre-1)); //affiche le nombre total d'adjacences divisé par l'odre -1
    }
    std::cout<<std::endl;
}

//centralite de vecteur propre
void Graphe::c_propre()
{
    double lambda=0,lambda_prec=1;
    std::vector < double > c;

    for (unsigned int j=0; j<m_sommets.size(); ++j) //parcours de tous les sommets pour initialiser les valeurs
    {
        cvp.push_back(1);
        c.push_back(0);
    }

    while(abs(lambda-lambda_prec)>0.01) //tant que la valeur absolue de la différence du lambda et de son précédent est grande
    {
        lambda_prec=lambda; //lambda précédent prend la valeur du lambda
        lambda = 0; //initialisation pour refaire les calculs
        for(unsigned int i=0; i<m_sommets.size(); ++i) //parcours des sommets
        {
            c[i]=0; //initialisation de c[i] (somme de tous les indices des voisins)
            for(unsigned int j=0; j<m_sommets.size(); ++j)//parcours des sommets
            {
                if(m_sommets[i]->estAdjacentA(j) == true)   //Voisin  i par rapport au sommet j
                {
                    c[i] = c[i] + cvp[j];
                }
            }
            lambda = lambda + (c[i]*c[i]);
        }

        lambda = sqrt(lambda);

        for(unsigned int i=0; i<m_sommets.size(); ++i) //parcours des sommets
        {
            cvp[i] = c[i] / lambda; //reprend toutes les valeurs calculées pour trouver notre cvp
        }

    }

    //affichage et calcul pour le vecteur propre normalisé et non normalisé
    std::cout<<"\n\tINDICES CENTRALITE VECTEUR PROPRE / NORMALISE :\n";
    for(unsigned int i=0; i<m_sommets.size(); ++i)
    {
        std::cout << "\n\t\tsommet " << i << " : "
                  << cvp[i] <<" et " <<(cvp[i]*(1.0/(m_ordre-1)));
    }
    std::cout<<std::endl;
}

//centralite de proximité
double Graphe::c_prox(int premier, int arrive)
{
    double p_poids=0; //initialisation

    auto cmp = [] (std::pair <Sommet*,double> p1, std::pair <Sommet*,double> p2) //compare 2 tableaux de pairs
    {
        return p2.second<p1.second; //return la valeur du plus petit poids des aretes des sommets adjacents
    };

    std::priority_queue <std::pair <Sommet*,double>, std::vector <std::pair <Sommet*,double>>, decltype(cmp) > file(cmp);

    file.push({m_sommets[premier],0}); //initialisation des poids

    for(auto m : m_sommets)
    {
        m->init_marque(); //initialisation de la couleur
    }


    while(!file.empty() && !m_sommets[arrive]->get_marque()) //tant que le fichier n'est pas vide et que le dernier sommet n'est pas marqué
    {
        Sommet* p=file.top().first; //ajoute un sommet au chemin

        for(unsigned int i=0; i<m_sommets.size(); i++)
        {
            if((p->estAdjacentA(i)) && (!m_sommets[i]->get_marque()))
            {
                std::pair <Sommet*,double> tampon = m_sommets[i]->get_voisin(p, file.top().second,m_aretes);
                file.push(tampon);
            }
        }
        p_poids = file.top().second;
        file.pop();     //Retire dernier élement de priority_queue
        p->marque();
    }
    return p_poids;
}

//affiche coord des extremites d'aretes
void Graphe::verification()
{
    for(unsigned int j=0; j<m_aretes.size(); ++j)
    {
        std::cout << std::endl;
        std::cout << m_aretes[j]->getExtrem1()->getX() << " " << m_aretes[j]->getExtrem1()->getY();
        std::cout << std::endl;
        std::cout << m_aretes[j]->getExtrem2()->getX() << " " << m_aretes[j]->getExtrem2()->getY();
        std::cout << std::endl;
    }
}

//calcul de la centralité de vecteur propre
void Graphe::calcul_cp (int i_debut, int i_fin)
{
    double p_poids=0;
    double cp=0, cpn=0;

    p_poids = c_prox(i_debut, i_fin);
    cp = 1/p_poids;
    cpn = (m_ordre-1)/p_poids;
    std::cout << std::endl;
    std::cout << "indice de proximite du sommet : " << i_debut << " a " << i_fin << " est " << cp << std::endl<<std::endl;
    std::cout << "indice de proximite normalise du sommet : " << i_debut << " a " << i_fin << " est " << cpn << std::endl<<std::endl;
}

//calcul centralité promixité automatisé pour tout sommet
void Graphe:: calcul_cp_auto()
{
    double p_poids=0;
    std::cout <<"\n\tINDICE CENTRALITE PROXIMITE / NORMALISE :\n";
    std::cout << std::endl;
    for(unsigned int i=0; i<m_sommets.size(); ++i)
    {
        for(unsigned int j=0; j<m_sommets.size(); ++j)
        {
            if(i!=j)
            {
                if ((m_sommets[i]->getNbAdj())==0)
                {
                    cp[i] = 0;
                    cpn[i] =0;
                }
                else
                {
                    p_poids = c_prox(i,j); //on recupere le poids total de c_prox
                    cp[i] = 1/p_poids;
                    cpn[i] = (m_ordre-1)/p_poids;
                }
                std::cout <<"\t\tsommet : "<< i << " au sommet : " << j << " = "
                          << std::setprecision(3)<<std::fixed << cp[i] << " et "<< cpn[i] << std::endl;
            }
        }
    }
    std::cout <<std::endl;
}


//centralite d'intermediarite
void Graphe::c_intermediarite()
{
    cint.reserve(m_sommets.size());
    cintn.reserve(m_sommets.size());

    for (unsigned int i=0;i<m_sommets.size();++i)
    {
        cint[i]=0;
        cintn[i]=((2*cint[i])/((m_ordre*m_ordre)-3*m_ordre+2));
    }

    //affichage et calcul pour le vecteur propre normalisé et non normalisé
    std::cout<<"\n\tINDICES CENTRALITE INTERMEDIARITE / NORMALISE :\n";
    for(unsigned int i=0; i<m_sommets.size(); ++i)
    {
        std::cout << "\n\t\tsommet " << i << " : "
                  << cint[i] <<" et " << cintn[i];
    }

    std::cout<<std::endl<<std::endl;
}


//calcul de la difference des indices entre 2 fichiers
void Graphe::calculDiff_indice (int f1, int f2) //recoit en parametre les numeros de fichiers à comparer
{
//Ciblage des fichiers textes

    std::string fichier1, fichier2;
    fichier1 = "sauvegarde_brut" + std::to_string(f1) + ".txt";
    fichier2 = "sauvegarde_brut" + std::to_string(f2) + ".txt";

    std::ifstream ifs1{fichier1}; //ouverture fichier 1
    if (!ifs1)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + fichier1 );

    //reserve de la place pour les données
    std::vector<double> indice1;
    indice1.reserve(m_sommets.size());
    std::vector<double> ideg1;
    ideg1.reserve(m_sommets.size());
    std::vector<double> idegn1;
    idegn1.reserve(m_sommets.size());
    std::vector<double> ivp1;
    ivp1.reserve(m_sommets.size());
    std::vector<double> ivpn1;
    ivpn1.reserve(m_sommets.size());
    std::vector<double> icp1;
    icp1.reserve(m_sommets.size());
    std::vector<double> icpn1;
    icpn1.reserve(m_sommets.size());
    std::vector<double> icint1;
    icint1.reserve(m_sommets.size());
    std::vector<double> icintn1;
    icintn1.reserve(m_sommets.size());

    //recuperer les valeurs du fichier 1
    for (unsigned int i=0; i<m_sommets.size(); ++i)
    {
        ifs1>> indice1[i] >> ideg1[i] >> idegn1[i] >> ivp1[i] >> ivpn1[i] >> icp1[i] >> icpn1[i] >> icint1[i] >> icintn1[i];
    }

    if ( ifs1.fail() )
        throw std::runtime_error("Probleme lecture données fichier 1");


    std::ifstream ifs2{fichier2}; //ouverture fichier 2
    if (!ifs2)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + fichier2 );

    //reserve de la place pour les données
    std::vector<double> indice2;
    indice2.reserve(m_sommets.size());
    std::vector<double> ideg2;
    ideg2.reserve(m_sommets.size());
    std::vector<double> idegn2;
    idegn2.reserve(m_sommets.size());
    std::vector<double> ivp2;
    ivp2.reserve(m_sommets.size());
    std::vector<double> ivpn2;
    ivpn2.reserve(m_sommets.size());
    std::vector<double> icp2;
    icp2.reserve(m_sommets.size());
    std::vector<double> icpn2;
    icpn2.reserve(m_sommets.size());
    std::vector<double> icint2;
    icint2.reserve(m_sommets.size());
    std::vector<double> icintn2;
    icintn2.reserve(m_sommets.size());

    //recuperer les valeurs du fichier 2
    for (unsigned int i=0; i<m_sommets.size(); ++i)
    {
        ifs2>> indice2[i] >> ideg2[i] >> idegn2[i] >> ivp2[i] >> ivpn2[i] >> icp2[i] >> icpn2[i]>> icint2[i] >> icintn2[i];
    }

    if ( ifs2.fail() )
        throw std::runtime_error("Probleme lecture donnees fichier2");

    //creation de vecteurs pour stocker les valeurs
    std::vector<double> dif_indice;
    dif_indice.reserve(m_sommets.size());
    std::vector<double> dif_ideg;
    dif_ideg.reserve(m_sommets.size());
    std::vector<double> dif_idegn;
    dif_idegn.reserve(m_sommets.size());
    std::vector<double> dif_ivp;
    dif_ivp.reserve(m_sommets.size());
    std::vector<double> dif_ivpn;
    dif_ivpn.reserve(m_sommets.size());
    std::vector<double> dif_icp;
    dif_icp.reserve(m_sommets.size());
    std::vector<double> dif_icpn;
    dif_icpn.reserve(m_sommets.size());
    std::vector<double> dif_icint;
    dif_icint.reserve(m_sommets.size());
    std::vector<double> dif_icintn;
    dif_icintn.reserve(m_sommets.size());

    //Calcul de différence des indices
    for (unsigned int i=0; i<m_sommets.size(); ++i)
    {
        dif_indice[i] = indice2[i]-indice1[i];
        dif_ideg[i] = ideg2[i]-ideg1[i];
        dif_idegn[i] = idegn2[i]-idegn1[i];
        dif_ivp[i] = ivp2[i]-ivp1[i];
        dif_ivpn[i] = ivpn2[i]-ivpn1[i];
        dif_icp[i] = icp2[i]-icp1[i];
        dif_icpn[i] = icpn2[i]-icpn1[i];
        dif_icint[i] = icint2[i]-icint1[i];
        dif_icintn[i] = icintn2[i]-icintn1[i];
    }

///Affichage des résultats de calculs de différence pour 1er sommet

    std::cout << "sommet / nom sommet / deg / degn / vp / vpn / cp / cpn / int / intn :\n";
    std::cout <<std::endl;
    for (unsigned int i=0; i<m_sommets.size(); ++i)
    {
        std::cout << "sommet : "<< i <<" : "<< m_sommets[i]->getLettre()<< " -> "
                  << "  " << dif_ideg[i]
                  << "  "<< dif_idegn[i]
                  << "  "<< dif_ivp[i]
                  << "  "<< dif_ivpn[i]
                  << "  "<< dif_icp[i]
                  << "  "<< dif_icpn[i]
                  << "  "<< dif_icint[i]
                  << "  "<< dif_icintn[i]<<std::endl
                  <<std::endl;
    }

}




//calcul du BFS
void Graphe::BFS(int premier)
{
    std::vector<int> i_preds(m_sommets.size());
    int i;

    //initalisation à 99 pour voir lesquels vont être parcourus ou non
    for (size_t i=0; i<i_preds.size(); ++i)
        i_preds[i]=99;

    //initialisation des couleurs à blanc
    for (auto it : m_sommets)
        it->reinitialiserCouleur();

    std::queue<Sommet*> file;
    file.push(m_sommets[premier]); //enfile le premier
    m_sommets[premier]->setCouleur(1); //on met le premier en gris

    //parcours
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

    //affichage
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

//calcul DFS
void Graphe::DFS(int premier)
{
    std::map<int, int> i_preds;

    //mets les sommets en blancs
    for (auto it : m_sommets)
        it->reinitialiserCouleur();

    //parcours
    recuDFS(i_preds,m_sommets[premier]);


    //affichage
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

std::cout << std::endl << std::endl;

}

//calcul du chemin pour le DFS
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

//recherche des composantes connexes
void Graphe::recherchecompoConnexes()
{
    int nbCompo=0;
    bool stop = false;
    std::map<int, int> i_preds; //liste des prdecesseurs pour le DFS
    std::map<int,std::vector<int>> compoConnexes; //numéro et identidfiant des sommets de chaque composante

    //mets les sommets en blanc
    for (auto it : m_sommets)
        it->reinitialiserCouleur();

    //recherche de composante de sommets
    do
    {
        stop=false;
        for (auto it : m_sommets)
        {
            if (it->getCouleur()!=2 && !stop)
            {
                //si on découvre un nouveau sommet qui n'a pas encore été rangé dans une composante connexe
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

    int k=0;

    //affichage
    for (auto it : compoConnexes)
    {
        std::cout<<std::endl<<" Composante connexe "<<it.first<<" : ";
        for (auto et : it.second)
            std::cout<<et<<" ";
        k++;
    }
    std::cout << std::endl << std::endl << " Le graphe a " << k << " composante(s) connexe(s)." << std::endl;
    std::cout << std::endl;
}

//k-connexité
void Graphe::connexite()
{
    if (m_orient== 1)
        std:: cout << "On ne peut pas calculer la k-connexite car le graphe est oriente."<< std::endl<< std::endl;

    else
    {
    int k,tot_chemin;
    k=99999;

    for(unsigned int i=0;i<m_sommets.size();++i)
    {
        for(unsigned int j=0;j<m_sommets.size();++j)
        {
            if(i!=j) //parcours des sommets i par rapport au sommet j s'ils sont différents
            {
                for(unsigned int m=0;m<m_sommets.size();++m)
                {
                    m_sommets[m]->setCouleur(0); //remet le sommet en blanc
                }

                tot_chemin = 0; //initialisation chemin total
                m_sommets[i]->connexite(j,tot_chemin);

                if(tot_chemin<k)
                {
                    k=tot_chemin; //implementation de k
                }
            }
        }
    }

    //Affichage
    std::cout << "\n\tK-CONNEXITE\n Enlever " << k << " arete(s) pour former au moins 2 composantes connexes.";
    std::cout << std::endl << std::endl;
    }
}

//recuperer l'indice du sommet
Sommet* Graphe::recupSommet (int indice)
{
    return m_sommets[indice];
}





//sauvegarde de tous les indices dans fichier
void Graphe::sauvegarde(int s)
{
    //creation d'une nouvelle sauvegarde
    std::string fichier;
    fichier = "sauvegarde" + std::to_string(s) +".txt";
    std::cout<<"\tsauvegarde des indices ok\n";
    std::ofstream ofs(fichier);
    if (!ofs)
        throw std::runtime_error( "Impossible d'écrire la sauvegarde car fichier inexistant ");
    else //ecriture dans la sauvegarde
    {
        ofs<<"\t INDICES"<<std::endl;
        ofs<< std::endl;
        ofs<<"Ordre des indices bruts et normalisés : \n\tcentralité de degré /centralité de vecteur propre / centralité de proximité / centralité intermediarité"<<std::endl<<std::endl;
        for (unsigned int i=0; i<m_sommets.size(); ++i)
            ofs<< "sommet " << i << " : "
               << deg[i]<<"   "<< (deg[i]*(1.0/(m_ordre-1)))
               <<"\t"<< cvp[i]<<"   "<< (cvp[i]*(1.0/(m_ordre-1)))
               <<"\t\t\t"<< cp[i] <<"   "<< cpn[i]
               <<"\t\t"<< cint[i] <<"   "<< cintn[i]<< std::endl;
        ofs << std::endl;
    }

    ///---------------------------------------------------------------///

    //creation d'une nouvelle sauvegarde
    std::string fichier_brut;
    fichier_brut = "sauvegarde_brut" + std::to_string(s) +".txt";
    std::ofstream ofs2(fichier_brut);
    if (!ofs2)
        throw std::runtime_error( "Impossible d'écrire la sauvegarde car fichier inexistant ");

    else //ecriture dans la sauvegarde
    {
        for (unsigned int i=0; i<m_sommets.size(); ++i)
            ofs2
                    << i << " " << deg[i]<< " " << (deg[i]*(1.0/(m_ordre-1)))
                    << " " << cvp[i]<< " " << (cvp[i]*(1.0/(m_ordre-1)))
                    << " " << cp[i] <<" "<< cpn[i]
                    << " " << cint[i]<<" "<< cintn[i]<<std::endl;
        ofs2 << std::endl;
    }
}

//Supprimer une ou plusieurs aretes
void Graphe::supp_arete()
{
    int indice=0;
    int nombre=0;
    std::cout<< "\nles aretes sont :\n";
    for(auto s : m_aretes)
    {
        std::cout<<"\t"<<s->getIndice()<<" ";
        std::cout<<s->getExtrem1()->getLettre()<<"  ";
        std::cout<<s->getExtrem2()->getLettre()<<"  ";
        std::cout<<s->getPoids();
        std::cout << std::endl;
    }


    std::cout<<std::endl << "Combien d'aretes voulez-vous supprimer ?" <<std::endl;
    std::cin >> nombre; //demande à l'utilisateur combien d'aretes il veut supprimer

    for (int i=0; i<nombre; ++i)
    {
        std::cout << std::endl << "Arete a supprimer : ";
        std::cin >> indice;

        for (unsigned int j=0; j<m_aretes.size(); ++j) //parcours des aretes pour supprimer la demander
        {
            if (indice == m_aretes[j]->getIndice())
            {
                delete m_aretes[indice]; //suppression l'indice de l'arete
                m_aretes.erase(m_aretes.begin()+indice); //suppression de l'aretes
            }
        }

    }

    //affichage des aretes restantes
    std::cout << "\nles aretes sont donc :\n";
    for(auto s : m_aretes)
    {
        std::cout<<"\t"<<s->getIndice()<<" ";
        std::cout<<s->getExtrem1()->getLettre()<<" ";
        std::cout<<s->getExtrem2()->getLettre()<<" ";
        std::cout<<s->getPoids();
        std::cout << std::endl;
    }

}
