#ifndef CONFIGURATION_H
#define CONFIGURATION_H

// files
#define CONFIG_DAT  "config.dat"
#define SCORES_DAT  "scores.dat"

// set_default member values
#define DEFAULT_DISPLAY  1
#define DEFAULT_AUDIO    2
#define DEFAULT_INPUT    3
#define DEFAULT_GENERAL  4
#define DEFAULT_HISCORES 5
#define DEFAULT_ALL      0

// Display
#define SM_640X480      0
#define SM_800X600      1
#define SM_1024X768     2

#include <SDL/SDL.h>

/** TreeView of config.dat structure
    Config.dat
    |
    +-- Display
    |   |
    |   +-- resolution      (int)
    |   +-- fullscreen      (int)
    |   +-- depth           (int)
    |   +-- hwsurface       (int)
    |   +-- doublebuf       (int)
    |
    +-- Audio
    |   |
    |   +-- enabled         (int)
    |   +-- music           (int)
    |   +-- soundfx         (int)
    |   +-- path            (char[15])
    |
    +-- Input
    |   |
    |   +-- jostick         (int)
    |   +-- repeat_delay    (int)
    |   +-- repeat_interval (int)
    |   +-- k_left_         (SDLKey)
    |   +-- k_left_         (SDLKey)
    |   +-- k_right_        (SDLKey)
    |   +-- k_rotate_       (SDLKey)
    |   +-- k_down_         (SDLKey)
    |   +-- k_down_all_     (SDLKey)
    |   +-- k_pause_        (SDLKey)
    |
    +-- Game
    |   |
    |   +-- o_speed
    |   +-- x_speed
    |   +-- lines_per_level
    |   +-- h_board_size
    |   +-- w_board_size
    |   +-- game_mode
    |
    +-- General
        |
        +-- theme_path      (char[15])

    scores.dat
    |
    +-- HiScores
        +-- winner[10]      (char[15])
        +-- score           (unsigned)
        +-- lines           (unsigned)
        +-- level           (unsigned)
        +-- ttime           (unsigned)
**/

using namespace std;

class Configuration
{
    public:
        Configuration();
        ~Configuration();
        int save_configuration(void);
        void set_default(Uint8 what_default);

        struct {
            Uint8 resolution;
            Uint8 fullscreen;
            Uint8 depth;
            Uint8 hwsurface;
            Uint8 doublebuf;
        } display;

        struct {
            Uint8 enabled;
            Uint8 music;
            Uint8 soundfx;
            //Uint8 path[15];
        } audio;

        struct {
            Uint8 jostick;
            Uint16 repeat_delay;
            Uint16 repeat_interval;
            SDLKey k_left_;
            SDLKey k_right_;
            SDLKey k_rotate_;
            SDLKey k_down_;
            SDLKey k_down_all_;
            SDLKey k_pause_;
        } input;

        struct {
            //string theme_path;
        } general;

        struct hi_scores {
            //string name;
            Uint32 score;
            Uint32 lines;
            Uint32 level;
            Uint32 ttime;
        } hiscores[15];

    private:
        int load_configuration(void);
};

#endif
