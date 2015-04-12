#include "galeria.h"
#include <SDL/SDL_image.h>

////////////////////////////////////////////////////////////////////////////////
// Publicas
////////////////////////////////////////////////////////////////////////////////

Galeria :: Galeria ()
{                                                             /* F  C */
    // Se cargan las imagenes del juego

	imagenes[BLOQUES]        = new Image ("bloques.bmp", 1, false, 1, 7);
	imagenes[BLOQUES_MINI]   = new Image ("bloques_mini.bmp", 1, false, 1, 7);
	imagenes[NUMEROS]        = new Image ("numeros.bmp", 1, false, 1, 10);
	imagenes[ARROW]          = new Image ("arrow.png");
	imagenes[FONDO_JUEGO]    = new Image ("fondo_juego.bmp");
	imagenes[FONDO_MENU]     = new Image ("fondo_menu.bmp");
	imagenes[FONDO_OPCIONES] = new Image ("fondo_opciones.bmp");
	imagenes[HI_SCORES]      = new Image ("hi_scores.bmp");
	imagenes[GAME_OVER]      = new Image ("game_over.png", 3, false, 3, 2);

    // Se cargan las fuentes del juego
	fuentes[CHICA]           = new Fuente ("chica.png", true);
	fuentes[CHICA2]          = new Fuente ("chica2.png", true);
}

Galeria :: ~Galeria ()
{
    // Se destruyen todas las instancias contenedoras de las imagenes y fuentes
	delete imagenes[BLOQUES];
	delete imagenes[BLOQUES_MINI];
	delete imagenes[NUMEROS];
	delete imagenes[FONDO_JUEGO];
	delete imagenes[FONDO_MENU];
	delete imagenes[FONDO_OPCIONES];
	delete imagenes[ARROW];
	delete imagenes[HI_SCORES];
	delete imagenes[GAME_OVER];

	delete fuentes[CHICA];
}

class Image * Galeria :: get_imagen (enum codigo_imagen codigo_imagen)
{
	return imagenes[codigo_imagen];
}

class Fuente * Galeria :: get_fuente (enum codigo_fuente indice)
{
	return fuentes[indice];
}
