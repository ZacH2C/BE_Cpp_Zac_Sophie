#include "application.h"

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
#include "modif_env.h"
#include "mydevices.h"
//!Sophie

//Pour accéléro
extern vecteur_accel accel_env;
//Mémorisation de la stabilité
vecteur_accel accel_stab(accel_env);
int cpt_stab, cpt_perturb = 0;
//FinPourAccelero

//Constructeur
application::application()
{
    epilepsie=0;
    i=0;
    j=0;
    bascule=0;
    robustesse=0;
}

application::application(Board *b)
{
    epilepsie=0;
    i=0;
    j=0;
    bascule=0;
    robustesse=0;
    ma_board=b;
}

//Mutateur
/*
void application::set_board(Board board_param)
{
    ma_board=board_param;
}
*/

///Méthodes
map<float,int> application::Stockage_lumiere(map<float,int> tableau_temps_luminosite, int lumiere_instantanee, float periode_echentillonage, int compteur)
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

bool application::Traitement_lumiere(map<float,int> dernieres_secondes, float periode_echantillonage)
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

    if(dernieres_secondes.size()<= 3000/periode_echantillonage)
    {
        //throw Erreur(string("Il faut attendre trois secondes au demarage"));
    }
    else
    {
        resultat = Traitement_frequence_clignotement(traitement_temps);
    }

    return resultat;
}

bool application::Traitement_frequence_clignotement(vector<float> vecteur_temps)
{
    bool retour_fonction=0;

    cout << "vecteur_temps.size() " << vecteur_temps.size() << endl;
    if(vecteur_temps.size() <= 95 && vecteur_temps.size() >= 40) //Valeurs empriques ! Peuvent être modifiés
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
        if(vecteur_temps[vecteur_temps.size()-1]-vecteur_temps[vecteur_temps.size()-11] <= 700) //1200 est une valeur empirique ! Peut être modifiée
        {
            retour_fonction=1;
        }
        robustesse=0;
    }

    return retour_fonction;
}

bool application::Detection_convulsions()
{
    float tolerance_angle = 10; //Degs
    float tolerance_norme = 10;
    bool retour=FALSE;
    //On cherche à détecter les changements par rapport à ce qu'on a mémorisé comme position de stabilité
    if ((accel_env-accel_stab)<tolerance_angle) //Pas de variation d'angle, on est a priori statiques ou en train de marcher
    {
        //Dans ce cas, tout va bien
        //on décrémente le compteur de perturbations et on incrémente le compteur de stabilité
        if (cpt_perturb>0) cpt_perturb--;
        cpt_stab++;
    }
    else //Variation d'angle, on veut savoir si on a juste tourné l'accéléro ou si la norme a changé aussi
    {
        if (abs(accel_env.norme_vect()-accel_stab.norme_vect())<tolerance_norme)
        {
            //On est dans le cas où l'accéléromètre est simplement tourné (var d'angle mais pas de norme)
            //Il n'y a donc a priori pas de pb, on change simplement de position d'équilibre
            //Cependant, on prend quand même en compte la possibilité d'une crise donc on ne décrémente pas cpt_perturb
            cpt_stab++;
        }
        else //Variation d'angle et de norme : PB
        {
            cpt_stab=0;
            cpt_perturb++;
        }
    }
    if (cpt_perturb>10) //On a rencontré trop de perturbations, on donne la priorité aux perturbations
    {
        //FAIRE QQCHOSE GENRE UN BIP OU JSP MAIS CA VA PAS PK PAS UNE !EXCEPTION!
        retour = true;
    }
    else
    {
        if (cpt_stab>5) //On est stable depuis suffisamment longtemps
        {
            accel_stab=accel_env;       //Stockage nouvel éq
            cpt_stab = 0;
            cpt_perturb = 0;  //RàZ
        }
    }
    return retour;
}

    ///Méthodes principale
void application::do_one_step_lumiere(float echantillonage_board )
{
    int val_lumiere=ma_board->analogRead(1);
    int val_BP=ma_board->analogRead(2);
    /*char stock_lumiere[100];
    sprintf(stock_lumiere,"Lumiere %d",val_lumiere);
    Serial.println(stock_lumiere);

    char stock_BP[100];
    sprintf(stock_BP,"Bouton poussoir %d",val_BP);
    Serial.println(stock_BP);*/

    //On fait clignotter la LED
    if(bascule) //Cette bascule change d'état chaque seconde
    {
        ma_board->digitalWrite(13,HIGH); //Par nature, la LED intelligente restera dans son état DELAY secondes (cf main) puis pourra ensuite changer d'état
    }
    else
    {
        ma_board->digitalWrite(13,LOW);
    }
    bascule=1-bascule;

    //On stocke la lumière et les temps qui y sont associés dans une map et on traite ces informations
    tableau = Stockage_lumiere(tableau,val_lumiere, echantillonage_board,i);
    epilepsie = Traitement_lumiere(tableau, echantillonage_board);
    /*
    try
    {
        epilepsie = Traitement_lumiere(tableau, echantillonage_board);
    }
    catch(Board::Erreur monErreur)
    {
        Serial.println(monErreur.getErreur());
    }
    */

    //Si la lumière peut provoquer une crise d'épilespsie, alors on incrémente un compteur jusqu'à 3 (sinon on détecte trop facilement des lumières nocives alors que ce n'est pas forcément le cas
    if(epilepsie == 1)
    {
        j++;
        cout<<"ATTENTION CRISE EPP"<<endl;
    }

    if(j==3)
    {
        cout<<"ON RENTRE DANS LA BOUCLE"<<endl;
        if(val_BP == 0)
        {
            while(ma_board->analogRead(2) != 1)
            {
                ma_board->digitalWrite(15,HIGH);
            }
        }
        j=0;
    }
    ma_board->digitalWrite(15,LOW);
    i++;
    sleep(echantillonage_board);
}
void application::do_one_step_convulsions()
{
    //float echantillonage = 10; //Execution de la loop toutes les 10 ms (sans prendre en compte  le tps d'éxec)
    //sleep(echantillonage);
    ma_board->digitalWrite(14,HIGH);
    cout<<"Valeurs mesurees : \nX:"<<ma_board->analogRead(7)-OFFSET<<" Y:"<<ma_board->analogRead(8)-OFFSET<<" Z:"<<ma_board->analogRead(9)-OFFSET<<endl; //!OFFSET pour l'affichage
    cout<<"Valeurs reelles : \nX:"<<accel_env.get_val('X')<<" Y:"<<accel_env.get_val('Y')<<" Z:"<<accel_env.get_val('Z')<<endl;
}
