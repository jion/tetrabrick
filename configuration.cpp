#include <fstream>
#include <stdexcept>
#include <SDL/sdl.h>
#include "configuration.h"

using namespace std;
////////////////////////////////////////////////////////////////////////////////
// Public
////////////////////////////////////////////////////////////////////////////////

Configuration::Configuration()
{
    // Se setean todos los items defaults como base
    set_default(DEFAULT_ALL);

    // Se sobreescriben con los datos de config.dat
    if(load_configuration() == -1) {       // Si no se puede abrir la configuracion
        if(save_configuration() == 0) {    // Se intenta crear el archivo con defaults
            if(load_configuration() == -1) // Si a pesar de crearlo no se puede abrir
                throw runtime_error("Configuration: config.dat - Access denied");
        }
        else {                              // Si tampoco se puede crear el archivo
            throw runtime_error("Configuration: config.dat - Access denied");
        }
    }
}

Configuration::~Configuration()
{
}

void Configuration::set_default(Uint8 what_default)
{
    switch(what_default)
    {
        case DEFAULT_ALL:
        case DEFAULT_DISPLAY:
            display.resolution = SM_800X600;
            display.fullscreen = 0;
            display.depth      = 0;
            display.hwsurface  = 0;
            display.doublebuf  = 0;
            if(what_default != DEFAULT_ALL)
                break;

        case DEFAULT_AUDIO:
            audio.enabled = 1;
            audio.music   = 1;
            audio.soundfx = 1;
            //audio.path    = "music/";
            if(what_default != DEFAULT_ALL)
                break;

        case DEFAULT_INPUT:
            input.jostick         = 0;
            input.repeat_delay    = 100;
            input.repeat_interval = 30;
            input.k_left_         = SDLK_LEFT;
            input.k_right_        = SDLK_RIGHT;
            input.k_rotate_       = SDLK_UP;
            input.k_down_         = SDLK_DOWN;
            input.k_down_all_     = SDLK_SPACE;
            input.k_pause_        = SDLK_p;
            if(what_default != DEFAULT_ALL)
                break;
        case DEFAULT_GENERAL:
            //general.theme_path = "default.pck";
            if(what_default != DEFAULT_ALL)
                break;

        case DEFAULT_HISCORES:
            for(int i=0;i <10;i++)
                hiscores[i] = (hi_scores) { 0, 1, 1, 999999 };
    }
}

int Configuration::save_configuration()
{
    // Save configuration data
	ofstream os(CONFIG_DAT,std::ios::binary);
	if(!os.is_open()) return -1;

    // Display
    os.write(reinterpret_cast<const char*>(&display.resolution),    sizeof(Uint8));
    os.write(reinterpret_cast<const char*>(&display.fullscreen),    sizeof(Uint8));
    os.write(reinterpret_cast<const char*>(&display.depth),         sizeof(Uint8));
    os.write(reinterpret_cast<const char*>(&display.hwsurface),     sizeof(Uint8));
    os.write(reinterpret_cast<const char*>(&display.doublebuf),     sizeof(Uint8));

    // Audio
    os.write(reinterpret_cast<const char*>(&audio.enabled),         sizeof(Uint8));
    os.write(reinterpret_cast<const char*>(&audio.music),           sizeof(Uint8));
    os.write(reinterpret_cast<const char*>(&audio.soundfx),         sizeof(Uint8));
    //os.write(reinterpret_cast<const char*>(&audio.path),            sizeof(char)*15);

    // Input
    os.write(reinterpret_cast<const char*>(&input.jostick),         sizeof(Uint8));
    os.write(reinterpret_cast<const char*>(&input.repeat_delay),    sizeof(Uint16));
    os.write(reinterpret_cast<const char*>(&input.repeat_interval), sizeof(Uint16));
    os.write(reinterpret_cast<const char*>(&input.k_left_),         sizeof(SDLKey));
    os.write(reinterpret_cast<const char*>(&input.k_right_),        sizeof(SDLKey));
    os.write(reinterpret_cast<const char*>(&input.k_rotate_),       sizeof(SDLKey));
    os.write(reinterpret_cast<const char*>(&input.k_down_),         sizeof(SDLKey));
    os.write(reinterpret_cast<const char*>(&input.k_down_all_),     sizeof(SDLKey));
    os.write(reinterpret_cast<const char*>(&input.k_pause_),        sizeof(SDLKey));

    // General
    //os.write(reinterpret_cast<const char*>(&general.theme_path),    sizeof(Uint8)*15);

	if(!os.good()) return -1;
	os.close();
	return 0;
}

////////////////////////////////////////////////////////////////////////////////
// Private
////////////////////////////////////////////////////////////////////////////////

int Configuration::load_configuration()
{
    // Load configuration data
	ifstream is(CONFIG_DAT, ios::binary);
	if(!is.is_open()) return -1;

    // Display
    is.read(reinterpret_cast<char*>(&display.resolution),    sizeof(Uint8));
    is.read(reinterpret_cast<char*>(&display.fullscreen),    sizeof(Uint8));
    is.read(reinterpret_cast<char*>(&display.depth),         sizeof(Uint8));
    is.read(reinterpret_cast<char*>(&display.hwsurface),     sizeof(Uint8));
    is.read(reinterpret_cast<char*>(&display.doublebuf),     sizeof(Uint8));

    // Audio
    is.read(reinterpret_cast<char*>(&audio.enabled),         sizeof(Uint8));
    is.read(reinterpret_cast<char*>(&audio.music),           sizeof(Uint8));
    is.read(reinterpret_cast<char*>(&audio.soundfx),         sizeof(Uint8));
    //is.read(reinterpret_cast<char*>(&audio.path),            sizeof(char)*15);

    // Input
    is.read(reinterpret_cast<char*>(&input.jostick),         sizeof(Uint8));
    is.read(reinterpret_cast<char*>(&input.repeat_delay),    sizeof(Uint16));
    is.read(reinterpret_cast<char*>(&input.repeat_interval), sizeof(Uint16));
    is.read(reinterpret_cast<char*>(&input.k_left_),         sizeof(SDLKey));
    is.read(reinterpret_cast<char*>(&input.k_right_),        sizeof(SDLKey));
    is.read(reinterpret_cast<char*>(&input.k_rotate_),       sizeof(SDLKey));
    is.read(reinterpret_cast<char*>(&input.k_down_),         sizeof(SDLKey));
    is.read(reinterpret_cast<char*>(&input.k_down_all_),     sizeof(SDLKey));
    is.read(reinterpret_cast<char*>(&input.k_pause_),        sizeof(SDLKey));

    // General
    //is.read(reinterpret_cast<char*>(&general.theme_path),    sizeof(Uint8)*15);

 	is.close();
    return 0;
}
