#ifndef GAME_OVER_H
#define GAME_OVER_H
// Se definen las teclas usadas
#define KEY_1   SDLK_SPACE
#define KEY_2   SDLK_ESCAPE
#define KEY_3   SDLK_RETURN
// Cabeceras
#include <SDL/SDL.h>
#include "escena.h"

class Game_Over : public Escena
{
    public:
        Game_Over(class Nucleo *nucleo);
        ~Game_Over();
		void reset  (void);
		void print  (void);
		void update (void);
		void action (int i_key);

    private:
        class Hi_Scores *hi_scores;
        Uint8 status;
};

#endif
