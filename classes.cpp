#include "class.h"
#include <iostream>
#include <string>
#include <cstdlib> // for rand() and srand()
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;
// Class graphe
graphe::graphe(int n)
{
    dim=n;
    tab =new int*[n];
    for (int i=0;i<dim;i++)
    {
        tab[i]=new int [dim];
    }
}

graphe::~graphe()
{
    if (tab!=0) delete [] tab;
    dim=0;
}
void graphe::affiche()
{
    for (int i=0;i<dim;i++)
    {
        for (int j=0;j<dim-1;j++)
            cout<<tab[i][j]<<",";
        cout<<tab[i][dim-1];
        cout<<"\n";

    }
}
//Class individu
individu::individu(int n)
{
    this->dim=n;
    this->indiv= new int [dim];
}
individu::individu(const individu& v)
{
    dim=v.dim;
    indiv= new int [dim];
    for (int i=0; i<dim;i++)
    {
        indiv[i]=v.indiv[i];
    }
}
// destructeur d'individu
chemin::~chemin()
{
    if (indiv!=0) delete [] indiv;
    dim=0;
}

int chemin::adapt (graphe G) const
{
    int s=G.val(G.dim-1,0);
    for (int i =0;i<dim-1; i++)
        s+=G.val(indiv[i],indiv[i+1]);
    return s;
}

void chemin::affiche()
{
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
    int c1=ch.indiv[l];
    int c2=ch.indiv[k];
    ch.indiv[l]=c2;
    ch.indiv[k]=c1;
    c1=ch.indiv[k+1];
    c2=ch.indiv[l-1];
    ch.indiv[k+1]=c2;
    ch.indiv[l-1]=c1;
    return ch ;
}
bool compare_by_adapt_asc(const chemin& A,const chemin& B, graphe G)
{
    return A.adapt(G)<B.adapt(G);
}
bool compare_by_adapt_desc(const chemin& A,const chemin& B, graphe G)
{
    return A.adapt(G)>B.adapt(G);
}

chemin selec_roulette(population pop, graphe G )
{
    int s=0;
    for (int i=0;i<pop.nbre;i++) s+=pop[i].adapt(G);
    int r = rand() % (s);
    int i=0; int sum=pop[0].adapt(G);
    while( (i<pop.nbre)&& (sum<r) )
    {
        i+=1;
        sum+=pop[i].adapt(G);
    }
    return pop [i];
}

 chemin selec_rang(const population& popu, graphe G)
{

      population pop_copie(popu);
       sort(pop_copie.pop.begin(), pop_copie.pop.end(), [&](const chemin& A, const chemin& B) {
        return compare_by_adapt_asc(A, B, G);
    });
      int s=0;
      for (int i=0;i<pop_copie.nbre;i++) s+=i+1;
      int r = rand() % (s);
      int i=0; int sum=1;
      while( (i<pop_copie.nbre)&& (sum<=r) )
        {
        i+=1;
        sum+=i+1;
      }
    return pop_copie.pop.at(i);
}
population selec_tournoi(const population &gen,graphe G, double p)
{
    int n=gen.nbre;
    population pop_tournoi=population(n);
    for(int i=0; i<n, i++)
    {
        int j=rand()%n;
        int k=rand()%n;
        chemin p1(gen.pop[j]);
        chemin p2(gen.pop[k]);
        double proba1,proba2;
        if p1.adapt(G)<p2.adapt(G) 
        {
            proba1=p;
            proba2=1-p;
        }
        else
        {
            proba2=p;
            proba1=1-p;
        }
        double proba=rand() / (double)RAND_MAX;
        if (proba<proba1) pop_tournoi[i]=p1;
        else pop_tournoi[i]=p2;
        
    }
    return pop_tournoi;
}
        
population selec_reproducteurs(population pop_initi,graphe G,std::function<chemin(const population&, graphe)> selection_method)
{
    population pop_prod (pop_initi.nbre);
    for (int i=0;i<pop_initi.nbre;i++)
    {
        chemin indiv_selected=selection_method(pop_initi,G);
        pop_prod[i]=indiv_selected;
    }
        return(pop_prod);
}

population selection_nextgen(population pop_prod, int q, graphe G)
{

    int n=pop_prod.nbre;
    population next_gen=population(n);
    for (int i=0;i<n;i+=2)
    {
        //crossover
        int j= rand() % (n);
        int l=rand() % (n);

        chemin p1(pop_prod.pop[j]);
        chemin p2(pop_prod.pop[l]);
        pop_prod.pop.erase(pop_prod.pop.begin()+j);
        pop_prod.pop.erase(pop_prod.pop.begin()+l);
        chemin f1=chemin(p1.dim);
        chemin f2=chemin(p1.dim);
        int k=rand() % (p1.dim);
        for (int m=0;m<k;m++)
        {
            f1.indiv[m]=p1.indiv[m];
            f2.indiv[m]=p2.indiv[m];
        }
        for (int m=k;m<p1.dim;i++)
        {
            f1.indiv[m]=p2.indiv[m];
            f2.indiv[m]=p1.indiv[m];
        }
        //mutation
        f1=mutation(f1);
        f2=mutation(f2);
        //add to the next generation
        next_gen.pop[i]=f1;
        next_gen.pop[i+1]=f2;
    }
    sort(pop_prod.pop.begin(), pop_prod.pop.end(), [&](const chemin& A, const chemin& B) {
        return compare_by_adapt_asc(A, B, G);
    });
    sort(next_gen.pop.begin(), next_gen.pop.end(), [&](const chemin& A, const chemin& B) {
        return compare_by_adapt_desc(A, B, G);
    });

    for (int i=0;i<q;i++)
        next_gen.pop[i]=pop_prod.pop[i];
    return next_gen;
}


