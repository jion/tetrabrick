#ifndef WIDGET_H
#define WIDGET_H
#include <string>
#include <vector>
#include <SDL/SDL.h>

using namespace std;

class Widget
{
    public:
        Widget();
        ~Widget();
        void show(class Escena *escena);

    protected:
        SDL_Surface *widget;

        void set_coord(int x, int y, int w, int h);
        void set_title(string title);
        void set_background(Uint8 r, Uint8 b, Uint8 g);
        void set_background(SDL_Surface *background_image);
        void set_alpha(Uint8  alpha);
        void set_border(int border);

    private:
        int x;
        int y;
        int w;
        int h;
        int border;
        int alpha;
        string title;
        SDL_Color color;

        void refresh(void);
        void create_window(void);

};

#endif
