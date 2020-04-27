#include "Arete.h"

Arete::Arete (int indice, int indice2, int poids,int extrem1, int extrem2)
    :m_indice{indice},m_indice2{indice2}, m_poids{poids}, m_extrem1{extrem1},m_extrem2{extrem2}
    {}
    int Arete::getIndice ()const
    {
        return m_indice;
    }
    int Arete::getIndice2()const
    {
        return m_indice2;
    }

    int Arete::getPoids () const
    {
        return m_poids;
    }

    int Arete::getExtrem1 ()const
    {
        return m_extrem1;
    }
     int Arete::getExtrem2 ()const
    {
        return m_extrem2;
    }

