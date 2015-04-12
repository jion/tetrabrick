#include "game_over.h"
#include "nucleo.h"
#include "hiscores.h"
#include "galeria.h"

Game_Over::Game_Over(class Nucleo *nucleo) : Escena (nucleo)
{
    //Reservar la cantidad
    configured_keys.push_back(KEY_1);
    configured_keys.push_back(KEY_2);
    configured_keys.push_back(KEY_3);

    hi_scores = new Hi_Scores( nucleo );
}

Game_Over::~Game_Over()
{
    delete hi_scores;
}

void Game_Over::reset()
{
    status = 0;
}

void Game_Over::print()
{
    static int a=1;
    if(a==1) {
    //nucleo->red_telon();
    a=0;
    }

    switch(status)
    {
        case 0:
            nucleo->galeria->get_imagen(GAME_OVER)->imprimir(scene, 50,200);
            break;
        case 1:
            hi_scores->show();
    }
}

void Game_Over::update()
{
}

// Cualquiera de las 3 teclas hara que se pase al siguiente status
void Game_Over::action(int i_key)
{
    if( status == 0 ) status = 1;
    else nucleo->cambiar_escena(ESCENA_MENU);
}
