#include "menu.h"
#include "nucleo.h"
#include "galeria.h"


    /**
    Modo un jugador
        Jugar
        Opciones de juego
        Volver
    Modo multijugador
        Unirse
            A servidor dedicado
            A partida en internet
            A partida en red
            Volver
        Crear nueva partida
        Volver
    Opciones
    Salir
    **/

using namespace std;

Menu :: Menu (class Nucleo *nucleo) : Escena (nucleo)
{
	fondo  = nucleo->galeria->get_imagen (FONDO_MENU);
    fuente = nucleo->galeria->get_fuente(CHICA);

    configured_keys.push_back (SDLK_UP);
    configured_keys.push_back (SDLK_DOWN);
    configured_keys.push_back (SDLK_RETURN);
    configured_keys.push_back (SDLK_ESCAPE);

	reset();
}

Menu :: ~Menu ()
{

}

void Menu::reset (void)
{
    menu_index = 0;
    item_index = 0;

    actualizar_titulos();
}

void Menu::print (void)
{
    const char* char_item;

    fondo->imprimir(nucleo->screen);

    for( int i = 0; i < 4 && item[i] != "\0"; i++ )
    {
        char_item = item[i].c_str();
        fuente->imprimir(nucleo->screen, (char*) char_item,   250, 200 + (50*i) );
    }

    nucleo->galeria->get_imagen(ARROW)->imprimir(nucleo->screen, 150, 200 + (50*item_index) );

    SDL_Flip(nucleo->screen);
}

void Menu::update (void)
{

}


void Menu::action (int i_key)
{
    if(i_key == -1) nucleo->terminar();

    switch( configured_keys[i_key] )
    {
        case  SDLK_UP:  // UP
            item_index--;
            if(item_index < 0) item_index++;
            break;

        case  SDLK_DOWN: // DOWN
            item_index++;
            if(item[item_index] == "\0") item_index--;
            break;

        case  SDLK_RETURN: // ENTER

            switch( menu_index )
            {
                case 0: // Menu Principal
                    switch( item_index )
                    {
                        case 0: menu_index = 1; break;                                   // Modo un jugador
                        case 1: menu_index = 2; break;                                   // Modo multijugador
                        case 2: break;nucleo->cambiar_escena( ESCENA_OPCIONES ); return; // Opciones
                        case 3: nucleo->terminar(); break; // Salir
                    }
                    break;

                case 1: // Modo un jugador
                    switch( item_index )
                    {
                        case 0: nucleo->cambiar_escena( ESCENA_JUEGO ); return; // Jugar
                        case 1: return;                                          // Opciones de juego
                        case 2: menu_index = 0; break;                          // Volver
                    }
                    break;

                case 2: // Modo multijugador
                    switch( item_index )
                    {
                        case 0: menu_index = 3; break;  // Unirse
                        case 1: return;                                          // Crear nueva partida
                        case 2: menu_index = 0; break;                          // Volver
                    }
                    break;

                case 3: // Unirse
                    switch( item_index )
                    {
                        case 0: return;                     // Modo un jugador
                        case 1: return;                     // Modo multijugador
                        case 2: return; // Opciones
                        case 3: menu_index = 2; break; // Salir
                    }
                    break;
            }
            actualizar_titulos();
            break;

        case  SDLK_ESCAPE: // ESCAPE
            nucleo->terminar();
            break;
    }
}

////////////////////////////////////////////////////////////////////////////////
// Privadas
////////////////////////////////////////////////////////////////////////////////

void Menu::actualizar_titulos(void)
{
    item_index = 0;

    items.erase(items.begin(), items.end());

    switch( menu_index )
    {
        case 0: // Menu Principal
            item[0] = "Modo un jugador";
            item[1] = "Modo multijugador";
            item[2] = "Opciones";
            item[3] = "Salir";
            break;
        case 1: // Modo un jugador
            item[0] = "Jugar";
            item[1] = "Opciones de juego";
            item[2] = "Volver";
            item[3] = "\0";
            break;
        case 2: // Modo multijugador
            item[0] = "Unirse";
            item[1] = "Crear nueva partida";
            item[2] = "Volver";
            item[3] = "\0";
            break;
        case 3: // Unirse
            item[0] = "A servidor dedicado";
            item[1] = "A partida en internet";
            item[2] = "A partida en red";
            item[3] = "Volver";
            break;
    }
}
