#include "core_simulation.h"
#include "mydevices.h"
#include <pthread.h>
#include "modif_env.h"
#include "application.h"

extern int luminosite_environnement;
extern int Accel_env_XYZ[3];


int main()
{
    // creation d'une board
    Board esp8266;

    AnalogSensorLuminosity Luminosite(10,luminosite_environnement);
    esp8266.pin(1,Luminosite);

    IntelligentDigitalActuatorLED LED_intelligente(25); //Entre 25 et 33 pour déclencher une crise d'épilepsie
    esp8266.pin(13,LED_intelligente);

    Bippeur Signal_sonore(1136);
    esp8266.pin(15,Signal_sonore);

    ExternalDigitalSensorButton BPoussoir;
    esp8266.pin(2,BPoussoir);

    /*
    //Acceleromètres
    AnalogSensorAccel Accel_X(0.1,'X');
    esp8266.pin(7,Accel_X);
    AnalogSensorAccel Accel_Y(0.1,'Y');
    esp8266.pin(8,Accel_Y);
    AnalogSensorAccel Accel_Z(0.1,'Z');
    esp8266.pin(9,Accel_Z);
    //Shaker
    Shaker My_Shaker(10,1,1);
    esp8266.pin(14,My_Shaker);
    */

    //allumage de la carte
    esp8266.run();

    return 0;
}
