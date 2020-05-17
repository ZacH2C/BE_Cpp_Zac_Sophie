#ifdef unix
    #include <unistd.h>
    #elif defined _WIN32
    # include <windows.h>
    #define sleep(x) Sleep(1000 * (x))
#endif
#include <stdio.h>
#include <pthread.h>
#include <windows.h>
#include "core_simulation.h"

// la fonction d'initialisation d'arduino
void Board::setup()
{
  // on configure la vitesse de la liaison
  Serial.begin(9600);

  // on fixe les pin en entree et en sorite en fonction des capteurs/actionneurs mis sur la carte
  int i;
  for(i=0 ; i<10 ; i++)
  {
      pinMode(i,INPUT);
  }
  for(i=10 ; i<20 ; i++)
  {
      pinMode(i,OUTPUT);
  }
}

/*Problèmes dans cette version :
- La synchronisation LED intelligente/Luxmètre ne se fait pas bien --> ne fonctionne que si on modifie la variable temps (résolu vite fait) !
- Problème avec l'utilisation simultanée du Bouton Poussoir et de la LED (intelligente pou pas)*/


// la boucle de controle arduino
void Board::loop()
{
    char stock_lumiere[100];
    int val_lumiere = analogRead(1);
    sprintf(stock_lumiere,"Lumiere %d",val_lumiere);
    Serial.println(stock_lumiere);

    /*char AffichageTemperature[100];
    int ValeurTemperature = analogRead(3);
    sprintf(AffichageTemperature,"Temperature %d",ValeurTemperature);
    Serial.println(AffichageTemperature);*/

    char AffichageBP[100];
    int ValeurBP = analogRead(2);
    sprintf(AffichageBP,"Bouton poussoir %d",ValeurBP);
    Serial.println(AffichageBP);

    static int bascule=0;
    if(bascule)
    {
        digitalWrite(13,HIGH);
    }
    else
    {
        digitalWrite(13,LOW);
    }
    cout << "Etat de la bascule : " << bascule << endl;
    bascule=1-bascule;

    sleep(1);



    /*char buf[100];
    char stock_lumiere[100];
    int val,val_lumiere;
    static int cpt=0;
    int i=0;

    for(i=0;i<10;i++)
    {
        // lecture sur la pin 1 : capteur de temperature
        val=analogRead(1);
        val_lumiere = analogRead(2);
        sprintf(buf,"temperature %d",val);
        sprintf(stock_lumiere,"lumiere %d",val_lumiere);
        Serial.println(buf);
        Serial.println(stock_lumiere);
        if(cpt%5==0)
        {
            // tous les 5 fois on affiche sur l ecran la temperature
            sprintf(buf,"%d",val);
            sprintf(stock_lumiere,"%d", val_lumiere);
            bus.write(1,buf,100);
            bus.write(1,stock_lumiere,100);
        }
        cpt++;
        sleep(1);
    }
    */
}
