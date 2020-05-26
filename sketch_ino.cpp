#ifdef unix
    #include <unistd.h>
    #elif defined _WIN32
    # include <windows.h>
    #define sleep(x) Sleep(1 * (x))
#endif
#include <stdio.h>
#include <pthread.h>
//#include <windows.h>
#include "core_simulation.h"
#include "Vecteurs_accel.h"
#include "application.h"
//!Sophie
#include <map>
#include <vector>

application mon_application;




// la fonction d'initialisation d'arduino
void Board::setup()
{
  // on configure la vitesse de la liaison
  Serial.begin(9600);

  // on fixe les pin en entree et en sorite en fonction des capteurs/actionneurs mis sur la carte
  int i;
  for(i=0 ; i<10 ; i++)
  {
      pinMode(i,LINPUT);
  }
  for(i=10 ; i<20 ; i++)
  {
      pinMode(i,OUTPUT);
  }
}

// la boucle de controle arduino
void Board::loop()
{
    //application.set_board(this);
    float echantillonage = 10;
    mon_application.do_one_step_lumiere(echantillonage);
    //application.do_one_step_convulsions();
    sleep(echantillonage);
}
//!Zac
