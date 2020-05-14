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
  pinMode(0,OUTPUT);
  pinMode(1,INPUT);
  pinMode(2,INPUT);
  pinMode(3,OUTPUT);
  pinMode(4,INPUT);
}

// la boucle de controle arduino
void Board::loop()
{

    char AffichageBP[100]; char stock_lumiere[100];
    int val_lumiere = analogRead(2); bool ValeurBP = analogRead(4);

    sprintf(stock_lumiere,"lumiere %d",val_lumiere);
    sprintf(AffichageBP,"Bouton poussoir %d",ValeurBP);
    Serial.println(stock_lumiere);
    Serial.println(AffichageBP);

    digitalWrite(3,ValeurBP);
    sleep(1);


    /*char buf[100];
    char stock_lumiere[100];
    int val,val_lumiere;
    static int cpt=0;
    static int bascule=0;
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
    // on eteint et on allume la LED
    if(bascule)
    {
        digitalWrite(0,HIGH);
        digitalWrite(3,HIGH);
    }
    else
    {
        digitalWrite(0,LOW);
        digitalWrite(3,LOW);
    }

    bascule=1-bascule;*/
}
