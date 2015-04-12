#include <stdexcept>
#include "widget.h"
#include "escena.h"

////////////////////////////////////////////////////////////////////////////////
// Public
////////////////////////////////////////////////////////////////////////////////

Widget::Widget();
{
    create_window(void);
}

Widget::~Widget()
{
    SDL_FreeSurface(widget);
}

void Widget::show(Escena *escena)
{
    SDL_Rect sdlr_window;

    refresh();
    sdlr_window.x = x;
    sdlr_window.y = y;
    SDL_BlitSurface(widget, 0, escena->scene, &wgt_rect);
}

////////////////////////////////////////////////////////////////////////////////
// Protected
////////////////////////////////////////////////////////////////////////////////

void Widget::set_coord(int x, int y, int w, int h)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

void Widget::set_title(string title)
{
    // Coming soon hahahaa
}

void Widget::set_background(Uint8 r, Uint8 b, Uint8 g)
{
    SDL_FillRect(widget, 0, SDL_MapRGB(widget->format, r, g, b));
}

void Widget::set_background(SDL_Surface *background_image)
{
    //
}

void Widget::set_alpha(Uint8  alpha)
{
    SDL_SetAlpha(widget, SDL_SRCALPHA | SDL_RLEACCEL, alpha);
}

void Widget::set_border(int border)
{
    // Coming soon hahahaa
}

////////////////////////////////////////////////////////////////////////////////
// Private
////////////////////////////////////////////////////////////////////////////////

void Widget::create_window(void)
{
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

    widget = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32,
                                    rmask, gmask, bmask, amask);
    if(widget == NULL)
        throw std::runtime_error( SDL_GetError() );
}
