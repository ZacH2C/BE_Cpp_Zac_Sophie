#ifdef unix
    #include <unistd.h>
    #elif defined _WIN32
    # include <windows.h>
    #define sleep(x) Sleep(1000 * (x))
#endif
#include <stdio.h>
#include <pthread.h>
//#include <windows.h>
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
    //int val_lumiere_prec
    //digitalWrite(14,HIGH);

    /*static int bascule=0;
    if(bascule) //Cette bascule change d'état chaque seconde
    {
        digitalWrite(13,HIGH); //Par nature, la LED intelligente restera dans sont état DELAY secondes puis pourra ensuite changer d'état
    }
    else
    {
        digitalWrite(13,LOW);
    }
    //cout << "Etat de la bascule : " << bascule << endl;
    bascule=1-bascule;*/

    /*char stock_lumiere[100];
    int val_lumiere = analogRead(1);
    sprintf(stock_lumiere,"Lumiere %d",val_lumiere);
    Serial.println(stock_lumiere);

    bool flag=0;
    int delat_luminosite=20;
    float delta_temps = 1;
    bool clignotement;

    if(abs(val_lumiere_prec - val_lumiere) > delat_luminosite)//detection d'un front
    {
        cout << "Val_lumiere : " << val_lumiere << " val_lumiere_prec : " << val_lumiere_prec << endl;
        clignotement = 1-clignotement;
        cout << "Clignotement : " << clignotement << endl;
        if(abs(temps_precedent - temps actuel) > delta_temps)
        {

        }
    }
    val_lumiere_prec = val_lumiere;*/
    sleep(0.1);

    //Fonction : stockge lumière -> prends en compte le temps déchantillonage et stocke la lumière sur 2-3s. Fat tablo qui detecte la lumière sur 3s. Retourne un pointeur sur un tablo de talle variable.

    //Bouton poussoir
    /*char AffichageBP[100];
    int ValeurBP = analogRead(2);
    sprintf(AffichageBP,"Bouton poussoir %d",ValeurBP);
    Serial.println(AffichageBP);*/

    //Thermomètre
    /*char AffichageTemperature[100];
    int ValeurTemperature = analogRead(6);
    sprintf(AffichageTemperature,"Temperature %d",ValeurTemperature);
    Serial.println(AffichageTemperature);*/

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

int Board::Stockage_lumiere(int lumiere_instantanee, int frequence_echentillonage)
{

    return 456;
}


