#include "class.h"
#include <iostream>
#include <string>
#include <cstdlib> // for rand() and srand()
#include <ctime>   // for time()
#include <bits/stdc++.h>
using namespace std;

int main()
{
    chemin ch(5);
    for (int i=0;i<ch.dim;i++)
    {
        ch.indiv[i]=i;
    }
    for (int i=0;i<ch.dim;i++)
    {
        ch.poids[i]=i*2;
    }
    cout<<ch.adapt()<<"\n";
    chemin ch1(5);
    for (int i=0;i<ch1.dim;i++)
    {
        ch1.indiv[i]=i*3;
    }
    for (int i=0;i<ch1.dim;i++)
    {
        ch1.poids[i]=i*5;
    }
    population popu(2);
    population popu1(popu);
    cout<<popu.nbre;
    popu.pop[0]=ch;    popu.pop[1]=ch1;
    chemin res=selec_roulette(popu); res.affiche();
    return 0;
}


helloo
marhbaaaaa
nestanna fiik
tasma3 fiyaaa ??? hello ??
