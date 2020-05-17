#ifndef MYDEVICES_H
#define MYDEVICES_H
#include <iostream>
#include <thread>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <fstream>
#include "Capteurs.h"
#include "Actionneurs.h"
#include "core_simulation.h"

class IntelligentDigitalActuatorLED: public Actionneurs
{
public:
    IntelligentDigitalActuatorLED(int t):Actionneurs(t){};
    virtual void run();
};

// exemple d'actionneur digital : une led, ne pas oublier d'heriter de Device
class DigitalActuatorLED: public Actionneurs
{
public:
    // initialisation du temps de rafraichiisement
  DigitalActuatorLED(int t):Actionneurs(t){};
  // thread representant l'actionneur et permettant de fonctionner independamment de la board
  virtual void run();
};


// exemple de capteur analogique de temperature, ne pas oublier d'heriter de Device
class AnalogSensorTemperature: public Capteurs {
private:
  int alea; //fait osciller la valeur du cpateur de 1
  int temps;
public:
  AnalogSensorTemperature(int d,int  t);//constructeur ne pas oublier d'initialiser la classe mere
  virtual void run();//thread representant le capteur et permettant de fonctionner independamment de la board
};

class ExternalDigitalSensorButton: public Capteurs
{
private:
    int DocumentExiste(void);
public:
    ExternalDigitalSensorButton();
    virtual void run();
};

class AnalogSensorLuminosity: public Capteurs
{
private:
    int alea;
    int temps;
public:
    AnalogSensorLuminosity(int delta_t, int l);
    virtual void run();
};

// exemple d'actionneur sur le bus I2C permettant d'echanger des tableaux de caracteres : un ecran, ne pas oublier d'heriter de Device
class I2CActuatorScreen : public Device{
protected:
    // memorise l'affichage de l'ecran
  char buf[I2C_BUFFER_SIZE];

public:
  // constructeur
  I2CActuatorScreen ();
  // thread representant le capteur et permettant de fonctionner independamment de la board
  virtual void run();
};

#endif

