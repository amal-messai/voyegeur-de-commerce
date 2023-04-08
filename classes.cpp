#include "classes.h"
#include <iostream>
#include <string>
#include <cstdlib> // for rand() and srand()
#include <vector>
#include <algorithm>
#include <ctime>   // for time()
#include <cstring>
using namespace std;
// Class graphe
int graphe::val(int i, int j) const {
    if (i >= 0 && i < dim && j >= 0 && j < dim) {
        return tab[i][j];
    } else {

        return -1;
    }
}
void population::sort_by_adapt_asc(const graphe& G) {
    for (int i = 0; i < nbre - 1; i++) {
        for (int j = 0; j < nbre - i - 1; j++) {
            if (pop[j].adapt(G) > pop[j + 1].adapt(G)) {
                chemin tmp = pop[j];
                pop[j] = pop[j + 1];
                pop[j + 1] = tmp;
            }
        }
    }

}
void population::sort_by_adapt_desc(const graphe& G) {
    for (int i = 0; i < nbre - 1; i++) {
        for (int j = 0; j < nbre - i - 1; j++) {
            if (pop[j].adapt(G) < pop[j + 1].adapt(G)) {
                chemin tmp = pop[j];
                pop[j] = pop[j + 1];
                pop[j + 1] = tmp;
            }
        }
    }

}
graphe::graphe(int n)
{
    dim=n;
    tab =new int*[n];
    for (int i=0;i<n;i++)
    {
        tab[i]=new int [n];
    }
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        tab[i][j] = 0; // initialize all values to 0
      }}

}
graphe::~graphe()
{
     for (int i = 0; i < dim; i++) {
        delete[] tab[i];
    }
    delete[] tab;
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
    dim=n;
    indiv= new int [dim];
    for (int j = 0; j < dim; j++) {
        indiv[j] = 0;
}}
individu::individu(const individu& v)
{
    dim=v.dim;
    indiv= new int [dim];
    for (int i=0; i<dim;i++)
    {
        indiv[i]=v.indiv[i];
    }
}

 //destructeur d'individu
chemin::~chemin()
{
    if (indiv!=0) delete [] indiv;
    dim=0;
}

int chemin::adapt (  const graphe& G) const
{
    int s=G.val( indiv[dim-1],indiv[0] );
    for (int i =0;i<dim-1; i++)
    {
        s+=G.val( indiv[i],indiv[i+1] );
    }
    return s;
}

bool chemin::in(int k)
{

    bool test= false;
    int i=0;
    while ( (test==false) && (i<dim))
    {
        if (indiv[i]==k)
            test=true;
        i++;
    }
    return test;

}
void chemin::affiche()
{
    cout<<"\n"<<"affichage de l'individu"<<"\n";
    for (int i=0;i<dim-1;i++)
        cout<< indiv[i]<<",";
    cout<<indiv[dim-1];
}
chemin& chemin::operator =(const chemin&other)
{
    if (this != &other) {
        dim = other.dim;
        delete[] indiv;
        indiv = new int[dim];
    for (int i=0;i<dim;i++) indiv[i]=other.indiv[i];}
    return *this;
}

// class population et ses fonctionalités
population::population(int n)
{
    nbre=n;
    pop .resize(n);
}

population::population(const population& other)
{
    nbre=other.nbre;
    pop.reserve(other.pop.size()); // allocate memory for the new population
        for (const auto& ch : other.pop) {
            pop.emplace_back(ch); // use chemin's copy constructor to make a copy of each individual
        }
    }


void population::affiche()
{
    for (int i=0;i<nbre;i++)
    {
        cout<<"indivual number="<<i+1;
        pop[i].affiche();
        cout<<"\n";

            }
}
population::~population()
{
    pop.clear();
    nbre=0;
}
population& population::operator=(const population& other)
{
   if (this != &other) {
        nbre = other.nbre;
        pop.clear();
        pop.reserve(other.pop.size());
        for (const auto& ch : other.pop) {
            pop.emplace_back(ch);
        }
    }
    return *this;
}

chemin mutation (chemin ch , const graphe& G)
{
    int l = rand() % (ch.dim-1)+2;
    int k = rand() % (ch.dim-2)+1;
    if (l<k)
    {
        int c=k;
        k=l;
        l=c;
    }
    while ((G.val(ch.indiv[k-1], ch.indiv[l])==-1) || (G.val(ch.indiv[l-1], ch.indiv[k+2])==-1)|| (G.val(ch.indiv[l-2], ch.indiv[k+1])==-1) || (G.val(ch.indiv[k], ch.indiv[l+1])==-1))
    {
         l = rand() % (ch.dim-1)+2;
         k = rand() % (ch.dim-2)+1;

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
bool compare_by_adapt_asc(const chemin& A,const chemin& B, const graphe& G)
{
    return A.adapt(G)< B.adapt(G);
}
bool compare_by_adapt_desc(const chemin& A,const chemin& B, const graphe& G)
{
    return A.adapt(G)>B.adapt(G);
}

chemin selec_roulette(const population& P, const graphe& G )
{
    int s=0;
    for (int i=0;i<P.nbre;i++) s+=P.pop[i].adapt(G);
    int r = rand() % (s+1);
    int i=0; int sum=P.pop[0].adapt(G);
    while( (i<P.nbre)&& (sum<r) )
    {
        i+=1;
        sum+=P.pop[i].adapt(G);
    }
    return P.pop[i];
}

 chemin selec_rang(const population& P, const graphe& G)
{

      population pop_copie(P);
      pop_copie.sort_by_adapt_asc(G);
      int somme_rang=P.nbre*(P.nbre+1)/2;
      int r = rand() % (somme_rang+1);
      int i=0; int sum=1;
      while( (i<pop_copie.nbre)&& (sum<r) )
        {
        i+=1;
        sum+=i+1;
      }
    return pop_copie.pop[i];
}

population selec_tournoi(const population &gen,const graphe& G)
{
    int n=gen.nbre;
    population pop_tournoi(n);
    for(int i=0; i<n; i++)
    {
        int j=rand()%n;
        int k=rand()%n;
        chemin p1(gen.pop[j]);
        chemin p2(gen.pop[k]);
        double proba1,proba2;
        if (p1.adapt(G)<p2.adapt(G))
        {
            proba1=0.8;
            proba2=1-0.8;
        }
        else
        {
            proba2=0.8;
            proba1=1-0.8;
        }
        double proba=rand() / (double)RAND_MAX;
        if (proba<proba1) pop_tournoi.pop[i]=p1;
        else pop_tournoi.pop[i]=p2;

    }
    return pop_tournoi;
}

population selec_reproducteurs( const population& pop_initi,const graphe& G,const char*  selection_method)
{
    population pop_prod (pop_initi.nbre);
    if (strcmp("selec_tournoi",selection_method) == 0) { pop_prod=selec_tournoi(pop_initi,G);return pop_prod;}
   if (strcmp("selec_rang", selection_method) == 0) {
            for (int i = 0; i < pop_initi.nbre; i++) {
                chemin indiv_selected = selec_rang(pop_initi, G);
                pop_prod[i] = indiv_selected;
            }
        } else if (strcmp("selec_roulette", selection_method) == 0) {
            for (int i = 0; i < pop_initi.nbre; i++) {
                chemin ch = selec_roulette(pop_initi, G);
                pop_prod[i] = ch;
            }
        }
return pop_prod;

    }

 population selection_nextgen(population pop_prod, int q, const graphe& G)
{

    int n=pop_prod.nbre;
    population next_gen=population(n);
    for (int i=0;i<(n/2);i++)
    {
        //crossover

        int j= rand() % (pop_prod.nbre);
        int l=rand() % (pop_prod.nbre);


        chemin p1(pop_prod.pop[j]);
        chemin p2(pop_prod.pop[l]);


        pop_prod.pop.erase(pop_prod.pop.begin()+j);

        pop_prod.pop.erase(pop_prod.pop.begin()+l);

        pop_prod.nbre-=2;


        chemin f1(p1.dim);
        chemin f2(p1.dim);

        int k=rand() % (p1.dim)+1;
        while ((G.val(p1.indiv[k-1], p2.indiv[k])==-1) || (G.val(p2.indiv[k-1], p1.indiv[k])==-1))
        {
            k=rand() % (p1.dim)+1;

        }


        for (int m=0;m<k;m++)
        {
            f1.indiv[m]=p1.indiv[m];
            f2.indiv[m]=p2.indiv[m];
        }
        for (int m=k;m<p1.dim;m++)
        {
            f1.indiv[m]=p2.indiv[m];
            f2.indiv[m]=p1.indiv[m];
        }
        /*
        cout<<"enfant"<<"\n";
        f1.affiche();
        cout<<"enfant"<<"\n";
        f2.affiche();
        */
        //mutation
        f1=mutation(f1,G);
        //f1.affiche();
        f2=mutation(f2,G);
        //f2.affiche();
        //add to the next generation
        next_gen.pop[2*i]=f1;
        //cout<<"addok"<<"\n";
        next_gen.pop[2*i+1]=f2;
        //cout<<"addok"<<"\n";

    }
    sort(pop_prod.pop.begin(), pop_prod.pop.end(), [&](const chemin& A, const chemin& B) {
        return compare_by_adapt_asc(A, B, G);
    });
    sort(next_gen.pop.begin(), next_gen.pop.end(), [&](const chemin& A, const chemin& B ) {
        return compare_by_adapt_desc(A, B, G);
    });

    for (int i=0;i<q;i++)
        next_gen.pop[i]=pop_prod.pop[i];
    return next_gen;
}



population gen_init(const graphe& G,int taille, int k)
{
    int nbre_ville=G.dim;
    population gen (taille);
    for (int i=0;i<taille;i++)
    {
        chemin chemin_result (nbre_ville);
        chemin_result.indiv[0]=k;
        for (int j=1;j<nbre_ville;j++)
        {
            int r = rand() % (nbre_ville);
            while( (  G.val(chemin_result.indiv[j-1],r)==-1 ) || ( chemin_result.in(r)==true ) )
            {
                r = rand() % (nbre_ville);
            }
              chemin_result.indiv[j]=r;
        }
        gen.pop[i]= chemin_result;
    }
    return gen;
}

