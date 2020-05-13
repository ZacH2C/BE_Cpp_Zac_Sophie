#include "mydevices.h"

#ifdef unix
    #include <unistd.h>
    #elif defined _WIN32
    # include <windows.h>
    #define sleep(x) Sleep(1000 * (x))
#endif

#include <pthread.h>

using namespace std;

int luminosite_environnement=200;

IntelligentDigitalActuatorLED::IntelligentDigitalActuatorLED(int t):Device()
{
    etat = LOW;
    temps = t;
}

void IntelligentDigitalActuatorLED::run(){
    while(1)
    {
        if(ptrmem!=NULL)
            etat=*ptrmem;
        if (etat==LOW)
        {
            luminosite_environnement -= 50;
            cout << "La LED intelligente est eteinte\n";
        }
        else
        {
            luminosite_environnement += 50;
            cout << "La LED intelligente est  allumee\n";
        }
        sleep(temps);
    }
}

//classe DigitalActuatorLED
DigitalActuatorLED::DigitalActuatorLED(int t):Device(),state(LOW),temps(t){
}

void DigitalActuatorLED::run(){
  while(1){
    if(ptrmem!=NULL)
      state=*ptrmem;
    if (state==LOW)
      cout << "((((eteint))))\n";
    else
    cout << "((((allume))))\n";
    sleep(temps);
    }
}

AnalogSensorLuminosity::AnalogSensorLuminosity(int l, int delta_t):Device()
{
    temps = delta_t;
    luminosite_environnement=l;
    alea = 1;
}

void AnalogSensorLuminosity::run()
{
    while(1)
    {
        alea=1-alea;
        if(ptrmem!=NULL)
            *ptrmem=luminosite_environnement+alea;
        sleep(temps);
    }
}

int AnalogSensorLuminosity::valeur_luminosite(void)
{
    return luminosite_environnement;
}

//classe AnalogSensorTemperature
AnalogSensorTemperature::AnalogSensorTemperature(int d,int  t):Device(),val(t),temps(d){
  alea=1;
}

void AnalogSensorTemperature::run(){
  while(1){
    alea=1-alea;
    if(ptrmem!=NULL)
      *ptrmem=val+alea;
    sleep(temps);
  }
}

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
