#include <stdexcept>
#include <SDL/SDL_image.h>
#include "Image.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////
// Publicas
////////////////////////////////////////////////////////////////////////////////

Image::Image( char *path, int type, bool alpha, int rows, int cols, int sep_pixels)
{
    char tmp_path[1024] = "images/";
    strcat(tmp_path, path);

	this->image = IMG_Load(tmp_path);
	this->type  = type;
	this->rows  = rows;
	this->cols  = cols;
	this->sep_pixels = sep_pixels;

	if (alpha)
	{
		SDL_Surface *tmp = image;

		image = SDL_DisplayFormat(tmp);
		SDL_FreeSurface(tmp);

		if (image == NULL) throw std::runtime_error( SDL_GetError() );

		Uint32 colorkey = SDL_MapRGB(image->format, 255, 0, 255);
		SDL_SetColorKey ( image, SDL_SRCCOLORKEY, colorkey );
	}

    if(type != 0) // Si no es una imagen simple
    {
        tile_width  = this->image->w / cols; // Se divide la imagen en columnas
        tile_height = this->image->h / rows; // y filas.
    }
}

Image::Image( SDL_Surface *image, int type, bool alpha, int rows, int cols, int sep_pixels)
{
	// Inicializar valores de la imagen
	this->image = image;
	this->type  = type;
	this->rows  = rows;
	this->cols  = cols;
	this->sep_pixels = sep_pixels;

	if (alpha)
	{
		SDL_Surface *tmp = image;

		image = SDL_DisplayFormat(tmp);
		SDL_FreeSurface(tmp);

		if (image == NULL) throw std::runtime_error( SDL_GetError() );

		Uint32 colorkey = SDL_MapRGB(image->format, 255, 0, 255);
		SDL_SetColorKey ( image, SDL_SRCCOLORKEY, colorkey );
	}

    if(type != 0) // Si no es una imagen simple
    {
        tile_width  = this->image->w / cols; // Se divide la imagen en columnas
        tile_height = this->image->h / rows; // y filas.
    }
}

Image::~Image ()
{
	SDL_FreeSurface(image);
}

void Image::cargar(const char *path, int item) //TODO: Debe convertirse en el constructor
{
    ph_pack  = path;
    i_number = item;
    //TODO: Cargar una grafica desde el pack especificado
}

void Image::imprimir (SDL_Surface *dst, int x, int y, int i)
{
    static int anim_count = 0, sentido = 0;
    SDL_Rect src_rect;
    SDL_Rect dst_rect = {x, y, 0, 0};

    switch(type)
    {
        case 0:
            SDL_BlitSurface(image, 0, dst, &dst_rect);
            return;

        case 2: // Animacion simple
            anim_count++;
            if(anim_count == rows * cols) anim_count = 0;
            i = anim_count;
            break;

        case 3: // Animacion con back
            if( sentido )
            {
                anim_count++;
                if(anim_count == rows * cols)
                {
                    anim_count--;
                    sentido = 0;
                }
            }
            else
            {
                anim_count--;
                if(anim_count < 0)
                {
                    anim_count++;
                    sentido = 1;
                }
            }
            i = anim_count;
            break;
    }


    if (i > (rows * cols) || i < 0)
        return;

    src_rect.w = tile_width  - sep_pixels;
    src_rect.h = tile_height - sep_pixels;

    src_rect.x = ((i % cols) * tile_width ) + sep_pixels;
    src_rect.y = ((i / cols) * tile_height) + sep_pixels;

    SDL_BlitSurface(image, &src_rect, dst, &dst_rect);
}

////////////////////////////////////////////////////////////////////////////////
// Publicas
////////////////////////////////////////////////////////////////////////////////

void image::load_img(){}

void image::what_is(void){}

void image::load_gfx(void){}

void image::load_img(void){}

void image::load_pte(void){}
