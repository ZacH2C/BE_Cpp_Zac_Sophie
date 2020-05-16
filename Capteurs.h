#ifndef DEF_CAPTEURS
#define DEF_CAPTEURS
#include "core_simulation.h"
#include <string.h>
#include <vector>

class Capteurs : public Device
{
protected:
    static int CptCapteur;
    int SortieCapteur;
    int temps;

public:
    Capteurs(void);
    ~Capteurs(void);

    int get_NombreCapteurs(void);
};

#endif


