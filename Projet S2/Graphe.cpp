#include "graphe.h"
#include "svgfile.h"
#include "couleur.h"
#include "util.h"
#include <cmath>
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
        m_aretes.push_back(new Arete {j,m_sommets[nb1],m_sommets[nb2]});
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

void Graphe::lectureFichierP()
{
    std::cout<<"Quel fichier ponderation souhaitez-vous lire?\n";
    std::string fichier2;
    std::cin>>fichier2;
    std::ifstream ifs2{"p_" + fichier2 + ".txt"}; //ouverture en mode lecture
    if (!ifs2)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + fichier2 );

    int nbr_arete;
    ifs2 >> nbr_arete;
    if ( ifs2.fail() )
        throw std::runtime_error("Probleme lecture nombre d'arete du graphe");

    int indiceTaille2;
    double poids;
    for(int k=0; k<nbr_arete; k++)
    {
        ifs2>>indiceTaille2>>poids;
        m_aretes[indiceTaille2]->setPoids(poids);
    }
    if ( ifs2.fail() )
        throw std::runtime_error("Probleme lecture donnees du graphe");

    ifs2.close();
}


void Graphe::afficherG()const
{
    std::cout<<"\tfichier topologie\n";

    if (m_orient==0)
        std::cout<<"\nGrahe non oriente";
    else
        std::cout<<"Graphe oriente";

    std::cout<<" d'ordre : "<< m_sommets.size();
    std::cout << std::endl;

    std::cout << "\nsommets :\n";
    for( auto s : m_sommets)
    {
        std::cout << "\t"<<s->getNum()<<" ";
        std::cout << s->getLettre()<<" ";
        std::cout << s->getX()<<" ";
        std::cout << s->getY()<<" ";
        std::cout << std::endl;
    }

    std::cout << "\ntaille : " << m_aretes.size();
    std::cout << std::endl;
    std::cout << "aretes :\n";
    for(auto s : m_aretes)
    {
        std::cout<<"\t"<<s->getIndice()<<" ";
        std::cout<<s->getExtrem1()->getNum()<<" ";
        std::cout<<s->getExtrem2()->getNum()<<" ";
        std::cout << std::endl;
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
        std::cout << "\t" << s->getPoids() << std::endl;
    }

    std::cout << "\n\nAsssociation 2 fichiers :\n";
    for(auto s : m_aretes)
    {
        std::cout<<"\t"<<s->getIndice()<<" ";
        std::cout<<s->getExtrem1()->getNum()<<" ";
        std::cout<<s->getExtrem2()->getNum()<<" ";
        std::cout<<s->getPoids();
        std::cout << std::endl;
        std::cout << std::endl;
    }
}


void Graphe::c_degre()
{
    for (unsigned int i=0; i<m_sommets.size(); ++i)
    {
        std::cout << "sommet " << i << " indice de centralite : " << deg[i] << std::endl;
        std::cout << "sommet " << i << " indice de centralite normalise: " << (deg[i]*(1.0/(m_ordre-1))) << std::endl;
        std::cout<<std::endl;
    }
}

void Graphe::c_propre()
{
    double lambda=0,lambda_prec=1;
    std::vector < double > c;

    for (unsigned int j=0; j<m_sommets.size(); ++j)
    {
        cvp.push_back(1);
        c.push_back(0);
    }

    while(abs(lambda-lambda_prec)>0.01)
    {
        lambda_prec=lambda;
        lambda = 0;
        for(unsigned int i=0; i<m_sommets.size(); ++i)
        {
            c[i]=0;
            for(unsigned int j=0; j<m_sommets.size(); ++j)
            {
                if(m_sommets[i]->estAdjacentA(j) == true)   //Voisin  i par rapport au sommet j
                {
                    c[i] = c[i] + cvp[j];
                }
            }
            lambda = lambda + (c[i]*c[i]);
        }

        lambda = sqrt(lambda);

        for(unsigned int i=0; i<m_sommets.size(); ++i)
        {
            cvp[i] = c[i] / lambda;
        }

    }
    for(unsigned int i=0; i<m_sommets.size(); ++i)
    {
        //std::cout << cvp[i] << std::endl;

        std::cout << "sommet " << i << " indice de centralite : " << cvp[i] << std::endl;
        std::cout << "sommet " << i << " indice de centralite normalise: " << (cvp[i]*(1.0/(m_ordre-1))) << std::endl;
        std::cout<<std::endl;
    }
}


void Graphe::verification() ///affiche coord des extremites d'aretes
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

void Graphe::sauvegarde()
{
    std::ofstream ofs("sauvegarde.txt");
    if (!ofs)
        throw std::runtime_error( "Impossible d'écrire la sauvegarde car fichier inexistant ");
    else
    {
        ofs<<"\t INDICES"<<std::endl;
        ofs<< std::endl;

        ofs<<" Centralité de degré :\n";
        for (unsigned int i=0; i<m_sommets.size(); ++i)
            ofs<< "sommet " << i << " : " << deg[i]<<std::endl;
        ofs<< std::endl;

        ofs<<" Centralité de degré normalisé :\n";
        for (unsigned int i=0; i<m_sommets.size(); ++i)
            ofs<< "sommet " << i << " : " << (deg[i]*(1.0/(m_ordre-1)))<<std::endl;
        ofs<< std::endl;

        ofs<< "Centralite de vecteur propre:\n";
        for (unsigned int i=0; i<m_sommets.size(); ++i)
            ofs << "sommet" << i <<" : " << cvp[i]<<std::endl;
        ofs<< std::endl;

        ofs<<" Centralité de vecteur propre normalisé :\n";
        for (unsigned int i=0; i<m_sommets.size(); ++i)
            ofs<< "sommet " << i << " : " << (cvp[i]*(1.0/(m_ordre-1)))<<std::endl;
        ofs<< std::endl;

        ofs<<"Centralité de vecteur de proximité :\n";
        for (unsigned int i=0; i<m_sommets.size(); ++i)
            ofs << " sommet : " << i << " : " << cp[i] << std::endl<< std::endl;

        ofs<<"Centralité de vecteur de proximité normalisé:\n";
        for (unsigned int i=0; i<m_sommets.size(); ++i)
            ofs << "sommet : " << i << " : " << cpn[i] << std::endl;
    }

}


void Graphe::dessinerGraphe() const ///sp permet de dessiner le graphe dans svgfile
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

double Graphe::c_prox(int premier, int arrive)
{
    double p_poids=0;

    auto cmp = [] (std::pair <Sommet*,double> p1, std::pair <Sommet*,double> p2)
    {
        return p2.second<p1.second;
    };

    std::priority_queue <std::pair <Sommet*,double>, std::vector <std::pair <Sommet*,double>>, decltype(cmp) > file(cmp);

    file.push({m_sommets[premier],0});

    for(auto m : m_sommets)
    {
        m->init_marque();
    }


    while(!file.empty() && !m_sommets[arrive]->get_marque())
    {
        Sommet* p=file.top().first;

        for(int i=0; i<m_sommets.size(); i++)
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

void Graphe::affichage(int arrive, double poids) const
{
    if(!m_sommets[arrive]->get_marque())
    {
        std::cout << "\nle point d'arrive n'est pas atteignable par ce point de depart. \n" << std::endl;
        return;
    }

    m_sommets[arrive]->afficher_result();

    std::cout << " : poids total parcouru";

    std::cout <<  "= " << poids << std::endl;
}


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

void Graphe:: calcul_cp_auto()
{

    double p_poids=0;
    cp.push_back(m_sommets.size());
    cpn.push_back(m_sommets.size());


    for(unsigned int i=0; i<m_sommets.size(); ++i)
    {
        for(unsigned int j=0; j<m_sommets.size(); ++j)
        {
            if(i!=j)
            {
                p_poids = c_prox(i,j); //on recupere le poids total de c_prox
                cp[i] = 1/p_poids;
                cpn[i] = (m_ordre-1)/p_poids;
                std::cout << std::endl;
                std::cout <<"indice de proximite :\n";
                std::cout << i << " a " << j << " : " << cp[i] << std::endl;
                std::cout << "indice de proximite normalise:\n";
                std::cout << i << " a " << j << " : " << cpn[i] << std::endl<<std::endl;
            }
        }
    }
}

Graphe::~Graphe()
{
    for (auto it : m_sommets)
        delete it;
}


/*-------------------------------*/

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

