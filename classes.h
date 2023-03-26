#ifndef CLASSE_H_INCLUDED
#define CLASSE_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
using namespace std;
class point
{
    float x ;
    float y ;
    point(float a, float b): x(a), y(b) {};
};
class graphe
{
public :
    int dim;
    double** tab;
    graphe( int n );
    ~graphe();
    double val (int i , int j) {return tab[i][j];};
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
    individu(int n);
    individu  (const individu& v);
    individu()=default;// default constructor
    virtual~individu(){};
    virtual double adapt()=0;

};
class chemin : public individu
{
public:
    double* poids;
    chemin(): individu() {};
    chemin(int n) : individu(n), poids(new double[n]) {} ;
    chemin (const chemin& other) : individu(other), poids(new double[other.dim]) {
        for (int i = 0; i < dim; i++) {
            poids[i] = other.poids[i];
        }
    }
    double adapt ();
    ~chemin();
};
class population
{
public:
    int nbre;
    vector<chemin> pop;
    population (int n );
    population(const population& other);
    ~population();
    chemin& operator[] (int i ) {return pop[i];};

};
chemin mutation (chemin ch)  ;
population* selection_prod (population pop, string select);
// méthodes de séléction des reproducteurs
chemin selec_roulette(population pop);
chemin selec_rang(population pop);

#endif CLASSE_H_INCLUDED


