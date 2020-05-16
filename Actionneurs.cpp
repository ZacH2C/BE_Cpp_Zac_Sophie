#include "mydevices.h"
#ifdef unix
    #include <unistd.h>
    #elif defined _WIN32
    # include <windows.h>
    #define sleep(x) Sleep(1000 * (x))
#endif
#include <pthread.h>
#include "core_simulation.h"
#include "Actionneurs.h"

using namespace std;

//Initialiser l'attribut en dehors de toute fonction ou classe (espace global)
int Actionneurs::CptActionneur = 0;

//Possible de faire une exception : La valeur de idCapteur doit être inférieure à 10 !
Actionneurs::Actionneurs(int t)
{
    temps = t;
    EntreeActionneur = LOW;
    CptActionneur += 1;
}

Actionneurs::~Actionneurs(void)
{
    CptActionneur -= 1;
}

int Actionneurs::get_NombreActionneurs(void)
{
    return CptActionneur;
}


