#include <stdexcept>
#include "tablero.h"
#include "galeria.h"
#include "image.h"
#include "ficha.h"

////////////////////////////////////////////////////////////////////////////////
//// Publicas
////////////////////////////////////////////////////////////////////////////////

Tablero::Tablero(Galeria *galeria)
{
    f_actual  = new Ficha(galeria);
    f_next    = new Ficha(galeria);
    g_bloques = galeria->get_imagen(BLOQUES);

    //** Se define la superficie del tablero.
    //TODO: Utils debera tener un crear superficie. Todo este chirimbolo no lo quiero aca.
    Uint32 rmask, gmask, bmask, amask;

    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
    #else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
    #endif

    sdls_tablero = SDL_CreateRGBSurface(SDL_SWSURFACE, 240, 480, 32, rmask, gmask, bmask, amask);
    if(sdls_tablero == NULL)
        throw std::runtime_error( SDL_GetError() );

    SDL_Surface *tmp = sdls_tablero;

	sdls_tablero = SDL_DisplayFormat(tmp);
	SDL_FreeSurface(tmp);

    // Se reinician todos los valores
    reset();
}

Tablero::~Tablero()
{
    delete actual;
    delete next;
    SDL_FreeSurface(sdls_tablero);
}

void Tablero::izquierda( void )
{
    x -= 1;
    if(colision()) x += 1;
}

void Tablero::derecha( void )
{
    x += 1;
    if(colision()) x -= 1;
}

void Tablero::rotar( void )
{
    f_actual->rotar(0);
    if(colision())
        f_actual->rotar(1);
}

// La funcion retorna:
//  1: Hubo colision.
// -1: La ficha no puede ser colocada porque el tablero esta lleno. Game Over.
int Tablero::bajar_todo( void )
{
    int ret = 0;
    while ( !(ret = bajar_uno()) );
    return ret;
}

// La funcion retorna:
//  0: Se bajo la ficha. No hay colisiones
//  1: Hubo colision.
// -1: La ficha no puede ser colocada porque el tablero esta lleno. Game Over.
int Tablero::bajar_uno( void )
{
    if(i_colision)
    {
        borrar_lineas();
        f_actual->nueva_ficha(f_next->valor);
        f_next->nueva_ficha()
        x = 4;
        y = 0;
        if(colision()) return TAB_GAMEOVER;
        i_colision = false;
    } else {
        y++;
        if(colision())
        {
            y--;
            actualizar_tablero();
            obtener_lineas();
            i_colision = true;
            return TAB_COLISION;
        }
    }
    return TAB_BAJAUNO;
}

void Tablero::print(SDL_Surface *dst, int x, int y, int nx, int ny)
{
    SDL_Rect dstrect = {x, y, 0, 0};

    SDL_BlitSurface(sdls_tablero, 0, dst, &dstrect);
    if( !i_colision )
        f_actual->imprimir(dst, (this->x * 24) + x, (this->y * 24) + y);
    f_next->imprimir(dst, nx, ny);
}

void Tablero::reset(void)
{
    x = 4;
    y = 0;
    i_lineas = 0;
    memset(i_tablero,  0, sizeof(i_tablero));
    memset(i_lines,    0, sizeof(i_lines));
    SDL_FillRect(sdls_tablero, 0, 0);
    f_actual->nueva_ficha();
    f_next->nueva_ficha();
    i_colision = false;
}

////////////////////////////////////////////////////////////////////////////////
//// Privadas
////////////////////////////////////////////////////////////////////////////////

bool Tablero::colision( void )
{
    for(int i=0; i < 4; i++)
        for(int j=0; j < 4; j++)
            if(f_actual->data[f_actual->posicion][i][j])
                if( ((y + j) > 19) ||
                    ((x + i) > 9)  ||
                    ((x + i) < 0)  ||
                    (i_tablero[y+j][x+i]) ) return true;

    return false;
}

void Tablero::actualizar_tablero(void)
{
    for(int i=0; i < 4; i++)
        for(int j=0; j < 4; j++)
            if(f_actual->data[f_actual->posicion][j][i])
            {
                // Datos
                tablero[y+j][x+i] = f_actual->valor;
                // Graficos
                bloques->imprimir( sdls_tablero, 24 * (i+x), 24 * (j+y), f_actual->valor-1);
            }
}

void Tablero::borrar_lineas(void)
{
    Uint8* temp = (Uint8*)&tablero;
    Uint8 i;

    // TODO: BUG: Revisar que se limpie la ultima fila.
    memcpy(temp, tablero, sizeof(tablero));
    for(i=0; i < 4; i++)
        if(i_lines[i])
        {
            memmove(temp+10, temp, sizeof(Uint8)*(10*i_lines[i]));
            i_lines[i] = 0;
        }

    //TODO: Actualiza completamente el grafico del tablero.Fix it.
    SDL_FillRect(sdls_tablero, 0, 0);

    for(i=0;i <10;i++)
        for(int j=0; j < 20; j++)
            if(tablero[j][i])
                bloques->imprimir( sdls_tablero, 24 * i, 24 * j, tablero[j][i] - 1);
}

void Tablero::obtener_lineas(void)
{
    i_lineas = 0;
    for(int i = y; (i < (y + 4)) && (i < 20); i++)
        if  (
                    (bool) tablero[i][0] && (bool) tablero[i][1] &&
                    (bool) tablero[i][2] && (bool) tablero[i][3] &&
                    (bool) tablero[i][4] && (bool) tablero[i][5] &&
                    (bool) tablero[i][6] && (bool) tablero[i][7] &&
                    (bool) tablero[i][8] && (bool) tablero[i][9]
            ) {
            i_lineas++;
            lines[i-y] = i;
            }
}
