#ifndef ficha_h
#define ficha_h

#include <SDL/SDL.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Ficha
{
    public:
        int  valor;
        int  posicion;
        bool data[4][4][4];

        Ficha( class Galeria *galeria );
        ~Ficha();
        void imprimir (SDL_Surface *dst, int x = 0, int y = 0);
        void nueva_ficha(int ficha = 0);
        void rotar(int lado); // 0 + // 1 -

    private:
        class Image *bloques;
        SDL_Surface  *pieza;

        void actualizar(void);
        void carga_valores(void);

        typedef Uint8 data_[4][4];

        typedef data_ pieza_[4];

        pieza_ fichas[7];

};

#endif
