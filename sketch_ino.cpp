#include "core_simulation.h"
#include "mydevices.h"
#include <pthread.h>

extern int luminosite_environnement;

int main()
{
    // creation d'une board
    Board esp8266;

    ExternalDigitalSensorButton BPoussoir;
    esp8266.pin(2,BPoussoir);

    AnalogSensorTemperature temperature(DELAY,TEMP);
    esp8266.pin(6,temperature);

    IntelligentDigitalActuatorLED LED_intelligente(DELAY);
    esp8266.pin(13,LED_intelligente);

    AnalogSensorLuminosity Luminosite(0.1,luminosite_environnement);
    esp8266.pin(1,Luminosite);

    /*DigitalActuatorLED led1(DELAY);
    esp8266.pin(11,led1);*/

    /*I2CActuatorScreen screen;*/
    /*esp8266.i2c(1,screen);*/



    //allumage de la carte
    esp8266.run();
    return 0;
}
