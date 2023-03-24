#include "classes.h"
#include <iostream>
#include <string>

using namespace std;
// constructeur de graphe
graphe::graphe(int n)
{
    dim=n;
    tab =new double*[n];
    for (int i=0;i<dim,i++)
    {
        tab[i]=new double [dim];
    }
    return this;
}
// distructeur de graphe
graphe::~graphe()
{
    if (tab!=0) delete [] tab;
    dim=0;
}

// constructeur d'individu
individu::individu(int n)
{
    this.dim=n;
    this->indiv= new double [dim];
    this->poids= new double [dim];
    return this
}
// distructeur d'individu
individu::~individu()
{
    if indiv!=0 delete [] indiv;
    if poids!=0 delete [] poids;
    dim=0;

}
chemin::chemin(chemin v)
{
    chemin(v.dim);
    for (int i=0; i<dim;i++)
    {
        indiv[i]=v.indiv[i];
        poids[i]=v.poids[i];
    }
    return this
}
double individu::adapt ()
{
    double s=0;
    for (int i =0;i<dim; i++)
        s+=poids[i];
    return s;
}
chemin mutation (chemin ch )
{
    int l= (int)((float)rand() * (chemin.dim+1) / (RAND_MAX-1)) ;
    int k= (int)((float)rand() * (chemin.dim+1) / (RAND_MAX-1)) ;
    if l<k
    {
        int c=k;
        k=l;
        l=k;
    }
    double c1=ch.indiv[l];
    double c2=ch.indiv[k];
    ch.indiv[l]=c2;
    ch.indiv[k]=c1;
    c1=ch.indiv[k+1];
    c2=ch.indiv[l-1];
    ch.indiv[k+1]=c2;
    ch.indiv[l-1]=c1;
    return chemin ;

}
chemin* selection_prod(population population, string select)
{
    population pop_prod= population(pop.chemin.dim)
    if strcmp(select, "roulette")==0;
    {
        double s=0 ;
        for (i=0;i<pop.nbre; i++)
        {
            chemin ch=pop.chemin[i];
            s+=ch.adapt;
        }

    }
}
