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
#include "Vecteurs_accel.h"

//Permet de modifier directement l'environnement
extern int luminosite_environnement;
extern vecteur_accel accel_env;

//On crée un actionneur qui simule une agitation de l'accéléromètre
class Shaker: public Actionneurs
{
private:
    int amplitude; //amplitude des secousses
    float T; //Période des secousses en s
    int aleaX;
    int aleaY;
    int aleaZ;
public:
    // initialisation de la fréq de shake et du rapport cyclique
  Shaker(int amplitude_param, float T_param, int t);
  // thread representant l'actionneur et permettant de fonctionner independamment de la board
  virtual void run();
};

//On créé un actionneur qui clignote et modifie l'environnement
class Clignoteur: public Actionneurs
{
private:
    int alpha; //rapport cyclique en %
    int F; //fréquence de clignotement en Hz
public:
    // initialisation de la fréq de clignotement et du rapport cyclique
  Clignoteur(int alpha_param, int F_param, int t);
  // thread representant l'actionneur et permettant de fonctionner independamment de la board
  virtual void run();
};

//A RACCORDER COMME SUIT
/*
pour la carte ->
    Clignoteur ClignoTest(50, 1,1); //Fréquence à 1, alpha à 50%
    esp8266.pin(14,ClignoTest);

pour l'activation dans la loop ->
    digitalWrite(14,HIGH);
*/

#endif

