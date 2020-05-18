#include "mydevices.h"
#ifdef unix
    #include <unistd.h>
    #elif defined _WIN32
    # include <windows.h>
    #define sleep(x) Sleep(1000 * (x))
#endif
#include<map>
#include <pthread.h>

using namespace std;
int luminosite_environnement=200;

//################################### CAPTEURS ###################################
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
