#ifndef CMP_H_INCLUDED
#define CMP_H_INCLUDED


#include <vector>
#include <queue>
#include <iostream>
#include <fstream>
#include <string>

class Sommet;
auto cmp = [] (std::pair <Sommet*,int> p1, std::pair <Sommet*,int> p2)
{return p2.second<p1.second;};


#endif // CMP_H_INCLUDED
