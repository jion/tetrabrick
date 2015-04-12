#include "hiscores.h"
#include "nucleo.h"
#include "galeria.h"

Hi_Scores::Hi_Scores(Nucleo *nucleo) : Widget( nucleo->screen, (SDL_Rect) {200, 50, 430, 520} )
{
    this->nucleo = nucleo;
    fuente = nucleo->galeria->get_fuente(CHICA2);
    set_color(183, 238, 128);
    refresh();
}

void Hi_Scores::refresh()
{
    static Image *fondo;
    fondo = nucleo->galeria->get_imagen (HI_SCORES);

    fondo->imprimir(widget);
    print_scores();
}

void Hi_Scores::print_scores(void)
{
    for(int i = 0; i < WIN_LIST.size(); i++)
    {
        fuente->imprimir(widget, (char*) WIN_LIST[i].name.c_str(), 50, 100 + (20*i) );
    }
}
