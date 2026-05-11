#ifndef IncludeWinBox
#define IncludeWinBox
#include "Circle.hpp"
#include <string>

using namespace std;

class WinBox{
    private:
        Point pos;
        float multi;
        string label;
        int width = pegSpacing;
        int height = pegSpacing/2;
        ALLEGRO_COLOR bgcolor;
        ALLEGRO_COLOR refcolor;
        ALLEGRO_COLOR tcolor = al_map_rgb(0, 0, 0);
        ALLEGRO_FONT* font = nullptr;
        double total_frames = fps/2;
    public:
        double frame = 0;
        bool hit = false;
        WinBox(Point pos_, float multi_, ALLEGRO_COLOR color_);
        void fps_update() {};
        void draw_update();
        virtual ~WinBox();
        Point get_pos() { return pos; }
        float get_multi() { return multi; }
        ALLEGRO_COLOR get_refcolor() { return refcolor; }
        int get_width() { return width; }
        int get_height() { return height; }
};

#endif