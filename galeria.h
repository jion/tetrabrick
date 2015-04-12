#ifndef galeria_h
#define galeria_h
#include "image.h"
#include "fuente.h"

/// Imagenes dentro de la Galeria
enum codigo_imagen
{
	BLOQUES,
	BLOQUES_MINI,
	NUMEROS,
	FONDO_JUEGO,
	FONDO_MENU,
	FONDO_OPCIONES,
	GAME_OVER,
	ARROW,
	HI_SCORES
};

/// Fuentes dentro de la Galeria
enum codigo_fuente
{
	CHICA,
	CHICA2
};

class Galeria
{
	public:
		Galeria ();
		~Galeria ();
		Image  * get_imagen (enum codigo_imagen imagen);
		Fuente * get_fuente (enum codigo_fuente indice); //TODO: Debe quedar obsoleta.

    private:
		Image  * imagenes [10];
		Fuente * fuentes [2];

};

#endif
