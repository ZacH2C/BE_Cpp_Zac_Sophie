#include "mydevices.h"
#ifdef unix
    #include <unistd.h>
    #elif defined _WIN32
    # include <windows.h>
    #define sleep(x) Sleep(1 * (x))
#endif
#include<map>
#include <pthread.h>
#include "Vecteurs_accel.h"

using namespace std;
int luminosite_environnement=200;
int Accel_env_XYZ[3]={3,18,-20}; //Valeur standard de l'acc�l�ration de l'environnement en g

vecteur_accel accel_env(12,1,5);

//################################### CAPTEURS ###################################

//Pour l'acc�l�rom�tre, on se base sur les specs de l'ADXL345 tr�s simplifi�es et on s'appuie sur l'architecture du capteur de lum
//On consid�re que chaque axe compte comme un capteur ind�pendant des autres mais du m�me type
//Axe='X' ou 'Y' ou 'Z'
AnalogSensorAccel::AnalogSensorAccel(int temps_param, char axe_param):Capteurs()
{
    temps=temps_param;
    axe=axe_param;
    alea = 1; //� modif
}

void AnalogSensorAccel::run()
{
    while(1)
    {
        alea=1-alea; //Bascule : toutes les 3 secondes on ajoute un alea
        if(ptrmem!=NULL)
            *ptrmem=accel_env.get_val(axe)+OFFSET; //+alea ? //On ne peut pas communiquer des n�gatifs par les pins
            //! Il faut enlever l'offset au moment de l'affichage du r�sultat et ne pas d�passer l'offset dans les n�gatifs pour Accel_envXYZ
        //cout<<"SLEEPING\n";
        sleep(1000*temps);
        //cout<<"ENDOFSLEEP\n";
    }
}

AnalogSensorTemperature::AnalogSensorTemperature(int d,int  t):Capteurs()
{
    temps = d;
    SortieCapteur=t;
    alea=1;
}

void AnalogSensorTemperature::run()
{
    while(1)
    {
        alea=1-alea;
        if(ptrmem!=NULL)
            *ptrmem=SortieCapteur+alea;

        sleep(temps);
  }
}

AnalogSensorLuminosity::AnalogSensorLuminosity(int delta_t, int l):Capteurs()
{
    temps = delta_t;
    SortieCapteur = l;
    alea = 1;
}

void AnalogSensorLuminosity::run()
{
    while(1)
    {
        alea=1-alea; //Bascule : toutes les 3 secondes on ajoute un alea
        if(ptrmem!=NULL)
            *ptrmem=luminosite_environnement+alea;

        sleep(temps);
    }
}

ExternalDigitalSensorButton::ExternalDigitalSensorButton():Capteurs()
{
    SortieCapteur = LOW;
}

void ExternalDigitalSensorButton::run()
{
    int Etat;
    while(1)
    {
        Etat = DocumentExiste();
        if(ptrmem!=NULL)
        {
            *ptrmem=Etat;
        }
    }
}

int ExternalDigitalSensorButton::DocumentExiste(void)
{
    int il_existe=0;
    if(ifstream("on.txt"))
    {// le fichier existe
        il_existe = HIGH;
    }
    else
    {
        il_existe = LOW;
    }
    return il_existe;
}

//################################### ACTIONNEURS ###################################
//!Sophie
void seconde::run()
{
    while(1)
    {
        cout << "1 seconde vient de s'ecouler" << endl;
        sleep(1000);
    }
}

void Bippeur::run()
{
    while(1)
    {
        if(ptrmem!=NULL)
            EntreeActionneur=*ptrmem;

        if (EntreeActionneur==LOW)
        {
            //cout << "########## Pas de son �mis ##########\n";
        }


        else
        {
            cout << "########## Son emis de periode " << temps << " ##########\n";
            /*digitalWrite(3,0); // �tat bas
            sleep(temps); //on attend 1136 milli-secondes
            digitalWrite(3,1); // �tat haut
            sleep(temps); // on attend 1136 millisecondes*/
        }


    }
}
//!FinSophie

void IntelligentDigitalActuatorLED::run(){
    bool flag=1;
    while(1)
    {
        if(ptrmem!=NULL)
            EntreeActionneur = *ptrmem;

        if (EntreeActionneur == LOW)
        {
            if(flag == 0)
            {
                luminosite_environnement -= 50;
                flag = 1;
            }
            //cout << "########## La LED intelligente est eteinte ##########\n";
        }
        else
        {
            if(flag == 1)
            {
                luminosite_environnement += 50;
                flag = 0;
            }
            //cout << "########## La LED intelligente est  allumee ##########\n";
        }
        sleep(temps);
    }
}

//classe DigitalActuatorLED
void DigitalActuatorLED::run()
{
    while(1)
    {
        if(ptrmem!=NULL)
            EntreeActionneur=*ptrmem;

        if (EntreeActionneur==LOW)
            cout << "########## La LED est eteinte ##########\n";

        else
            cout << "########## La LED est  allumee ##########\n";

        sleep(temps);
    }
}

//################################### COMMUNICATION ###################################
// classe I2CActuatorScreen
I2CActuatorScreen::I2CActuatorScreen ():Device(){
  }

void I2CActuatorScreen::run(){
  while(1){
    if ((i2cbus!=NULL)&&!(i2cbus->isEmptyRegister(i2caddr))){
      Device::i2cbus->requestFrom(i2caddr, buf, I2C_BUFFER_SIZE);
      cout << "---screen :"<< buf << endl;
    }
    sleep(1);
    }
}
