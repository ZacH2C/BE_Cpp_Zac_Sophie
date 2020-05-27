#ifndef APPLICATION_H
#define APPLICATION_H
#include <map>
#include <vector>
#include "core_simulation.h"
#include "Vecteurs_accel.h"

using namespace std;

class Board;

class application
{
    //friend class Board;
public:
    application();                    //Constructeur par défaut
    application(Board *b); //Constructeur avec params
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

    ///Méthodes principales !NE PAS UTILISER EN MEME TEMPS!
    void do_one_step_lumiere(float echantillonage_board);
    void do_one_step_convulsions(float echantillonage_board);

private:
    Board *ma_board;
    ///VAR GLOBALES
    //DetectFlash
    bool epilepsie;
    int i; int j;
    int bascule;
    map<float,int> tableau;
    int robustesse;
    //DetectSecousses
    vecteur_accel accel_stab;
    int cpt_stab;
    int cpt_perturb;

};
#endif
