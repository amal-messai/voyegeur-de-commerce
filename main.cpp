#include "classes.h"
#include <iostream>
#include <string>
#include <cstdlib> // for rand() and srand()
#include <ctime>   // for time()
#include <bits/stdc++.h>
#include <cstring>
#include <vector>
using namespace std;
int main()
{
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
population pop_init=gen_init(G,6,0);

population prod=selec_reproducteurs(pop_init,G,"selec_roulette");
cout<<"ok2 "<<"\n";
population pop_next=selection_nextgen(prod,pop_init,2,G);
cout<<"ok3"<<"\n";
pop_init=pop_next;
cout<<"ok4"<<"\n ";


for (int i=0; i<4;i++)
{
    cout<<"ieration"<<i;
    prod=selec_reproducteurs(pop_init,G,"selec_roulette");
    cout<<"reproducing  made";
    pop_next=selection_nextgen(prod,pop_init,2,G);
    cout<<"next gen "<<i<<"\n";
    pop_init=pop_next;
}
pop_init.affiche();

sort(pop_init.pop.begin(), pop_init.pop.end(), [&](const chemin& A, const chemin& B) {
        return compare_by_adapt_asc(A, B, G);
});
chemin chemin_meilleur(pop_init.pop[0]);
chemin_meilleur.affiche();

    return 0;
}

