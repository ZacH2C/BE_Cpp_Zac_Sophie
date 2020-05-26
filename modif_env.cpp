#include "modif_env.h"
#ifdef unix
    #include <unistd.h>
    #elif defined _WIN32
    # include <windows.h>
    #define sleep(x) Sleep(1000 * (x))
#endif
#include<map>
#include <pthread.h>

//On créé un actionneur virtuel qui n'est pas relié à la board mais qui modifie l'environnement
//classe Shaker
Shaker::Shaker(int amplitude_param, int F_param, int t):Actionneurs(t)
{
    amplitude = amplitude_param; //alpha en %
    F = F_param; //F en Hz
}

void Shaker::run()
{
    float T = 1/F;
    while(1)
    {
        if(ptrmem!=NULL)
            EntreeActionneur=*ptrmem;
        else
            EntreeActionneur=LOW;
        if (EntreeActionneur==LOW){}
            //cout << "########## Pas de secousses ##########\n";
        else
        {
            accel_env.modif_vect(amplitude, amplitude, amplitude);
            //cout<<"UP"<<endl;
            sleep(T/2);
            accel_env.modif_vect(-amplitude, -amplitude, -amplitude);
            //cout<<"DOWN"<<endl;
            sleep(T/2);
        }

    }
}

//On créé un actionneur virtuel qui n'est pas relié à la board mais qui modifie l'environnement
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
        else
            EntreeActionneur=LOW;
        if (EntreeActionneur==LOW)
            //cout << "########## Pas de clignotement ##########\n";
            NULL;
        else
        {
            //cout << "########## Clignotement Actif (flash) ##########\n";
            luminosite_environnement += 50;
            //cout<<"Etat lum:"<<luminosite_environnement<<"\n";
            sleep( T*alpha/100 );
            //cout << "########## Clignotement Actif (pause) ##########\n";
            luminosite_environnement -= 50;
            //cout<<"Etat lum:"<<luminosite_environnement<<"\n";
            sleep(T-T*alpha/100);
        }

    }
}

