#include "couleur.h"
#include "svgfile.h"
#include "util.h"
#include <iostream>

/// fichier couleur.cpp tiré de correction TP 6 maillage de M FERCOQ repris integralement

Couleur::Couleur(uint8_t rouge, uint8_t vert, uint8_t bleu)
    : m_rouge{rouge}, m_vert{vert}, m_bleu{bleu}
{ }


Couleur::Couleur()
    : Couleur(0, 0, 0) // Délégation de constructeur
{ }


void Couleur::afficher() const
{
    std::cout << "(" << (int)m_rouge << ", " << (int)m_vert << ", " << (int)m_bleu << ")" << std::endl;
}

uint8_t saisirCanal()
{
    int val;
    std::cin >> val;
    while (val<0 || val>255)
    {
        std::cout << "Mauvaise valeur couleur, recommencer : ";
        util::videCin();
        std::cin >> val;
    }

    return (uint8_t)val;
}

void Couleur::setCouleur(uint8_t red, uint8_t green, uint8_t blue)
{
    m_rouge=red;
    m_vert=green;
    m_bleu=blue;
}

void Couleur::saisir()
{
    std::cout << "Veuillez saisir rouge vert et bleu SVP : ";
    m_rouge = saisirCanal();
    m_vert = saisirCanal();
    m_bleu = saisirCanal();
}

Couleur::operator std::string() const
{
    return Svgfile::makeRGB(m_rouge, m_vert, m_bleu);
}
