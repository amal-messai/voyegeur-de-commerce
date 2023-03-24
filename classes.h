#ifndef CLASSES_H_INCLUDED
#define CLASSES_H_INCLUDED

#include <iostream>
#include <string>

using namespace std;

class point
{
    float x ;
    float y ;
    point(float a, float b): x(a), y(b) {};
};
class graphe ;
{
public :
    int dim;
    double** tab;
    graphe( int n )
    ~graphe();
    double val (int i , int j) {return tab[i][j]};
    void affiche();
};

class ville
{
public:
    string nom;
    point coord;
    ville (string a , point  p ) : nom(a), coord (p){};

};

class individu
{
public:
    int dim;
    double* indiv;
    double* poids;
    individu(int n);
    virtual individu (individu v)
    ~individu();
    virtual double adapt();

};
class chemin : public individu
{
public:
    chemin(int n) : individu (n) {};
    chemin (chemin v);
    double adapt ();

};
class population
{
public:
    int nbre;
    chemin* pop;
    population (int n );
    chemin operator[] (int i ) {return chemin[i] };

};
chemin mutation (chemin ch)  ;
population* selection_prod (pipulation pop, string select);


