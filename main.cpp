#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <stdexcept>
#include "nucleo.h"

using namespace std;

int main ( int argc, char *argv[] ) try
{
    int i_fullscreen = 0, i_depth = 0; // Parametros pasados a nucleo, 0 es default.

    // Lee los argumentos pasados al ejecutable
    while ( argc > 1 ) {
        if ( strcmp(argv[1], "-f") == 0 ) {
            i_fullscreen = 1;
            argv++;
            argc--;
        } else
        if ( strcmp(argv[1], "-bpp") == 0 ) {
            if ( argv[2] && (((i_depth = atoi(argv[2])) == 16) ||
                             ((i_depth = atoi(argv[2])) == 24) ||
                             ((i_depth = atoi(argv[2])) == 32)) ) {
				argv += 2;
				argc -= 2;
            } else {
				printf("The -bpp option requires a valid argument:\n\n");

				printf("16: Run 16bpp mode\n");
				printf("24: Run 24bpp mode\n");
				printf("32: Run 32bpp mode\n");
				exit(1);
            }
        } else
		if (( strcmp(argv[1], "-help") == 0 ) || (strcmp(argv[1], "--help") == 0)) {
			printf ("Usage:\n\n");
			printf (" -f        Set fullscreen mode\n");
			printf (" -bpp #    Screen bpp (16, 24 or 32)\n");
			break;
		} else {
            printf ("\"%s\" not is a valid argument. Write \"-help\" for more information.\n", argv[1]);
			break;
		}
    }

    // Inicia semilla de numeros aleatorios
    srand( time(NULL) ); //TODO: Pasar a Utils.

    // Se crea el objeto principal y se transfiere a este el control.
    Nucleo nucleo(i_fullscreen, i_depth);

	return 0;
}catch( exception& e ) // Recolector de excepciones.
{
    cerr << "Sale por SE: " + e.what() << endl;
    return 1;
}
