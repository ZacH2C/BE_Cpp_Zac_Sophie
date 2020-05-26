#ifndef APPLICATION_H
#define APPLICATION_H
#include <map>
#include <vector>
#include "core_simulation.h"

map<float,int> ma_map;

class application
{
    //friend class Board;

public:
    application();                    //Constructeur par défaut
    //application(int X, int Y, int Z); //Constructeur avec params
    ~application();

    ///Mutateur
    //void set_board(Board board_param);

    ///Méthodes lumière
    map<float,int> Stockage_lumiere(map<float,int> tableau_temps_luminosite, int lumiere_instantanee, float periode_echentillonage, int compteur);
    bool Traitement_lumiere(map<float,int> dernieres_secondes, float periode_echantillonage);
    bool Traitement_frequence_clignotement(vector<float> vecteur_temps);

    ///Méthodes convulsions
    bool Detection_convulsions();
    ///TODO : UTILISATION CAPTEURS, TESTS

    ///Méthodes principale !NE PAS UTILISER EN MEME TEMPS!
    void do_one_step_lumiere(float echantillonage_board);
    void do_one_step_convulsions();

private:
    //Board ma_board;
    ///METTRE VAR GLOBALES
    bool epilepsie;
    int i; int j;
    int bascule;
    map<float,int> tableau;
    int robustesse;
};
#endif
