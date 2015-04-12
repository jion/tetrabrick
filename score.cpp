#include "score.h"
#include "image.h"
#include "galeria.h"

Score::Score(class Galeria *galeria, Uint32 *value)
{
    numeros = galeria->get_imagen(NUMEROS);
    this->value = value;
}

void Score::imprimir (SDL_Surface *dst, Uint8 zeros, Uint32 x, Uint32 y)
{
    Uint32 i, sx;
    Uint32 temp = *value;

    for(i=0; i < zeros; i++)
    {
        sx = (x + (20 * zeros)) - ((i+1) * 20);
        numeros->imprimir(dst, sx, y, temp % 10);
        temp /= 10;
    }
}
