#ifndef HISCORES_H
#define HISCORES_H
#define WIN_LIST    nucleo->configuration->win_list_

#include <SDL/SDL.h>
#include "widgets/widget.h"
#include <string>

using namespace std;

class Hi_Scores : public Widget
{
    public:
        Hi_Scores(class Nucleo *nucleo);
        void refresh(void);
        void set_newScore(Uint32 score);

    private:
        void print_scores(void);

        class Fuente *fuente;
        class Nucleo *nucleo;
};

#endif
