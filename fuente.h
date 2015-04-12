#ifndef Fuente_h
#define Fuente_h

#include <SDL/SDL.h>

/*!
 * \brief Almacena una plantilla de fuentes
 * \author Hugo Ruscitti
 */
class Fuente
{
	public:
		Fuente (char *ruta, bool alpha = false);
		~Fuente ();
		void imprimir (SDL_Surface *dst, char *cadena, int x, int y);

	private:
		SDL_Surface *ima;
		int separacion;
		/// define el órden de las letras en la grilla
		char cadena[113 + 1];
		/// mantiene la posición de cada letra en la grilla
		SDL_Rect rect_letras[113];

		void buscar_posiciones (void);
		int imprimir (SDL_Surface *dst, char letra, int x, int y);
		Uint32 get_pixel(SDL_Surface *surface, int x, int y);
};

#endif
