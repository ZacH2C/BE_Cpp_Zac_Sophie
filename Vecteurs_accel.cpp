#include "Vecteurs_accel.h"
#include <iostream>
using namespace std;

//Constructeur par défaut
vecteur_accel::vecteur_accel() : m_X(0), m_Y(0), m_Z(0)
{
}
//Constructeur avec init
vecteur_accel::vecteur_accel(int X, int Y, int Z) : m_X(X), m_Y(Y), m_Z(Z)
{
}
//Destructeur
vecteur_accel::~vecteur_accel()
{
}

int vecteur_accel::get_val(char Axe) const
{
    int retour;
    switch(Axe)
    {
        case 'X': retour=m_X;     break;
        case 'Y': retour=m_Y;     break;
        case 'Z': retour=m_Z;     break;
        default : retour=1337;    break;
    }
    return retour;
}

void vecteur_accel::set_vect(int X, int Y, int Z)
{
    m_X = X;
    m_Y = Y;
    m_Z = Z;
}

void vecteur_accel::modif_vect(int add_X, int add_Y, int add_Z)
{
    m_X += add_X;
    m_Y += add_Y;
    m_Z += add_Z;
}

float vecteur_accel::norme_vect() const
{
    return sqrt(m_X*m_X+m_Y*m_Y+m_Z*m_Z);
}

void vecteur_accel::afficher_vect() const
{
    cout<<"X="<<m_X<<" Y="<<m_Y<<" Z="<<m_Z<<endl;
}

//Produit scalaire entre deux vecteurs
int operator*(vecteur_accel const& vect_a, vecteur_accel const& vect_b)
{
    return vect_a.get_val('X')*vect_b.get_val('X')+vect_a.get_val('Y')*vect_b.get_val('Y')+vect_a.get_val('Z')*vect_b.get_val('Z');
}

//Angle entre deux vecteurs
float operator-(vecteur_accel const& vect_a, vecteur_accel const& vect_b)
{
    float retour;
    cout<<"OPERATION\n"<<endl;
    if(vect_a.norme_vect()==0 || vect_b.norme_vect()==0) retour=0;
    else retour=acos((vect_a*vect_b)/(vect_a.norme_vect()*vect_b.norme_vect()))*180/PI;
    return retour;
}

///La fonction acos a comme specs :
//Return :
//Principal arc cosine of x, in the interval [0,pi] radians.
//One radian is equivalent to 180/PI degrees.
