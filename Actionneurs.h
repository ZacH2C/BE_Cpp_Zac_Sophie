#ifndef DEF_ACTIONNEURS
#define DEF_ACTIONNEURS
#include "core_simulation.h"
#include <string.h>
#include <vector>

class Actionneurs : public Device
{
protected:
    static int CptActionneur;
    int EntreeActionneur;
    int temps;// temps entre 2 affichage de l etat de la led

public:
    Actionneurs(int t);
    ~Actionneurs(void);
    int get_NombreActionneurs(void);
};

#endif

