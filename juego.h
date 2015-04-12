#ifndef juego_h
#define juego_h

// Atajos config.dat
#define KEY_LEFT        nucleo->configuration->input->k_left_
#define KEY_RIGHT       nucleo->configuration->input->k_right_
#define KEY_ROTATE      nucleo->configuration->input->k_rotate_
#define KEY_DOWN        nucleo->configuration->input->k_down_
#define KEY_DOWNALL     nucleo->configuration->input->k_down_all_
#define KEY_PAUSE       nucleo->configuration->input->k_pause_
#define O_SPEED         nucleo->configuration->game->o_speed
#define X_SPEED         nucleo->configuration->game->x_speed
#define LINES_PER_LEVEL nucleo->configuration->game->lines_per_level
// Atajos nucleo
#define SCREEN          nucleo->sdls_screen


// Cabeceras
#include <SDL/SDL.h>
#include "escena.h"

class Juego : public Escena
{
	public:
		Juego(class Nucleo *nucleo);
		~Juego();
		void start(void);
		void stop (void); // Tambien funciona como pausa.
		void reset(void);

	private:
        void print(void);
        void events(void);
        void pause(void);
        void game_over(void); // En singleplayer, Muestra cuadros de game over.
        Uint32 TimeLeft( Uint32 intervalo ); // Cuenta milisegundos

        // Game data
        Uint32 o_speed;         //--> Velocidad Inicial
        Uint32 x_speed;         //--> Multiplicador x nivel
        Uint8  lines_per_level; //--> Lineas necesarias para aumentar el nivel
        Uint32 speed;
        Uint32 score;
        Uint32 lines;
        Uint32 level;

        // Estados del juego
        bool _pause;
        bool _gameover;

        // Componentes de la escena
		class Tablero   *t_tablero;
		class Score     *c_score;
		class Score     *c_lines;
		class Score     *c_level;
		class Image     *i_fondo;
};

#endif
