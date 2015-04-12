#include <stdexcept>
#include "ficha.h"
#include "galeria.h"

////////////////////////////////////////////////////////////////////////////////
//// Publicas
////////////////////////////////////////////////////////////////////////////////

Ficha::Ficha( Galeria *galeria )
{
    bloques = galeria->get_imagen( BLOQUES );

    valor    = 0;
    posicion = 0;
    memset( data, 0, sizeof( data ) );

    //TODO: Utils..
    // Se define la superficie de la grafica de la ficha.
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

    pieza = SDL_CreateRGBSurface(SDL_SWSURFACE, 96, 96, 32, rmask, gmask, bmask, amask);
    if(pieza == NULL)
        throw std::runtime_error( SDL_GetError() );

    SDL_Surface *tmp = sdls_tablero;

	sdls_tablero = SDL_DisplayFormat(tmp);
	SDL_FreeSurface(tmp);
}

Ficha::~Ficha()
{
    SDL_FreeSurface(pieza);
}

void Ficha::nueva_ficha( int ficha = 0 )
{
    if(ficha) valor = ficha;
    else valor = (int) ( rand () % 7 + 1 );

    posicion = 0;
    actualizar();
}

void Ficha::rotar( int lado )
{
    if( lado == 0 )
    {
        posicion++;
        if( posicion > 3 ) posicion = 0;
    }
    else if( lado == 1 )
    {
        posicion--;
        if( posicion < 0 ) posicion = 3;
    }
    actualizar();
}

void Ficha::imprimir( SDL_Surface *dst, int x, int y )
{
        SDL_Rect dstrect = {x, y, 0, 0};
        SDL_BlitSurface(pieza, 0, dst, &dstrect);
}

////////////////////////////////////////////////////////////////////////////////
//// Privadas
////////////////////////////////////////////////////////////////////////////////

void Ficha::actualizar(void)
{
    memset( data, 0, sizeof( data ) );
    SDL_FillRect(pieza, 0, 0);

    switch(valor)
    {
        case 1:
            data[0][0][0] = true; data[0][1][0] = true;
            data[0][0][1] = true; data[0][2][0] = true;

            data[1][0][0] = true; data[1][1][1] = true;
            data[1][1][0] = true; data[1][1][2] = true;

            data[2][2][0] = true; data[2][1][1] = true;
            data[2][2][1] = true; data[2][0][1] = true;

            data[3][0][0] = true; data[3][0][2] = true;
            data[3][0][1] = true; data[3][1][2] = true;
            break;

        case 2:
            data[0][0][0] = true; data[0][1][1] = true;
            data[0][0][1] = true; data[0][2][1] = true;

            data[1][0][0] = true; data[1][0][1] = true;
            data[1][1][0] = true; data[1][0][2] = true;

            data[2][0][0] = true; data[2][2][0] = true;
            data[2][1][0] = true; data[2][2][1] = true;

            data[3][1][0] = true; data[3][1][2] = true;
            data[3][1][1] = true; data[3][0][2] = true;
            break;

        case 3:
            for( int i=0; i<4; i++ )
            {
                data[i][0][0] = true; data[i][1][1] = true;
                data[i][1][0] = true; data[i][0][1] = true;
            }
            break;

        case 4:
            data[0][1][0] = true; data[0][1][1] = true;
            data[0][0][1] = true; data[0][2][1] = true;

            data[1][0][0] = true; data[1][1][1] = true;
            data[1][0][1] = true; data[1][0][2] = true;

            data[2][0][0] = true; data[2][1][1] = true;
            data[2][1][0] = true; data[2][2][0] = true;

            data[3][1][0] = true; data[3][0][1] = true;
            data[3][1][1] = true; data[3][1][2] = true;
            break;

        case 5:
            data[0][0][0] = true; data[0][0][2] = true;
            data[0][0][1] = true; data[0][0][3] = true;

            data[2][0][0] = true; data[2][0][2] = true;
            data[2][0][1] = true; data[2][0][3] = true;

            data[1][0][0] = true; data[1][2][0] = true;
            data[1][1][0] = true; data[1][3][0] = true;

            data[3][0][0] = true; data[3][2][0] = true;
            data[3][1][0] = true; data[3][3][0] = true;
            break;

        case 6:
            data[0][1][0] = true; data[0][0][1] = true;
            data[0][2][0] = true; data[0][1][1] = true;

            data[2][1][0] = true; data[2][0][1] = true;
            data[2][2][0] = true; data[2][1][1] = true;

            data[1][0][0] = true; data[1][1][1] = true;
            data[1][0][1] = true; data[1][1][2] = true;

            data[3][0][0] = true; data[3][1][1] = true;
            data[3][0][1] = true; data[3][1][2] = true;
            break;

        case 7:
            data[0][0][0] = true; data[0][1][1] = true;
            data[0][1][0] = true; data[0][2][1] = true;

            data[2][0][0] = true; data[2][1][1] = true;
            data[2][1][0] = true; data[2][2][1] = true;

            data[1][1][0] = true; data[1][0][1] = true;
            data[1][1][1] = true; data[1][0][2] = true;

            data[3][1][0] = true; data[3][0][1] = true;
            data[3][1][1] = true; data[3][0][2] = true;
            break;
    }

    for ( int i = 0; i < 4; ++i )
        for ( int j = 0; j < 4; ++j )
            if( data[posicion][i][j] )
                bloques->imprimir( pieza, i * 24, j * 24, valor-1 );
}

void Ficha::carga_valores(void)
{
    typedef Uint8 bloque[4][4];

    bloque b1[4] = {
        {
            {0,0,3,0},
            {0,0,3,0},
            {0,3,3,0},
            {0,0,0,0}
        }, {
            {0,3,0,0},
            {0,3,3,3},
            {0,0,0,0},
            {0,0,0,0}
        }, {
            {0,3,3,0},
            {0,3,0,0},
            {0,3,0,0},
            {0,0,0,0}
        }, {
            {0,3,3,3},
            {0,0,0,3},
            {0,0,0,0},
            {0,0,0,0}
        }
    };

}
