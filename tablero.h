/**
Class Tablero
~~~~~~~~~~~~~

Maneja el tablero del juego.

Uint8 tablero[10][23];
-
Contiene los datos de cada casillero del tablero. 0 Es un casillero
vacio, 0> es un casillero ocupado con un bloque, siendo cada numero
un color de bloque diferente. El tablero es de 10x20 pero hay 3
filas adicionales para meter la ficha nueva.

Uint8 lines[5];
-
Ubicacion de las lineas en el tablero. 0 significa que no hay linea,
0> siendo significa que hay una linea en la fila x-1

Uint8 bajar_uno(void);
-
Devuelve 0 si no colisiono la ficha, 1 si colisiono.

Uint8 nueva_ficha(Uint8 valor);
-
valor es el tipo de ficha a agregar. Devuelve 0 si todo sale ok, si
al agregar la ficha esta colisiona, significa que el juego ha terminado
y devuelve 1.

 1  3      13
 [----------]
    |       |
    |       |
    |       |
    1       10
**/

#ifndef tablero_h
#define tablero_h
#define TAB_BAJAUNO     0
#define TAB_COLISION    1
#define TAB_GAMEOVER   -1
#include <SDL\SDL.h>


class Tablero
{
    public:
        Tablero(class Galeria *galeria);
        ~Tablero();
        void print     (SDL_Surface *dst, int x, int y, int nx, int ny);
        void reset     (void);
        int  bajar_uno (void);
        int  bajar_todo(void);
        void derecha   (void);
        void izquierda (void);
        void rotar     (void);

        int i_lineas;    // Cantidad de lineas formadas con la ultima ficha
        int i_colision;  // La ficha actual colisiono y el tablero espera nueva ficha

    private:
        bool  colision(void);
        void  obtener_lineas(void);
        void  clean_lines(void);
        void  actualizar_tablero(void);

        SDL_Surface *sdls_tablero;
        class Ficha *f_actual;
        class Ficha *f_next;
        class Image *g_bloques;
        Uint8        i_tablero[20][10];
        Uint8        i_lines[4]; // Almacena las filas donde se han formado lineas
        Uint32       x, y;
};

#endif
