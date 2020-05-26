#ifndef VECTEURS_ACCEL_H
#define VECTEURS_ACCEL_H

#include <cmath>
#define PI 3.14159265

class vecteur_accel
{
public:
    vecteur_accel();                    //Constructeur par défaut (init à 0,0,0)
    vecteur_accel(int X, int Y, int Z); //Constructeur avec params
    ~vecteur_accel();

    ///Accesseur
    int get_val(char Axe) const;
    ///Mutateur
    void set_vect(int X, int Y, int Z);                 //permet de choisir les composantes du vecteur
    void modif_vect(int add_X, int add_Y, int add_Z);   //permet d'ajouter des valeurs aux composantes du vecteur

    ///Méthodes
    float norme_vect() const;
    void afficher_vect() const;

private:
    int m_X;
    int m_Y;
    int m_Z;
};

///Opérateurs
//Produit scalaire entre nos vecteurs d'acceleration
int operator*(vecteur_accel const& vect_a, vecteur_accel const& vect_b);
//Angle entre deux vecteurs
float operator-(vecteur_accel const& vect_a, vecteur_accel const& vect_b);

#endif
