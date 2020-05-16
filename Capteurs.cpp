#include "mydevices.h"
#ifdef unix
    #include <unistd.h>
    #elif defined _WIN32
    # include <windows.h>
    #define sleep(x) Sleep(1000 * (x))
#endif
#include <pthread.h>
#include "core_simulation.h"
#include "Capteurs.h"

using namespace std;

//Initialiser l'attribut en dehors de toute fonction ou classe (espace global)
int Capteurs::CptCapteur = 0;

//Possible de faire une exception : La valeur de idCapteur doit être inférieure à 10 !
Capteurs::Capteurs(void)
{
    CptCapteur += 1;
}

Capteurs::~Capteurs(void)
{
    CptCapteur -= 1;
}

int Capteurs::get_NombreCapteurs(void)
{
    return CptCapteur;
}

