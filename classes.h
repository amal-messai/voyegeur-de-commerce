#ifndef CLASS_H_INCLUDED
#define CLASS_H_INCLUDED
#include <iostream>
#include <string>
#include <vector>
#include <functional>
using namespace std;
class point
{
    float x ;
    float y ;
    point(float a, float b): x(a), y(b) {};
    point(const point& A):x(A.x), y(A.y){};
};
class graphe
{
public :
    int dim;
    int** tab;
    graphe( int n );
    ~graphe();
    int val (int i , int j) const {return tab[i][j];};
    void affiche();
};

class ville
{
public:
    string nom;
    point coord;
    //ville (string a ,const point&  p ) : nom(a), coord (p){};

};


class individu
{
public:
    int dim;
    int* indiv;
    individu(int n);
    individu  (const individu& v);
    individu()=default ;// default constructor
    virtual~individu(){};
    virtual int adapt(const graphe& G) const =0;
    virtual bool in(int k)=0;

};
class chemin : public individu
{
public:
    chemin(): individu(){};
    chemin(int n) : individu(n) {} ;
    chemin (const chemin& other) : individu(other) {};
    int adapt (const graphe& G) const ;
    ~chemin();
    chemin& operator =(const chemin&other);
    bool in(int k);
    void affiche();
};

class population
{
public:
    int nbre;
    vector <chemin> pop;
    population (int n );
    population(const population& other);
    ~population();
    chemin& operator[] (int i ) {return pop.at(i);};
    operator =(const population& other);
    void affiche();

};
chemin mutation (chemin ch, graphe G)  ;
// méthodes de séléction des reproducteurs
chemin selec_roulette(population pop, graphe G);
chemin selec_rang(const population& pop, graphe G );
population selec_tournoi(const population &gen,graphe G);


// méthode de sélection de next generation
bool compare_by_adapt_asc(const chemin& A,const chemin& B, graphe G);
bool compare_by_adapt_desc(const chemin& A,const chemin& B, graphe G);
population selec_reproducteurs(population pop_initi,graphe G, std::string selection_method);
population selection_nextgen(population pop_prod, int q, graphe G);
population gen_init(graphe G,int taille, int k);

#endif CLASS_H_INCLUDED


