/* *************************************************************************
 *   Tetrabrick                                                            *
 *   Copyright (C) 2007 by Manuel Schnidrig                                *
 *   el.manu@gmail.com                                                     *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include <math.h>
#include "juego.h"
#include "nucleo.h"
#include "tablero.h"
#include "score.h"

////////////////////////////////////////////////////////////////////////////////
//// Publicas
////////////////////////////////////////////////////////////////////////////////

Juego::Juego (class Nucleo *nucleo) : Escena (nucleo)
{
    // Crea los componentes
    t_tablero = new Tablero(nucleo->galeria);
    c_score   = new Score  (nucleo->galeria, &score);
    c_lines   = new Score  (nucleo->galeria, &lines);
    c_level   = new Score  (nucleo->galeria, &level);
    i_fondo   = nucleo->galeria->get_imagen(FONDO_JUEGO);

	reset();
}

Juego::~Juego ()
{
    // Destruye los componentes
    delete t_tablero;
    delete c_score;
    delete c_lines;
    delete c_level;
}

void Juego::reset (void)
{
    score   = 0;
    lines   = 0;
    level   = 0;
    o_speed = O_SPEED; //1000
    x_speed = X_SPEED; //100
    speed   = o_speed;
    lines_per_level = LINES_PER_LEVEL; //15;
    _pause    = false;
    _gameover = false;
    tablero->reiniciar();
}

void Juego::print (void)
{
    fondo    ->imprimir(SCREEN);
    t_tablero->imprimir(SCREEN, 27,  0, 350, 50);
    c_score  ->imprimir(SCREEN, 10,  28,  523);
    c_lines  ->imprimir(SCREEN, 4,   580, 35);
    c_level  ->imprimir(SCREEN, 2,   580, 80);
}

void Juego::start(void)
{
    static SDL_Event event;

    if(_gameover) return;
    while(!i_stop) {
        while(_pause) {
            // TODO: Print Pause widget que va a eliminar lo de abajo
            // TODO: Refrescar tiempo
            if(SDL_PollEvent(&event)) {
                switch(event.type)
                {
                    case SDL_KEYDOWN:
                        if( event.key.keysym.sym == KEY_PAUSE ) _pause = false;
                        break;

                    case SDL_QUIT:
                        exit(0);
                }
            }

        }


    }




    SDLKey sdlk_event;

    while(!i_stop)
    {
        sdlk_event = events(); // Recoje eventos---------------------

        //--- aca los labura

        if( (TimeLeft(speed) == 0) || (sdlk_event == KEY_DOWN) )
            switch(tablero->bajar_uno)
            {
                case TAB_BAJAUNO:

                    break;
                case TAB_COLISION:
                        // Actualizacion del puntaje y del nivel
                        lines += tablero->lineas;
                        score += (Uint32) pow(3, tablero->lineas);
                        level  = lines / lines_per_level;
                        speed  = o_speed - ( level * x_speed );
                        if(speed < 0) speed = 0; /*--> Evita error x velocidad negativa
                                                       (¿Sera humanamente posible llegar
                                                        a esta nivel? :P ) */
                    break;
                case TAB_GAMEOVER:
                    break;
            }
    }
}

void Juego::action(int i_key)
{
    if(i_key == -1) nucleo->terminar();
    if(configured_keys[i_key] == KEY_ESC) nucleo->cambiar_escena(ESCENA_MENU);

    if( !pause && !gameover )
    {
        if(configured_keys[i_key] == KEY_LEFT)    tablero->izquierda();
        if(configured_keys[i_key] == KEY_RIGHT)   tablero->derecha();
        if(configured_keys[i_key] == KEY_ROTATE)  tablero->rotar();
        if(configured_keys[i_key] == KEY_DOWN)    tablero->bajar_uno();
        if(configured_keys[i_key] == KEY_DOWNALL) tablero->bajar_todo();
    }

    if( !gameover )
    {
        if(configured_keys[i_key] == KEY_PAUSE) pause = !pause;
    }
}

////////////////////////////////////////////////////////////////////////////////
//// Privadas
////////////////////////////////////////////////////////////////////////////////

Uint32 Juego::TimeLeft( Uint32 intervalo )
{
    static Uint32 next_time = 0;
    Uint32 now;

    now = SDL_GetTicks();
    if ( next_time <= now )
    {
        next_time = now + intervalo;
        return(0);
    }
    return(next_time-now);
}
