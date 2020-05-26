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
//!Sophie
#include <map>
#include <vector>

map<float,int> tableau;
int robustesse = 0;
//!FinSophie

extern vecteur_accel accel_env;

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
    //!Sophie

//    static int i; static int j;
//    static int bascule=0;
//    float echantillonage = 10;
//
//
//    int val_lumiere = analogRead(1);
//    int val_BP = analogRead(2);
//
//    /*char stock_lumiere[100];
//    sprintf(stock_lumiere,"Lumiere %d",val_lumiere);
//    Serial.println(stock_lumiere);
//
//    char stock_BP[100];
//    sprintf(stock_BP,"Bouton poussoir %d",val_BP);
//    Serial.println(stock_BP);*/
//
//    if(bascule) //Cette bascule change d'état chaque seconde
//    {
//        digitalWrite(13,HIGH); //Par nature, la LED intelligente restera dans son état DELAY secondes (cf main) puis pourra ensuite changer d'état
//    }
//    else
//    {
//        digitalWrite(13,LOW);
//    }
//    bascule=1-bascule;
//
//    digitalWrite(14,LOW);
//
//    tableau = Stockage_lumiere(tableau,val_lumiere, echantillonage,i);
//    bool epilepsie = Traitement_lumiere(tableau, echantillonage);
//
//    if(epilepsie == 1)
//    {
//        j++;
//        cout << "ATTENTION : LA LUMINOSITE PEUT PROVOQUER UNE CRISE D'EPILEPSIE !" << endl;
//    }
//
//    if(j==3)
//    {
//        cout << "Je suis entree ici" << endl;
//        while(val_BP == LOW)
//        {
//            digitalWrite(15,HIGH);
//        }
//        j=0;
//    }
//    digitalWrite(15,LOW);
//    sleep(echantillonage);
//    i++;
//
    //!FinSophie
    //!Zac
    //float echantillonage = 10; //Execution de la loop toutes les 10 ms (sans prendre en compte  le tps d'éxec)
    //sleep(echantillonage);
    digitalWrite(14,HIGH);
    sleep(500);
    cout<<"Valeurs mesurees : \nX:"<<analogRead(7)-OFFSET<<" Y:"<<analogRead(8)-OFFSET<<" Z:"<<analogRead(9)-OFFSET<<endl; //!OFFSET pour l'affichage
    cout<<"Valeurs reelles : \nX:"<<accel_env.get_val('X')<<" Y:"<<accel_env.get_val('Y')<<" Z:"<<accel_env.get_val('Z')<<endl;

    //!FinZac
}

map<float,int> Board::Stockage_lumiere(map<float,int> tableau_temps_luminosite, int lumiere_instantanee, float periode_echentillonage, int compteur)
{
    map<float, int>::iterator it;
    int nombre_elements = 3000/periode_echentillonage;
    tableau_temps_luminosite.insert({compteur*periode_echentillonage,lumiere_instantanee});

    if(compteur > nombre_elements)
    {
        it = tableau_temps_luminosite.begin();
        tableau_temps_luminosite.erase(it);
    }

    return tableau_temps_luminosite;
}

bool Board::Traitement_lumiere(map<float,int> dernieres_secondes, float periode_echantillonage)
{
    int delta_luminosite = 40;
    map<float,int>::iterator m_it = dernieres_secondes.begin();
    int val_lumiere_prec = m_it->second;
    vector<float> traitement_temps;
    bool resultat;

    for(m_it=dernieres_secondes.begin(); m_it!=dernieres_secondes.end(); m_it++)
    {
        if(abs(val_lumiere_prec - m_it->second) > delta_luminosite)//detection d'un front
        {
            traitement_temps.push_back(m_it->first); //On récupère les temps associés au fronts dans un vecteur
        }
        val_lumiere_prec = m_it->second;
    }

    if(dernieres_secondes.size()>= 3000/periode_echantillonage)
    {
        resultat = Traitement_frequence_clignotement(traitement_temps);
    }

    return resultat;
}

bool Board::Traitement_frequence_clignotement(vector<float> vecteur_temps)
{
    bool retour_fonction=0;
    int i;

    //cout << "vecteur_temps.size() " << vecteur_temps.size() << endl;
    if(vecteur_temps.size() <= 70 && vecteur_temps.size() >= 5) //Valeurs empriques ! Peuvent être modifiés
    {
        robustesse++;
        //cout << "vecteur_temps[vecteur_temps.size()-1]-vecteur_temps[vecteur_temps.size()-11] " << vecteur_temps[vecteur_temps.size()-1]-vecteur_temps[vecteur_temps.size()-11] << endl;
    }

    else
    {
        retour_fonction=0;
    }

    if(robustesse >= 10)
    {
        if(vecteur_temps[vecteur_temps.size()-1]-vecteur_temps[vecteur_temps.size()-11] <= 1200) //1200 est une valeur empirique ! Peut être modifiée
        {
            retour_fonction=1;
        }
        robustesse=0;
    }
    return retour_fonction;
}


//Peut être ajouté dans le loop au besoin :

//Clignotement de la LED :


//int val_lumiere_prec
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

    /*

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
    //Fonction : stockge lumière -> prends en compte le temps déchantillonage et stocke la lumière sur 2-3s. Fat tablo qui detecte la lumière sur 3s. Retourne un pointeur sur un tablo de talle variable.


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
    }*/
