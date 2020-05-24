#ifndef MODIF_ENV_H
#define MODIF_ENV_H

#include <iostream>
#include <thread>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <fstream>

#include "Capteurs.h"
#include "Actionneurs.h"
#include "core_simulation.h"
#include "mydevices.h"

extern int luminosite_environnement;
extern int Accel_env_XYZ[3];

//On cr�e un actionneur qui simule une agitation de l'acc�l�rom�tre
class Shaker: public Actionneurs
{
private:
    int amplitude; //amplitude des secousses
    int F; //fr�quence des secousses en Hz
public:
    // initialisation de la fr�q de shake et du rapport cyclique
  Shaker(int amplitude_param, int F_param, int t);
  // thread representant l'actionneur et permettant de fonctionner independamment de la board
  virtual void run();
};

//On cr�� un actionneur qui clignote et modifie l'environnement
class Clignoteur: public Actionneurs
{
private:
    int alpha; //rapport cyclique en %
    int F; //fr�quence de clignotement en Hz
public:
    // initialisation de la fr�q de clignotement et du rapport cyclique
  Clignoteur(int alpha_param, int F_param, int t);
  // thread representant l'actionneur et permettant de fonctionner independamment de la board
  virtual void run();
};

//A RACCORDER COMME SUIT
/*
pour la carte ->
    Clignoteur ClignoTest(50, 1,1); //Fr�quence � 1, alpha � 50%
    esp8266.pin(14,ClignoTest);

pour l'activation dans la loop ->
    digitalWrite(14,HIGH);
*/

#endif

