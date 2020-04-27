#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED

#include <iostream>
#include <vector>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <map>


class Sommet
{
private :
    int m_num;
    int m_marquage;
    std::map<Sommet*,int> m_adjacents; //sommet et poids

public :
    Sommet (int num);
    int getNum ()const;
    void afficher ()const;
    void remplir(Sommet* adjacent, int poids);
    void setMarquage(int nv);
    int getMarquage()const;
    bool estAdjacentA(int i);
    int getDist(int i);

};


#endif // SOMMET_H_INCLUDED
