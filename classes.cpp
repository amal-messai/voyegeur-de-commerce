#include "class.h"
#include <iostream>
#include <string>
#include <cstdlib> // for rand() and srand()
#include <algorithm>
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

double chemin::adapt ()
{
    double s=0;
    for (int i =0;i<dim; i++)
        s+=poids[i];
    return s;
}
individu::individu()
{
    dim=taille;
    indiv=new double [dim];
}
// class population et ses fonctionalités
population::population(int n)
{
    nbre=n;
    pop=new chemin[nbre];
}
population::population(const population& other)
{
    nbre=other.nbre;
    pop=new chemin[other.nbre];
    for(int i=0;i<nbre;i++) pop[i]=other.pop[i];

}
population::~population()
{
    if (pop!=0) delete[] pop;
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
    while( (i<pop.nbre)&& (sum<=r) )
    {
        i+=1;
        sum+=pop[i].adapt();
    }
    return pop [i];
}

 chemin selec_rang(population popu)
{
      bool comparator(const chemin&a, const chemin&b)
      {
          return a.adapt()> b.adapt();
      }
      population pop_copie(popu);
      std::sort(pop_copie.pop, pop_copie.pop+ popu.nbre, comparator);
      double s=0;
      for (int i=0;i<pop_copie.nbre;i++) s+=i+1;
      double r = (double)rand() / RAND_MAX * s;
      int i=0; double sum=1;
      while( (i<pop_copie.nbre)&& (sum<=r) )
        {
        i+=1;
        sum+=i+1;
      }
    return pop_copie [i];
}
