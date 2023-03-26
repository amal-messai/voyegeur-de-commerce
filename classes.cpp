#include "class.h"
#include <iostream>
#include <string>
#include <cstdlib> // for rand() and srand()
#include <algorithm>
#include <vector>
using namespace std;
// constructeur de graphe
graphe::graphe(int n)
{
    dim=n;
    tab =new double*[n];
    for (int i=0;i<dim;i++)
    {
        tab[i]=new double [dim];
    }
}
// destructeur de graphe
graphe::~graphe()
{
    if (tab!=0) delete [] tab;
    dim=0;
}

// constructeur d'individu
individu::individu(int n)
{
    this->dim=n;
    this->indiv= new double [dim];
}
individu::individu(const individu& v)
{
    dim=v.dim;
    indiv= new double [dim];
    for (int i=0; i<dim;i++)
    {
        indiv[i]=v.indiv[i];
    }
}
// destructeur d'individu
chemin::~chemin()
{
    if (indiv!=0) delete [] indiv;
    if (poids!=0) delete [] poids;
    dim=0;
}

double chemin::adapt () const
{
    double s=0;
    for (int i =0;i<dim; i++)
        s+=poids[i];
    return s;
}

void chemin::affiche()
{
    cout<<"affichage du poids";
    for (int i=0;i<dim-1;i++)
        cout<< poids[i]<<",";
    cout<<poids[dim-1];
    cout<<"\n"<<"affichage de l'individu"<<"\n";
    for (int i=0;i<dim-1;i++)
        cout<< indiv[i]<<",";
    cout<<indiv[dim-1];

}

// class population et ses fonctionalités
population::population(int n)
{
    nbre=n;
    pop.resize(n);
}
population::population(const population& other)
{
    nbre=other.nbre;
    pop.resize(other.pop.size());
    int i = 0;
    for (const auto& ch : other.pop) {
        pop[i] = ch;
        ++i;
    }
}

population::~population()
{
    pop.clear();
    nbre=0;
}

chemin mutation (chemin ch )
{
    int l = rand() % (ch.dim);
    int k = rand() % (ch.dim);
    if (l<k)
    {
        int c=k;
        k=l;
        l=c;
    }
    double c1=ch.indiv[l];
    double c2=ch.indiv[k];
    ch.indiv[l]=c2;
    ch.indiv[k]=c1;
    c1=ch.indiv[k+1];
    c2=ch.indiv[l-1];
    ch.indiv[k+1]=c2;
    ch.indiv[l-1]=c1;
    return ch ;
}

chemin selec_roulette(population pop)
{
    double s=0;
    for (int i=0;i<pop.nbre;i++) s+=pop[i].adapt();
    double r = (double)rand() / RAND_MAX * s;
    int i=0; double sum=pop[0].adapt();
    while( (i<pop.nbre)&& (sum<r) )
    {
        i+=1;
        sum+=pop[i].adapt();
    }
    return pop [i];
}

 chemin selec_rang(const population& popu)
{
      population pop_copie(popu);
      std::sort(pop_copie.pop.begin(), pop_copie.pop.end(),[]( const chemin&a, chemin&b){ return a.adapt()>b.adapt();});
      double s=0;
      for (int i=0;i<pop_copie.nbre;i++) s+=i+1;
      double r = (double)rand() / RAND_MAX * s;
      int i=0; double sum=1;
      while( (i<pop_copie.nbre)&& (sum<=r) )
        {
        i+=1;
        sum+=i+1;
      }
    return pop_copie.pop.at(i);
}
