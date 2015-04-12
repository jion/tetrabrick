#include <stdexcept>
#include "nucleo.h"
#include "escena.h
// --Scenes--
#include "juego.h"
#include "opciones.h"
#include "menu.h"
#include "game_over.h"

////////////////////////////////////////////////////////////////////////////////
//// Publicas
////////////////////////////////////////////////////////////////////////////////

Nucleo::Nucleo(int i_fullscreen, int i_depth) try
{
    // Inicia la SDL
    init_SDL();

    // Carga la configuracion, los graficos y los utiles
    r_configuration = new Configuration;
    r_galeria       = new Galeria;
    r_utils         = new Utils;

    // Inicia a 0 todo lo referido al subsitema Multiplayer
    d_multiplayer = NULL;
    s_multiplayer = NULL;

    // Crea la Display Surface
    create_DisplaySurface(i_fullscreen, i_depth);

    // Crea las escenas
    e_juego  = new Juego(this);
    e_menu   = new Menu(this);
    e_actual = e_menu;

    // Configuraciones varias
    SDL_EnableKeyRepeat(100, 30); //TODO: Pasarlo directamente a modulo Configuration
    //SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

    // Transfiere el control al bucle principal
    bucle_principal();

} catch( exception& e ) throw(e.what());

Nucleo::~Nucleo()
{
    delete galeria;
    delete configuration;
    delete utils:

    delete menu;
	delete juego;

	if(s_multiplayer) delete s_multiplayer;
}

void Nucleo::terminar(int reason)
{
	//TODO: Switch reasons
}

////////////////////////////////////////////////////////////////////////////////
// Privadas
////////////////////////////////////////////////////////////////////////////////


void Nucleo::bucle_principal (void)
{

}

void Nucleo::init_SDL(void)
{
    Uint32 flags = SDL_INIT_VIDEO | SDL_INIT_TIMER;

    // Configura los modulos activados
    if(configuration->audio->enabled) flags |= SDL_INIT_AUDIO;
    if(configuration->input->jostick) flags |= SDL_INIT_JOYSTICK;

    // Inicia la SDL
	if (SDL_Init(flags) == -1) throw std::runtime_error(SDL_GetError());

	// Sale por SDL_Quit
	atexit(SDL_Quit);
}

void Nucleo::create_DisplaySurface(int i_fullscreen, int i_depth)
{
	Uint32 flags = 0, res_w, res_h;

	// Se configuran las flags
	if(fullscreen) flags |= SDL_FULLSCREEN; else
	if(r_configuration->display->fullscreen)  flags |= SDL_FULLSCREEN;
	if(r_configuration->display->hwsurface) { flags |= SDL_HWSURFACE;
	if(r_configuration->display->doublebuf)   flags |= SDL_DOUBLEBUF; }

	// Se configura la profundidad de colores
	if(i_depth == 0) i_depth = r_configuration->display->depth;

    // Se configura la resolucion
    switch(r_configuration->display->resolution)
    {
        case SM_640X480:
            res_w = 640;
            res_h = 480;
            break;
        case SM_800X600:
            res_w = 800;
            res_h = 600;
            break;
        case SM_1024X768:
            res_w = 1024;
            res_h = 768;
            break;
    }

    // Crea la ventana
    sdls_screen = SDL_SetVideoMode(res_w, res_h, depth, flags);
    if(sdls_screen == NULL) throw std::runtime_error(SDL_GetError());

    // Extras de la ventana
	SDL_WM_SetCaption ("TetraBrick (version: 0.4)", NULL);
	SDL_ShowCursor(SDL_DISABLE);
}



////////////////////////////////////////////////////////////////////////////////
// Descartadas
////////////////////////////////////////////////////////////////////////////////

/* void Nucleo::red_telon(void)
{
    SDL_Surface *telon;
    // Se define la superficie de la grafica de la ficha.
    Uint32 rmask, gmask, bmask, amask;

    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x00000000;
    #else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0x00000000;
    #endif

    telon = SDL_CreateRGBSurface(SDL_SWSURFACE, 800, 600, 32, rmask, gmask, bmask, amask);
    if(telon == NULL)
        throw std::runtime_error( SDL_GetError() );

    SDL_FillRect(telon, 0, SDL_MapRGB(telon->format, 0, 0, 0));
    SDL_SetAlpha(telon, SDL_SRCALPHA | SDL_RLEACCEL, 128);

    SDL_BlitSurface(old_scene, 0, screen, 0);
    SDL_BlitSurface(telon, 0, screen, 0);

    SDL_FreeSurface(telon);
} */

/* int Nucleo :: sincronizar_fps (void)
{
	static int t;
	static int tl = SDL_GetTicks ();
	static int frecuencia = 1000 / 100;
	static int tmp;
#ifdef DEBUG
	static int fps = 0;
	static int t_fps = 0;
#endif

	t = SDL_GetTicks ();

#ifdef DEBUG
	if ((t - t_fps) >= 1000)
	{
		printf("FPS = %d\n", fps);
		fps = 0;
		t_fps += 1000 + 1;
	}

	fps ++
#endif

	if ((t - tl) >= frecuencia)
	{
		tmp = (t - tl) / frecuencia;
		tl += tmp * frecuencia;
		return tmp;
	}
	else
	{
		SDL_Delay (frecuencia - (t - tl));
		tl += frecuencia;
		return 1;
	}
}*/

/*void Nucleo::input_refresh (void)
{
	static SDL_Event event;

	while(SDL_PollEvent(&event))
	{
	    if(event.type == SDL_KEYDOWN)
	        for(int i=0; i < actual->configured_keys.size(); i++)
                if(event.key.keysym.sym == actual->configured_keys[i])
                    actual->action(i);

		if(event.type == SDL_QUIT) actual->action(-1);
	}
}*/

/*void Nucleo :: pantalla_completa (void)
{
	SDL_WM_ToggleFullScreen(screen);
}*/
