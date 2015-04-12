#ifndef score_h
#define score_h

#include <SDL/SDL.h>

class Score
{
    public:
        Score(class Galeria *galeria, Uint32 *value);
        void imprimir (SDL_Surface *dst, Uint8 zeros = 10, Uint32 x = 0, Uint32 y = 0);

    private:
        Uint32 *value;

        class Image *numeros;
};

#endif
