#include <string.h>
#include <SDL/SDL_image.h>
#include "Fuente.h"

/*!
 * \brief Carga una grilla con las fuentes
 * \author Hugo Ruscitti
 */
Fuente :: Fuente (char *ruta, bool alpha)
{
	Uint32 colorkey;
	char tmp_ruta[1024] = "images/";

	strcat(tmp_ruta, ruta);
	printf("+ Cargando fuente: %s\n", ruta);

	ima = IMG_Load(tmp_ruta);

	if (ima == NULL)
	{
		printf("Error: %s\n", SDL_GetError());
		exit(1);
	}

	if (!alpha)
	{
		SDL_Surface *tmp = ima;

		ima = SDL_DisplayFormat(tmp);
		SDL_FreeSurface(tmp);

		if (ima == NULL)
		{
			printf("Error: %s\n", SDL_GetError());
			exit(1);
		}

		colorkey = SDL_MapRGB(ima->format, 255, 0, 255);
		SDL_SetColorKey(ima, SDL_SRCCOLORKEY, colorkey);
	}

	buscar_posiciones();
}

/*!
 * \brief Destructor del objeto
 * \author Hugo Ruscitti
 */
Fuente :: ~Fuente ()
{
	SDL_FreeSurface(ima);
	printf("- Descargando fuente.\n");
}


/*!
 * \brief Imprime una cadena de texto sobre dst
 * \author Hugo Ruscitti
 */
void Fuente :: imprimir (SDL_Surface *dst, char *texto, int x, int y)
{
	int i;
	int aux = 0;

	for (i = 0; texto[i] != '\0'; i ++)
	{
		aux = imprimir(dst, texto[i], x, y);
		x = x + aux + 2; // o 1 si el modo es 320x240
	}
}


/*!
 * \brief Imprime un caracter sobre dst.
 * \return el ancho (en pixeles) del caracter impreso.
 *
 * \author Hugo Ruscitti
 */
int Fuente :: imprimir (SDL_Surface *dst, char letra, int x, int y)
{
	int i;
	bool encuentra = false;
	SDL_Rect dstrect;

	if (letra == ' ')
	{
		x += 16; // o 8 si el modo es 320x240
		return 16; // o 8 si el modo es 320x240
	}

	// busca el indice del caracter
	for (i = 0; cadena[i] != '\0'; i++)
	{
		if (cadena[i] == letra)
		{
			encuentra = true;
			break;
		}
	}

	if (! encuentra)
	{
		printf("No se encuentra el caracter '%c'\n", letra);
		return 0;
	}

	dstrect.x = x;
	dstrect.y = y;
	dstrect.w = rect_letras[i].w;
	dstrect.h = rect_letras[i].h;

	SDL_BlitSurface(ima, &rect_letras[i], dst, &dstrect);

	return rect_letras[i].w;
}


/*!
 * \brief Determina la posición de cada letra dentro de la grilla
 * \author Hugo Ruscitti
 */
void Fuente :: buscar_posiciones (void)
{
#define LEYENDO 0
#define DIVISION 1
	int indice = 0;
	Uint32 color = 0;
	Uint32 negro = SDL_MapRGB(ima->format, 0, 0, 0);
	int estado = DIVISION;

	strcpy(cadena, "abcdefghijklmnopqrstuvwxyz" \
			"ABCDEFGHIJKLMNOPQRSYUVWXYZ" \
			"1234567890" \
			"ñÑáéíóúÁÉÍÓÚäëïöü" \
			"!¡?¿@#$%&'+-=><*/,.:;-_()[]{}|^`~\\");

	if (SDL_MUSTLOCK(ima))
	{
		if (SDL_LockSurface(ima) < 0)
		{
			printf("No se puede bloquear %s con %s\n", "ima", \
					"SDL_LockSurface");
			return;
		}
	}

	indice = -1;

	for (int x = 0; x < ima->w; x ++)
	{
		color = get_pixel (ima, x, 0);

		if (estado == DIVISION && color == negro)
		{
			estado = LEYENDO;
			indice ++;
			rect_letras[indice].x = x;
			rect_letras[indice].y = 2; // o 1 si el modo es 320x240
			rect_letras[indice].h = ima->h - 2; // o 1 si ...etc.
			rect_letras[indice].w = 0;
		}

		if (color == negro)
			rect_letras[indice].w ++;
		else
			estado = DIVISION;
	}

	if (SDL_MUSTLOCK(ima))
		SDL_UnlockSurface(ima);
}


/*!
 * \brief Obtiene un píxel de la superficie (extraido de la doumentación de SDL)
 * \author SDL Documentation
 */
Uint32 Fuente :: get_pixel(SDL_Surface *surface, int x, int y)
{
	int bpp = surface->format->BytesPerPixel;
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

	switch (bpp)
	{
		case 1:
			return *p;

		case 2:
			return *(Uint16 *)p;

		case 3:
			if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
				return p[0] << 16 | p[1] << 8 | p[2];
			else
				return p[0] | p[1] << 8 | p[2] << 16;

		case 4:
			return *(Uint32 *)p;

		default:
			return 0;
	}
}
