#ifndef CLASS_H_INCLUDED
#define CLASS_H_INCLUDED
#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <memory>

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
    int val (int i , int j) const ;
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
    vector<int> indiv;
    individu(int n);
    individu  (const individu& v);
    individu()=default ;// default constructor
    virtual~individu() =default;
    virtual int adapt( const graphe& G) const =0;
    virtual bool in(int k)=0;

};
class chemin : public individu
{
public:
    chemin(): individu(){};
    chemin(int n) : individu(n) {} ;
    chemin (const chemin& other) : individu(other){};
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
    void sort_by_adapt_asc(const graphe& G);
    void sort_by_adapt_desc(const graphe& G);
    vector <chemin> pop;
    population (int n );
    population(const population& other);
    ~population();
    chemin& operator[] (int i ) {return pop.at(i);};
    population& operator =(const population& other);
    void affiche();

};
chemin mutation (chemin ch, const graphe& G)  ;
// méthodes de séléction des reproducteurs
chemin selec_roulette(const population& P, const graphe& G);
chemin selec_rang(const population& P, const graphe& G );
population selec_tournoi(const population &gen,const graphe& G);


// méthode de sélection de next generation
bool compare_by_adapt_asc(const chemin& A,const chemin& B, const graphe& G);
bool compare_by_adapt_desc(const chemin& A,const chemin& B, const graphe& G);
population selec_reproducteurs( const population& pop_initi,const graphe& G, const char* selection_method);
population selection_nextgen(population pop_prod,population pop_init, int q, const graphe& G);
population gen_init(const graphe& G,int taille, int k);

#endif CLASS_H_INCLUDED


