#include "classes.h"
#include <iostream>
#include <string>
#include <cstdlib> // for rand() and srand()
#include <ctime>   // for time()
#include <bits/stdc++.h>
using namespace std;

int main()
{
    srand(time(NULL));
    graphe G (4);
    G.tab[0][0]=-1;
    G.tab[0][1]=10;
    G.tab[0][2]=15;
    G.tab[0][3]=20;

    G.tab[1][0]=10;
    G.tab[1][1]=-1;
    G.tab[1][2]=35;
    G.tab[1][3]=25;

    G.tab[2][0]=15;
    G.tab[2][1]=35;
    G.tab[2][2]=-1;
    G.tab[2][3]=30;

    G.tab[3][0]=20;
    G.tab[3][1]=25;
    G.tab[3][2]=30;
    G.tab[3][3]=-1;
G.affiche();
population pop_init=gen_init(G,5,0);
pop_init.affiche();
cout<<pop_init.pop[0].adapt(G);
//chemin ch= selec_roulette(pop_init,G);
//cout<<"\n"; cout<<"la selection par roulette donne "<<"\n";
//ch.affiche();

//population prod=selec_reproducteurs(pop_init,G,"selec_roulette");
//population pop_next=selection_nextgen(prod,5,G);
//pop_init=pop_next;
////for (int i=0; i<10;i++)
////{
////    cout<<"ieration"<<i;
////    delete &prod;
////    delete &pop_next;
////    prod=selec_reproducteurs(pop_init,G,"selec_roulette");
////    pop_next=selection_nextgen(prod,5,G);
////    delete &pop_init;
////    population pop_init=pop_next;
////
////}
//
//
//sort(pop_init.pop.begin(), pop_init.pop.end(), [&](const chemin& A, const chemin& B) {
//        return compare_by_adapt_asc(A, B, G);
//});
//chemin chemin_meilleur(pop_init.pop[0]);
//chemin_meilleur.affiche();

    return 0;
}

