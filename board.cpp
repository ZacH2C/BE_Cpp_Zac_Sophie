#include "core_simulation.h"
#include "mydevices.h"
#include <pthread.h>
#include "modif_env.h"
#include "application.h"

extern int luminosite_environnement;

int main()
{
        // creation d'une board
    Board esp8266;

    //Actionneurs utiles pour les deux applications
    Bippeur Signal_sonore(1136);
    esp8266.pin(15,Signal_sonore);

    ExternalDigitalSensorButton BPoussoir;
    esp8266.pin(2,BPoussoir);



    ///Détection de la lumiere
    /*AnalogSensorLuminosity Luminosite(10,luminosite_environnement);
    esp8266.pin(1,Luminosite);

    //Entre 25 et 33 pour déclencher une crise d'épilepsie (+marge)
    IntelligentDigitalActuatorLED LED_intelligente(50);
    esp8266.pin(13,LED_intelligente);*/



    ///Détection des convulsions
    //Acceleromètres
    AnalogSensorAccel Accel_X(0.1,'X');
    esp8266.pin(7,Accel_X);

    AnalogSensorAccel Accel_Y(0.1,'Y');
    esp8266.pin(8,Accel_Y);

    AnalogSensorAccel Accel_Z(0.1,'Z');
    esp8266.pin(9,Accel_Z);

    //Shaker
    Shaker My_Shaker(1,0.5,0); //1 ne détecte pas, 3 détecte
    esp8266.pin(14,My_Shaker);

    //allumage de la carte
    esp8266.run();

    return 0;
}
