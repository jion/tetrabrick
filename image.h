/* *************************************************************************
 *   Tetrabrick v1.0                                                       *
 *   Copyright (C) 2007 by Manuel Schnidrig                                *
 *   el.manu@gmail.com                                                     *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

//TODO: Cambiar el nombre de la clase por "grafica"

/**
Cargador de imagenes del juego.
Este cargador acepta imagenes simples, tiles o animaciones.
Las animaciones son tmb tiles.

imagen ( char *ruta, Uint8 tipo = 0, bool alpha = false, Uint8 fil = 0, Uint8 col = 0, Uint8 sep_pixels = 2 )
imagen ( SDL_Surface *imagen, Uint8 tipo = 0, bool alpha = false, Uint8 fil = 0, Uint8 col = 0, Uint8 sep_pixels = 2 )

tipo:
0 Imagen simple
1 Tiles
2 Animation Simple     (1,2,3,1,2,3)
3 Animation con vuelta (1,2,3,2,1)
4 GFX
5 Particle effect
*/

#ifndef Image_h
#define Image_h
#define IMG_STD     510
#define IMG_TIL     511
#define IMG_ANI     512
#define IMG_ANV     513
#define IMG_GFX     514
#define IMG_PTE     515
#include <SDL/SDL.h>

class Image
{
	public:
        // Constructor pasando imagen o ruta
		Image( char *path, int type = 0, bool alpha = false, int rows = 0,
            int cols = 0, int sep_pixels = 2 );
		Image( SDL_Surface *image, int type = 0, bool alpha = false,
            int rows = 0, int cols = 0, int sep_pixels = 2 );

		~Image();
		void cargar(const char *path, int item);
		void imprimir(SDL_Surface *dst, int x = 0, int y = 0, int tile = 0);

	private:
        void what_is(void);  // Devuelve si es una imagen GFX o BMP
        void load_gfx(void); // Carga un GFX
        void load_img(void); // Carga una imagen
        void load_pte(void); // Carga un efecto de particulas

        //TODO: Para las diferentes resoluciones
		SDL_Surface *sdls_image; // Contiene la imagen o
		//GFX_Data    gfx_data;    // Contiene el grafico GFX o
		//PTE_Data    pte_data;    // Contiene el efecto de particulas

		int   type;     // Tipo de imagen: descriptas arriba
		char* ph_pack;  // Path del pack de imagenes
		int   i_number; // Numero de item del pack

		// Tiles / Animaciones
		int cols;        // Columnas y
		int rows;        // Filas de imagenes que contiene
		int tile_width;  // Ancho y
		int tile_height; // Largo de cada una
		int sep_pixels;  // Separacion entre cada imagen
};

#endif
