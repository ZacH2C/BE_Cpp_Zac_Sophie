#include "modif_env.h"
#ifdef unix
    #include <unistd.h>
    #elif defined _WIN32
    # include <windows.h>
    #define sleep(x) Sleep(1000 * (x))
#endif
#include<map>
#include <pthread.h>

//On cr�� un actionneur virtuel qui n'est pas reli� � la board mais qui modifie l'environnement
//classe Clignoteur
Clignoteur::Clignoteur(int alpha_param, int F_param, int t):Actionneurs(t)
{
    alpha = alpha_param; //alpha en %
    F = F_param; //F en Hz
}

void Clignoteur::run()
{
    float T = 1/F;
    while(1)
    {
         if(ptrmem!=NULL)
            EntreeActionneur=*ptrmem;

        if (EntreeActionneur==LOW)
            cout << "########## Pas de clignotement ##########\n";
        else
        {
            cout << "########## Clignotement Actif (flash) ##########\n";
            luminosite_environnement += 50;
            cout<<"Etat lum:"<<luminosite_environnement<<"\n";
            sleep( T*alpha/100 );
            cout << "########## Clignotement Actif (pause) ##########\n";
            luminosite_environnement -= 50;
            cout<<"Etat lum:"<<luminosite_environnement<<"\n";
            sleep(T-T*alpha/100);
        }

    }
}
