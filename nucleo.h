#ifndef nucleo_h
#define nucleo_h
#include <SDL/SDL.h>
#include "galeria.h"
#include "configuration.h"
#include "utils.h"


using namespace std;

/// Tipos de Escena dentro del programa
enum escenas {ESCENA_MENU, ESCENA_JUEGO};

class Nucleo
{
    public:
		Nucleo(int i_fullscreen, int i_depth);
		~Nucleo();
		void terminar(int reason);

        class Galeria       *r_galeria;       // Galeria de graficas
        class Configuration *r_configuration; // Todos los datos de config.dat
        class Utils         *r_utils;         // Red telon, messagebox, etc
        SDL_Surface         *sdls_screen;     // Puntero a la Display Surface
        struct {
            int enabled; // 1 si esta activado el subsistema, 0 si no lo esta.
            /*TODO: Punteros a toda la informacion
                    global del subsistema Multiplayer*/
        } d_multiplayer;

    private:
        void init_SDL(void);
        void create_DisplaySurface(int i_fullscreen, int i_depth);
		void bucle_principal(void);
		void cambiar_escena(enum escenas nueva);
		void capture_events(void);

  		class Escena      *e_actual;      //  }
  		class Menu        *e_menu;        //  } 3 Escenas.
		class Juego       *e_juego;       //  }
		class Multiplayer *s_multiplayer; /* Subsistema que maneja toda la
                                          conectividad del juego. */
};

/*
    public:
		Nucleo(int i_fullscreen, int i_depth);
		~Nucleo();
		void bucle_principal (void);
		void cambiar_escena  (enum escenas nueva);
		void red_telon       (void);
		void terminar        (void);

        SDL_Surface          *screen; // --> The Screen
        Configuration        *configuration;
		class Galeria        *galeria;

    private:
		void iniciar_ventana   (Uint8 resolucion, bool fullscreen);
		void pantalla_completa (void);
		void input_refresh     (void);
		int  sincronizar_fps   (void);

        SDL_Surface     *old_scene;
  		class Escena    *actual;
		class Juego     *juego;
		class Opciones  *opciones;
		class Menu      *menu;
		class Game_Over *game_over;

        //TODO: Averiguar si sirven para algo.
        bool salir;
		int  menu_index;
};*/

#endif
