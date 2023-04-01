#include "class.h"
#include <iostream>
#include <string>
#include <cstdlib> // for rand() and srand()
#include <vector>
#include <algorithm>
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
        return compare_by_adapt_desc(A, B, G);
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
population selec_tournoi(const population &pop,graphe G)
{
    population pop_tournoi(pop.nbre);
    for (int i=0;i<pop.nbre;i++)
    {
        int r = rand() % (pop.nbre);
        if (compare_by_adapt_asc(pop.pop.at(i),pop.pop.at(r),G))
            pop_tournoi[i]=pop.pop.at(i);
        else
            pop_tournoi[i]=pop.pop.at(r);;

    }
    return pop_tournoi;
}

population selec_reproducteurs(population pop_initi,graphe G,std::string selection_method)
{
    if (selection_method.compare("selec_tournoi") == 0) {return selec_tournoi(pop_initi,G);}
    population pop_prod (pop_initi.nbre);
    for (int i = 0; i < pop_initi.nbre; i++) {
        chemin indiv_selected;
        if (selection_method.compare("selec_rang") == 0) {
            indiv_selected = selec_rang(pop_initi, G);
        }
        else if (selection_method.compare("roulette") == 0) {
            indiv_selected = selec_roulette(pop_initi, G);
        }
        pop_prod[i] = indiv_selected;
    }
    return pop_prod;
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
population gen_init(graphe G,int taille)
{
    int nbre_ville=G.dim;
    population P(taille);
    for (int i=0;i<taille;i++)
    {
        chemin chemin_result(nbre_ville);
        chemin_result.indiv[0]=rand() % (nbre_ville);
        for (int j=1;j<nbre_ville;j++)
        {
            int r = rand() % (nbre_ville);
            while( G.val(j-1,r)==-1 )
                    int r = rand() % (nbre_ville);
            chemin_result.indiv[j]=r;
        }
        P.pop[i]=chemin_result;
    }
    return P;
}
