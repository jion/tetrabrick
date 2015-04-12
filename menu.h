#ifndef menu_h
#define menu_h

#include <string>
#include <vector>
#include <SDL/SDL.h>
#include "Escena.h"

using namespace std;

class Menu : public Escena
{
    public:
        Menu(class Nucleo *nucleo);
        ~Menu();
		void reset  (void);
		void print  (void);
		void update (void);
		void action (int i_key);

        vector<string>  items;

    private:
        void actualizar_titulos(void);

        class Image         *fondo;
        class Fuente        *fuente;

        string item[4];
        string menu[4];
        int menu_index;
        int item_index;
};

#endif
